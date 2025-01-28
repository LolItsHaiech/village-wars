#ifndef UPGRADE_RESOURCE_H
#define UPGRADE_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include "check_up_resources.h"
#include "number_of_resources.h"
#include "../../file_management.h"
#include <unistd.h>

inline void upgrade_resources(user *player) {
    int return_back = 0, number_resources, choice;
    system("cls");
    while (return_back == 0) { //todo
        system("cls");
        int state[6] = {0, 0, 0, 0, 0,0}, count_resource[3] = {0, 0, 0},capacity[3];
        number_resources = number_resource_finished(player, state, count_resource);

        if (number_resources == 0) {
            printf("you have no resource to upgrade or resource is in not finished \n");
            sleep(3);

            return_back = 1;

            break;
        }
        max_capacity(player, capacity);
        print_storage(player, capacity);
        printboard_delete_up_resource(player);
        scanf("%d", &choice);

                        fflush(stdin);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorrect try again");
            printboard_delete_up_resource(player);
            scanf("%d", &choice);
            fflush(stdin);

        }
        if (choice == number_resources + 1) {
            return_back = 1;
            break;
        }
        check_up_resource(player, player->resources_generators[state[choice - 1]].resource, state[choice - 1],
                          player->resources_generators[state[choice - 1]].lvl);
        save_user(player);
    }
}
#endif
