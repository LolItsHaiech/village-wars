//
// Created by RayanClick on 1/12/2025.
//

#ifndef ADD_MILITARY_H
#define ADD_MILITARY_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include "../resources_building/set_time.h"
#include "../../file_management.h"
#include "../resources_building/printboard_resource.h"
#include "../../file_management.h"
#include"build_soldiers.h"
#include <unistd.h>

inline void add_military(user *player) {
    int choice;
    while (true) {
        system("cls");

        int i, counter = 0, numbers_military = 0, state[3] = {-1, -1, -1}, number_military_active = 0;
        for (i = 0; i < 6; i++)
            if (player->buildings[i].building_type == BARRACK && player->buildings[i].lvl != 0) {
                numbers_military++;
                if (player->buildings[i].status == DEFAULT && player->buildings[i].is_working == true) {
                    state[counter] = i;
                    number_military_active++;
                    counter++;
                }
            }
        if (numbers_military == 0) {
            printf("your village dont have any barrack building\n");
            sleep(2);
            break;
        }
        if (number_military_active == 0) {
            printf("your barracks building in process\n");
            sleep(2);
            break;
        }
        print_add_soldier(player, state);
        scanf("%d", &choice);
        while (choice < 1 || choice > number_military_active + 1) {
            printf("your choice is incorect try again\n");
            sleep(1);
            system("cls");
            print_add_soldier(player, state);
            scanf("%d", &choice);
        }
        if (choice == number_military_active + 1) {
            break;
        }

        if (player->buildings[state[choice-1]].storage != 0)
            build_soldiers(player, state[choice-1], player->buildings[state[choice-1]].lvl);
        else {
            printf("currently, it is not possible to create soldiers in this barrack\n");
            sleep(2);
        }
    }

}
#endif //ADD_MILITARY_H
