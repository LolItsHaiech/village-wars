#include "attacks.h"
#include "../user.h"
#include "../../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../file_management.h"
#include "../../utils/input.h"
#include "../../utils/time.h"


enum AttackMenuOptions { HISTORY, VIEW_ATTACKS, NEW_ATTACK, RETURN };

void attack_ui(user *player) {
    bool exited = false;
    while (!exited) {
        enum AttackMenuOptions input =(enum AttackMenuOptions) open_menu("Militaries", (char *[]){
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
           "  %d warrior(s)"
           "  %d archer(s)"
           "  %d rider(s)",
           player->soldiers_count.warrior, player->soldiers_count.archer, player->soldiers_count.rider);

    int warrior = read_int_input("Warrior count:", 0, player->soldiers_count.warrior);
    int archer = read_int_input("Archer count:", 0, player->soldiers_count.archer);
    int rider = read_int_input("Rider count:", 0, player->soldiers_count.rider);

    system("cls");
    printf("New attack\n\n");

    int enemies_count;
    user *enemies_list = get_all_users_expect(&enemies_count, player);

    printf("Which village do you want to attack?\n");
    int i;
    for (i = 0; i < enemies_count; i++)
        printf("  %d - %s (%s village)\n", i + 1, enemies_list[i].username, enemies_list->village_name);

    int input = read_int_input("Village number", 1, enemies_count);

    attack new_attack;
    new_attack.id = get_last_attack_id();
    new_attack.attacked_user_id = enemies_list[input-1].id;
    new_attack.attacker_user_id = player->id;
    new_attack.request_time = time(NULL);
    new_attack.soldiers_count.rider = rider;
    new_attack.soldiers_count.archer = archer;
    new_attack.soldiers_count.warrior = warrior;
    new_attack.surviving_soldiers = new_attack.soldiers_count;
    new_attack.status = IN_PROGRESS;

    if(enemies_count!=0)
        free(enemies_list);


    player->soldiers_count.warrior-=warrior;
    player->soldiers_count.archer-=archer;
    player->soldiers_count.rider-=rider;
    save_user(player);
    add_attack(new_attack);
}

void view_attacks_ui(user* player) {
    // todo update

    system("cls");
    printf("View attacks\n\n");

    int attack_count;
    attack *attack_arr = get_user_attacks(&attack_count, player->id, true);
    int i;
    for (i = 0; i < attack_count; ++i) {
        char attacker_username[11];
        char attacked_username[11];
        char start_time[50];
        get_username_by_id(attacker_username, attack_arr[i].attacker_user_id);
        get_username_by_id(attacked_username, attack_arr[i].attacked_user_id);
        get_date_time(start_time, &attack_arr[i].request_time);
        printf("  %d - %s -> %s  %s, %d %d %d\n", i + 1,
            attacker_username, attacked_username, start_time,
            attack_arr[i].soldiers_count.warrior,attack_arr[i].soldiers_count.archer,
            attack_arr[i].soldiers_count.rider);
    }
    free(attack_arr);

    int input;
    printf("Enter the attack you want to proceed to the next step:\n"
           "(Enter 0 to go back)\n");
    input = read_int_input("", 0, attack_count);
    if(input == 0)
        return;

    proceed_attack(attack_arr);
}


void attacks_history_ui(user* player) {
    // todo update

    system("cls");
    printf("Attacks history\n\n");

    int attack_count;
    attack *attack_arr = get_user_attacks(&attack_count, player->id, false);
    int i;
    for (i = 0; i < attack_count; ++i) {
        char attacker_username[11];
        char attacked_username[11];
        char start_time[50];
        char end_time[50];
        get_username_by_id(attacker_username, attack_arr[i].attacker_user_id);
        get_username_by_id(attacked_username, attack_arr[i].attacked_user_id);
        get_date_time(start_time, &attack_arr[i].request_time);
        printf("  %s -> %s  %s, %s, %d %d %d %s\n",
            attacker_username, attacked_username, start_time, end_time,
            attack_arr[i].soldiers_count.warrior,attack_arr[i].soldiers_count.archer,
            attack_arr[i].soldiers_count.rider, attack_arr[i].attackers_won?"won":"lost");
    }
    free(attack_arr);
    char inp;
    do {
        printf("Enter 0 to go back");
        inp = getchar();
        fflush(stdin);
    } while (inp!='0');
}

bool proceed_attack(user* player, attack* input_attack) {
    switch (input_attack->status) {
        case ON_THE_WAY:
            if(input_attack->request_time + 600 >= time(NULL)) {
                input_attack->status = IN_PROGRESS;
                input_attack->start_time = time(NULL);
                save_attack(input_attack);
                return true;
            }
            return false;

        case IN_PROGRESS:
            break;
        //todo
        case ON_THE_WAY_BACK:
            if(input_attack->end_time + 600 >= time(NULL)) {
                player->soldiers_count.archer+=input_attack->surviving_soldiers.archer;
                player->soldiers_count.warrior+=input_attack->surviving_soldiers.warrior;
                player->soldiers_count.rider+=input_attack->surviving_soldiers.rider;
                save_user(player);
                return true;
            }
            return false;
        case DONE:
            return false;
    }
}
