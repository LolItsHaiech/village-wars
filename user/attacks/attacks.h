#ifndef ATTACKS_H
#define ATTACKS_H

#include "../../utils/structs.h"

#include "attacks.h"

#include <math.h>

#include "../user.h"
#include "../../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "../../utils/input.h"
#include "../../utils/time.h"
#include "../../headers/constants.h"


void attack_ui(user *player);
void new_attack_ui(user *player);
void view_attacks_ui(user *player);
void attacks_history_ui(user *player);
bool proceed_attack(user *player, attack *input_attack);

enum AttackMenuOptions { HISTORY = 1, VIEW_ATTACKS, NEW_ATTACK, RETURN };

void attack_ui(user *player) {
    bool exited = false;

    while (!exited) {
        enum AttackMenuOptions input = (enum AttackMenuOptions) open_menu("Militaries", (char *[]){
                                                                              "History",
                                                                              "View attacks",
                                                                              "New Attack",
                                                                              "Return back"
                                                                          }, 4);

        switch (input) {
            case HISTORY:
                attacks_history_ui(player);
                break;
            case VIEW_ATTACKS:
                view_attacks_ui(player);
                break;
            case NEW_ATTACK:
                new_attack_ui(player);
                break;
            case RETURN:
                exited = true;
        }
    }
}

void new_attack_ui(user *player) {
    system("cls");
    printf("New attack\n\n"
           "Available soldiers:\n"
           "  %d warrior(s)\n"
           "  %d archer(s)\n"
           "  %d rider(s)\n",
           player->soldiers_count.warrior, player->soldiers_count.archer, player->soldiers_count.rider);

    int warrior = read_int_input("Warrior count", 0, player->soldiers_count.warrior);
    int archer = read_int_input("Archer count ", 0, player->soldiers_count.archer);
    int rider = read_int_input("Rider count  ", 0, player->soldiers_count.rider);

    system("cls");
    printf("New attack\n\n");

    int enemies_count;
    user *enemies_list = get_all_users_expect(&enemies_count, player);

    printf("Which village do you want to attack?\n"
           "(Enter 0 to return back)\n\n");
    int i;
    for (i = 0; i < enemies_count; i++)
        printf("  %d - %s (%s village)\n", i + 1, enemies_list[i].username, enemies_list[i].village_name);

    int input = read_int_input("Village number", 0, enemies_count);

    if(input==0) {
        if (enemies_count != 0)
            free(enemies_list);
        return;
    }

    attack new_attack;
    new_attack.id = get_last_attack_id() + 1;
    new_attack.attacked_user_id = enemies_list[input - 1].id;
    new_attack.attacker_user_id = player->id;
    new_attack.request_time = time(NULL);
    new_attack.start_attack_time = time(NULL);
    new_attack.soldiers_count.rider = rider;
    new_attack.soldiers_count.archer = archer;
    new_attack.soldiers_count.warrior = warrior;
    new_attack.surviving_soldiers = new_attack.soldiers_count;
    new_attack.status = ON_THE_WAY;
    new_attack.attackers_won = false;


    if (enemies_count != 0)
        free(enemies_list);


    player->soldiers_count.warrior -= warrior;
    player->soldiers_count.archer -= archer;
    player->soldiers_count.rider -= rider;
    save_user(player);
    add_attack(new_attack);
}

void view_attacks_ui(user *player) {
    system("cls");
    printf("View attacks\n\n");

    int attack_count;
    attack *attack_arr = get_user_attacks(&attack_count, player->id, false); // todo fix this shit
    int i;
    for (i = 0; i < attack_count; ++i) {
        char start_time[50];
        user *attacker = get_user_by_id(attack_arr[i].attacker_user_id);
        user *attacked = get_user_by_id(attack_arr[i].attacked_user_id);
        get_date_time(start_time, &attack_arr[i].request_time);
        printf("  %d - %s -> %s  %s, %d %d %d\n", i + 1,
               attacker->username, attacked->username, start_time,
               attack_arr[i].soldiers_count.warrior, attack_arr[i].soldiers_count.archer,
               attack_arr[i].soldiers_count.rider);

        free(attacker);
        free(attacked);
    }

    int input;
    printf("Enter the attack you want to proceed to the next step:\n"
        "(Enter 0 to go back)\n");
    input = read_int_input("", 0, attack_count);
    if (input == 0)
        return;

    proceed_attack(player, &attack_arr[input - 1]);
    free(attack_arr);
}


