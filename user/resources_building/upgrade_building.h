#ifndef UPGRADE_BUILDING_H
#define UPGRADE_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include "check_up_building.h"
#include "printboard_resource.h"
#include "number_of_building.h"
#include "../../file_management.h"

int return_back = 0;

void upgrade_building(user *player) {
    system("cls");

    while (return_back == 0) {
        int state[6] = {0, 0, 0, 0, 0, 0}, count_building[4] = {0, 0, 0, 0};
        int numbers_building;
        int i, choice, less_wood = 0, less_stone = 0, less_food = 0, check_up;
        numbers_building = number_buildings(player, state, count_building);

        if (numbers_building == 0) {
            printf("you have no building to upgrade");
            return_back = 1;
            break;
        }

        printboard_delete_up_building(player);
        scanf("%d", &choice);
        while (1 > choice || choice > numbers_building + 1) {
            printf("your choice is incorect try again");
            system("cls");

            printboard_delete_up_building(player);
            scanf("%d", &choice);
        }
        if (choice == numbers_building + 1) {
            return_back = 1;
            break;
        }
        //todo type
        check_up_building(player, player->buildings[state[choice - 1]].building_type, state[choice - 1],
                          player->buildings[state[choice - 1]].lvl);
        save_user(player);
    }
}
#endif
