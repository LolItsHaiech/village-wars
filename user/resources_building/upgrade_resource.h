#ifndef UPGRADE_RESOURCE_H
#define UPGRADE_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include "check_up_resources.h"
#include "printboard_resource.h"
#include "number_of_resources.h"

void upgrade_resources(user *player) {
    int return_back = 0, number_resources, choice;

    system("cls");

    while (return_back == 0) {
        int state[6] = {0, 0, 0, 0, 0}, count_resource[3] = {0, 0, 0};
        number_resources = number_resource(player, state, count_resource);

        if (number_resources == 0) {
            printf("you have no resource to upgrade or resource is in prosses \n");
            return_back = 1;
            break;
        }

        printboard_delete_up_resource(player);
        scanf("%d", &choice);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            printboard_delete_up_resource(player);
            scanf("%d", &choice);
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
