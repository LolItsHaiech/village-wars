#ifndef CHECK_BUILD_SOLDIERS_H
#define CHECK_BUILD_SOLDIERS_H
#include <stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "../resources_building/set_time.h"
#include "number_military.h"
#include "../resources_building/printboard_resource.h"
#include "../../file_management.h"
#include "check_can_build.h"
#include <unistd.h>
#include <math.h>

inline void max_build_soldiers(user *player, int max_soldier[]) {
    int food, wood, stone;
    food = player->resources.food_count;
    wood = player->resources.wood_count;
    stone = player->resources.stone_count;

    max_soldier[0] = (food / 20) < wood / 50 ? (food / 20) : (wood / 50);
    max_soldier[0] = max_soldier[0] < stone / 30 ? max_soldier[0] : (stone / 30);
    max_soldier[1] = (food / 30) < wood / 75 ? (food / 30) : (wood / 75);
    max_soldier[1] = max_soldier[1] < stone / 30 ? max_soldier[1] : (stone / 30);
    max_soldier[2] = (food / 60) < wood / 100 ? (food / 60) : (wood / 100);
    max_soldier[2] = max_soldier[2] < stone / 50 ? max_soldier[2] : (stone / 50);
}

inline void build_soldiers(user *player, int state_barrack, int level) {
    while (true) {
        int soldiers_count = 0, capacity[3] = {0, 0, 0}, time_needed, choice, empty_soldier = 0, max_soldier[3];

        system("cls");

        if (player->buildings[state_barrack].storage == 0) {
            printf("this building cant create another building");
            sleep(1);
            break;
        }
        max_build_soldiers(player, max_soldier);
        system("cls");
        max_capacity(player, capacity);
        print_storage(player, capacity);
        printf(" barack in this moment can build %d soldirs\n", player->buildings[state_barrack].storage);
        printf("max soldier you can build whit source warrior=%d archer=%d rider=%d \n", max_soldier[0], max_soldier[1],
               max_soldier[2]);

        printf("soldier\tdefence power\tattack power\ttime build(second)\tfood req stone req  wood req"
               "\n1_warior\t5\t10\t\t\t%d\t\t20\t30\t50\n2_archer\t4\t15\t\t\t%d\t\t30\t30\t75\n3_rider\t\t7\t20\t\t\t%d\t\t60\t50\t100"
               "\n4_return back\n", time_build_soldier[player->buildings[state_barrack].lvl].warrior,
               time_build_soldier[player->buildings[state_barrack].lvl].archer,
               time_build_soldier[player->buildings[state_barrack].lvl].rider);
        scanf("%d", &choice);

        while (choice < 1 || choice > 4) {
            printf("your choic is incorect try again\n");
            sleep(1);
            system("cls");
            max_capacity(player, capacity);
            print_storage(player, capacity);
            printf(" barack in this moment can build %d soldirs\n", player->buildings[state_barrack].storage);
            printf("max soldier you can build whit source warrior=%d archer=%d rider=%d \n", max_soldier[0],
                   max_soldier[1], max_soldier[2]);

            printf(" barack in this moment can build %d soldirs\n", player->buildings[state_barrack].storage);
            printf("soldier\tdefence power\tattack power\ttime build(second)"
                   "\n1_warior\t5\t10\t\t\t%d\t\t20\t30\t50\n2_archer\t4\t15\t\t\t%d\t\t30\t30\t75\n3_rider\t\t7\t20\t\t\t%d\t\t60\t50\t100"
                   "\n4_return back\n", time_build_soldier[player->buildings[state_barrack].lvl].warrior,
                   time_build_soldier[player->buildings[state_barrack].lvl].archer,
                   time_build_soldier[player->buildings[state_barrack].lvl].rider);

            scanf("%d", &choice);
        }
        if (choice == 4)
            break;
        //todo choice enum
        switch (choice) {
            case 1: //todo time build and max build it
                printf("enter the number you want to build warior(print 0 to exit)\n");
                scanf("%d", &soldiers_count);
                while (soldiers_count > player->buildings[state_barrack].storage || soldiers_count < 0) {
                    system("cls");

                    if (soldiers_count < 0) {
                        printf("your choice is incorect try again\n");
                        sleep(1);
                    } else if (soldiers_count > player->buildings[state_barrack].storage) {
                        printf("your military can not create this amount of soldiers at this time\n");
                        sleep(1);
                    }
                    printf("try again\nenter the number you want to build warior(print 0 to exit)\n");
                    scanf("%d", &soldiers_count);
                }
                if (soldiers_count == 0)
                    break;
                if (check_can_up(player, WARRIOR, soldiers_count)) {
                    system("cls");
                    printf("WARRIOR  is ready to build in\n");
                    empty_soldier = find_empty_soldier_builder(player);
                    player->soldiers[empty_soldier].soldier = WARRIOR;
                    player->soldiers[empty_soldier].number_soldiers = soldiers_count;
                    time_needed = get_time_needed_soldiers(level, WARRIOR);
                    set_time(player, 3, empty_soldier, time_needed);
                    player->buildings[state_barrack].storage -= soldiers_count;
                    player->soldiers[empty_soldier].state_barrack = state_barrack;;
                    save_user(player);
                    sleep(1);
                }
                break;
            case 2:
                printf("enter the number you want to build archer(print 0 to exit)\n");
                scanf("%d", &soldiers_count);
                while (soldiers_count > player->buildings[state_barrack].storage || soldiers_count < 0) {
                    system("cls");

                    if (soldiers_count < 0) {
                        printf("your choice is incorect try again\n");
                    } else if (soldiers_count > player->buildings[state_barrack].storage) {
                        printf("your military can not create this amount of soldiers at this time\n");
                    }
                    printf("try again\nenter the number you want to build archer(print 0 to exit)\n");
                    scanf("%d", &soldiers_count);
                }
                if (soldiers_count == 0)
                    break;
                if (check_can_up(player, ARCHER, soldiers_count)) {
                    {
                        //todo time
                        system("cls");
                        printf("ARCHER is ready to build in\n");
                        empty_soldier = find_empty_soldier_builder(player);
                        player->soldiers[empty_soldier].soldier = ARCHER;
                        player->soldiers[empty_soldier].number_soldiers = soldiers_count;
                        time_needed = get_time_needed_soldiers(level, ARCHER);
                        set_time(player, 3, empty_soldier, time_needed);
                        player->buildings[state_barrack].storage -= soldiers_count;
                        player->soldiers[empty_soldier].state_barrack = state_barrack;;

                        save_user(player);
                        sleep(1);
                    }
                    break;
                case 3:
                    printf("enter the number you want to build rider(print 0 to exit)\n");
                    scanf("%d", &soldiers_count);
                    while (soldiers_count > player->buildings[state_barrack].storage || soldiers_count < 0) {
                        system("cls");
                        if (soldiers_count < 0) {
                            printf("your choice is incorect try again\n");
                        } else if (soldiers_count > player->buildings[state_barrack].storage) {
                            printf("your military can not create this amount of soldiers at this time\n");
                        }
                        printf("try again\nenter the number you want to build rider(print 0 to exit)\n");
                        scanf("%d", &soldiers_count);
                    }
                    if (soldiers_count == 0)
                        break;
                    else if (check_can_up(player, RIDER, soldiers_count)) {
                        system("cls");
                        printf("RIDER  is ready to build in\n");
                        empty_soldier = find_empty_soldier_builder(player);
                        player->soldiers[empty_soldier].soldier = RIDER;
                        player->soldiers[empty_soldier].number_soldiers = soldiers_count;
                        time_needed = get_time_needed_soldiers(level, RIDER);
                        set_time(player, 3, empty_soldier, time_needed);
                        player->buildings[state_barrack].storage -= soldiers_count;
                        player->soldiers[empty_soldier].state_barrack = state_barrack;;

                        save_user(player);
                        sleep(1);
                    }
                }
        }
    }
}
#endif //CHECK_BUILD_SOLDIERS_H
