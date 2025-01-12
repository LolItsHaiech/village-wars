#ifndef DELETE_BUILDING_H
#define DELETE_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "set_time.h"
#include "number_of_building.h"
#include "printboard_resource.h"

inline void delete_building(user *player) {
    system("cls");
    //todo boolean
    int choice, except_choice;
    while (true) {
        int state[6] = {0, 0, 0, 0, 0, 0}, number_building, count_building[6] = {0, 0, 0, 0, 0, 0};
        number_building = number_buildings(player, state, count_building);
        if (number_building == 0) {
            printf("you have no building to delete");
            break;
        }
        printboard_delete_up_building(player);
        scanf("%d", &choice);
        while (1 > choice || choice > number_building + 1) {
            printf("your choice is incorect try again");
            system("cls");
            printboard_delete_up_building(player);
            scanf("%d", &choice);
        }
        if (choice == number_building + 1)
            break;
        if (1 <= choice && choice <= number_building) {
            system("cls");
            printf("are you sure to delete this building %s level %d ?\n1.yes\n2.no",
                   name_building[(int) player->buildings[state[choice - 1]].building_type],
                   player->buildings[state[choice - 1]].lvl);
            scanf("%d", &except_choice);
            while (except_choice != 1 && except_choice != 2) {
                printf("your choice is incorect try again");
                scanf("%d", &except_choice);
            }
            switch (except_choice) {
                case 1:
                    system("cls");
                    printf("deleting building..... \rready to delete in  2 minutes");
                    player->buildings[state[choice - 1]].lvl = 0;
                    set_time(player, 2, state[choice - 1], 120);
                    player->buildings[state[choice - 1]].status = DELETING;
                    save_user(player);
                    break;

                case 2:
                    printf("process is cancelled");
                    break;
            }
        }
    }
}

#endif