void attacks_history_ui(user *player) {
    system("cls");
    printf("Attacks history\n\n");

    int attack_count;
    attack *attack_arr = get_user_attacks(&attack_count, player->id, true); // todo fix this shit
    int i;
    for (i = 0; i < attack_count; ++i) {
        char start_time[50];
        char end_time[50];
        user *attacker = get_user_by_id(attack_arr[i].attacker_user_id);
        user *attacked = get_user_by_id(attack_arr[i].attacked_user_id);
        get_date_time(start_time, &attack_arr[i].request_time);
        printf("  %s -> %s  %s, %s, %d %d %d %s\n",
               attacker->username, attacked->username, start_time, end_time,
               attack_arr[i].soldiers_count.warrior, attack_arr[i].soldiers_count.archer,
               attack_arr[i].soldiers_count.rider, attack_arr[i].attackers_won ? "won" : "lost");

        free(attacker);
        free(attacked);
    }
    free(attack_arr);
    char inp;
    do {
        printf("Enter 0 to go back");
        inp = getchar();
        fflush(stdin);
    } while (inp != '0');
}

bool proceed_attack(user *player, attack *input_attack) {
    // todo test
    switch (input_attack->status) {
        case ON_THE_WAY:
            if (input_attack->request_time + 600 <= time(NULL)) {
                input_attack->status = ON_THE_WAY;
                input_attack->start_attack_time = time(NULL);

                int strength_sum = input_attack->soldiers_count.warrior * warrior_stats.strength +
                                   input_attack->soldiers_count.archer * archer_stats.strength +
                                   input_attack->soldiers_count.rider * rider_stats.strength;

                user *attacked_user = get_user_by_id(input_attack->id);
                int defence_sum = attacked_user->soldiers_count.warrior * warrior_stats.defence +
                                  attacked_user->soldiers_count.archer * archer_stats.defence +
                                  attacked_user->soldiers_count.rider * rider_stats.defence;

                if (strength_sum > defence_sum) {
                    // attack won
                    input_attack->attackers_won = true;
                    //todo ?
                    bool soldiers_eleminated = false;


                    if (attacked_user->soldiers_count.warrior != 0) {
                        int count = ceil((float) 2 * (strength_sum - defence_sum) / warrior_stats.strength);
                        attacked_user->soldiers_count.warrior = attacked_user->soldiers_count.warrior > count
                                                                    ? attacked_user->soldiers_count.warrior - count
                                                                    : 0;
                        soldiers_eleminated = true;
                    } else if (attacked_user->soldiers_count.archer != 0) {
                        int count = ceil((float) 2 * (strength_sum - defence_sum) / archer_stats.strength);
                        attacked_user->soldiers_count.archer = attacked_user->soldiers_count.archer > count
                                                                   ? attacked_user->soldiers_count.archer - count
                                                                   : 0;
                        soldiers_eleminated = true;
                    } else if (attacked_user->soldiers_count.rider != 0) {
                        int count = ceil((float) 2 * (strength_sum - defence_sum) / rider_stats.strength);
                        attacked_user->soldiers_count.rider = attacked_user->soldiers_count.rider > count
                                                                  ? attacked_user->soldiers_count.rider - count
                                                                  : 0;
                        soldiers_eleminated = true;
                    }


                    if (soldiers_eleminated) {
                        player->resources.food_count = attacked_user->resources.food_count *= 0.5;
                        player->resources.wood_count = attacked_user->resources.wood_count *= 0.5;
                        player->resources.stone_count = attacked_user->resources.stone_count *= 0.5;

                        attacked_user->resources.food_count *= 0.5;
                        attacked_user->resources.wood_count *= 0.5;
                        attacked_user->resources.stone_count *= 0.5;
                    } else {
                        player->resources.food_count = attacked_user->resources.food_count *= 0.6;
                        player->resources.wood_count = attacked_user->resources.wood_count *= 0.6;
                        player->resources.stone_count = attacked_user->resources.stone_count *= 0.6;

                        attacked_user->resources.food_count *= 0.4;
                        attacked_user->resources.wood_count *= 0.4;
                        attacked_user->resources.stone_count *= 0.4;
                    }

                    system("cls");
                    printf("Attack won\n");

                    printf("Press <Enter> to continue...\n");
                    getchar();
                    fflush(stdin);


                    // todo check capacity before adding
                } else {
                    // attack lost

                    //todo ?
                    if (input_attack->surviving_soldiers.warrior != 0) {
                        int count = ceil((float) 2 * (defence_sum - strength_sum) / warrior_stats.strength);
                        input_attack->surviving_soldiers.warrior = input_attack->surviving_soldiers.warrior > count
                                                                       ? input_attack->surviving_soldiers.warrior -
                                                                         count
                                                                       : 0;
                    } else if (input_attack->surviving_soldiers.archer != 0) {
                        int count = ceil((float) 2 * (defence_sum - strength_sum) / archer_stats.strength);
                        input_attack->surviving_soldiers.archer = input_attack->surviving_soldiers.archer > count
                                                                      ? input_attack->surviving_soldiers.archer - count
                                                                      : 0;
                    } else if (input_attack->surviving_soldiers.rider != 0) {
                        int count = ceil((float) 2 * (defence_sum - strength_sum) / rider_stats.strength);
                        input_attack->surviving_soldiers.rider = input_attack->surviving_soldiers.rider > count
                                                                     ? input_attack->surviving_soldiers.rider - count
                                                                     : 0;
                    }

                    system("cls");
                    printf("Attack lost\n"
                           "%d warrior(s), %d archer(s) and %d rider(s) survived.\n\n",
                           input_attack->surviving_soldiers.warrior, input_attack->surviving_soldiers.archer,
                           input_attack->surviving_soldiers.rider);

                    printf("Press <Enter> to continue...\n");
                    getchar();
                    fflush(stdin);


                    if (input_attack->surviving_soldiers.rider == 0 &&
                        input_attack->surviving_soldiers.warrior == 0 &&
                        input_attack->surviving_soldiers.archer == 0) {
                        input_attack->status = DONE;
                    }
                }

                save_user(attacked_user);
                save_user(player);
                save_attack(input_attack);
                free(attacked_user);
                return true;
            }

            system("cls");
            printf("Your soldiers didn't reach the destination yet.\n");

            printf("Press <Enter> to continue...\n");
            getchar();
            fflush(stdin);

            return false;

        case ON_THE_WAY_BACK:
            if (input_attack->start_attack_time + 600 <= time(NULL)) {
                player->soldiers_count.archer += input_attack->surviving_soldiers.archer;
                player->soldiers_count.warrior += input_attack->surviving_soldiers.warrior;
                player->soldiers_count.rider += input_attack->surviving_soldiers.rider;
                save_user(player);


                system("cls");
                printf("Your soldiers came back\n");

                printf("Press <Enter> to continue...\n");
                getchar();
                fflush(stdin);

                return true;
            }

            system("cls");
            printf("Your soldiers have not arrived yet.\n");

            printf("Press <Enter> to continue...\n");
            getchar();
            fflush(stdin);
            return false;


        default:
            system("cls");
            printf("Failed to proceed");

            printf("Press <Enter> to continue...\n");
            getchar();
            fflush(stdin);
            return false;
    }
}

#endif //ATTACKS_H
