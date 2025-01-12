#ifndef DELETE_RESOURCE_H
#define DELETE_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "printboard_resource.h"
#include "number_of_resources.h"
#include "set_time.h"


inline void delete_resources(user *player) {
    system("cls");
    //todo boolean
    int choice, except_choice;
    while (true) {
        int state[6] = {0, 0, 0, 0, 0, 0}, number_resources, count_resources[3] = {0, 0, 0};
        number_resources = number_resource(player, state, count_resources);
        if (number_resources == 0) {
            printf("you have no resource to delete");
            break;
        }
        printboard_delete_up_resource(player);
        scanf("%d", &choice);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            system("cls");
            printboard_delete_up_resource(player);
            scanf("%d", &choice);
        }
        if (choice == number_resources + 1)
            break;
        if (1 <= choice && choice <= number_resources) {
            printf("are you sure to delete this resource %s level %d ?\n1.yes\n2.no",
                   name_resource[player->resources_generators[state[choice - 1]].resource],
                   player->resources_generators[state[choice - 1]].lvl);
            scanf("%d", &except_choice);
            while (except_choice != 1 && except_choice != 2) {
                printf("your choice is incorrect try again");
                system("cls");
                printf("are you sure to delete this resource %s level %d ?\n1.yes\n2.no",
                       name_resource[(int) player->resources_generators[state[choice - 1]].resource],
                       player->resources_generators[state[choice - 1]].lvl);
                scanf("%d", &except_choice);
            }
            switch (except_choice) {
                case 1:
                    printf("deleting resource..... \ready to delete in  1 minutes");
                    player->resources_generators[state[choice - 1]].lvl = 0;
                    set_time(player, 1, state[choice - 1], 60);
                    player->resources_generators[state[choice - 1]].status = DELETING;
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
