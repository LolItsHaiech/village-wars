#ifndef UPGRADE_BUILDING_H
#define UPGRADE_BUILDING_H
#include <stdio.h>
#include "../user.h"
#include <stdlib.h>
#include "check_up_building.h"
#include "printboard_resource.h"
#include "number_of_building.h"
#include <unistd.h>

inline void upgrade_building(user *player) {

    while (true) {
        system("cls");
        int state[6] = {0, 0, 0, 0, 0, 0}, count_building[4] = {0, 0, 0, 0}, numbers_building, choice,capacity[3]={0,0,0};
        numbers_building = number_buildings_finished(player, state, count_building);
        if (numbers_building == 0) {
            printf("you have no building to upgrade or building is not finished");
            sleep(3);

            break;
        }


        max_capacity(player, capacity);
        print_storage(player, capacity);
        printboard_delete_up_building(player);
        scanf("%d", &choice);
        fflush(stdin);

        while (1 > choice || choice > numbers_building + 1) {
            printf("your choice is incorrect try again");
            system("cls");
            print_storage(player, capacity);
            printboard_delete_up_building(player);
            scanf("%d", &choice);

                        fflush(stdin);
}
        if (choice == numbers_building + 1)
            break;

        check_up_building(player, player->buildings[state[choice - 1]].building_type, state[choice - 1],
                          player->buildings[state[choice - 1]].lvl);
        save_user(player);
    }
}
#endif
