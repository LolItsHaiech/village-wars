#ifndef DELETE_RESOURCE_H
#define DELETE_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "printboard_resource.h"
#include "number_of_resources.h"
#include "set_time.h"
#include <unistd.h>
void print_delete_resource(user *player) {
    int i, counter = 1,resource_req[3]={0,0,0};
    printf("\nresources:   \t level\tproduction");
    for (i = 0; i < 6; i++)


        if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT) {
            resource_requirements(player->resources_generators[i].resource,player->resources_generators[i].lvl,resource_req);
            printf("\n  %d\t%s\t%d\t%d", counter, name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].lvl, player->resources_generators[i].collect_rate);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting resource or return back:\n");
}


inline void delete_resources(user *player) {
    system("cls");
    //todo boolean
    int choice, except_choice;
    while (true) {
        int state[6] = {0, 0, 0, 0, 0, 0}, number_resources, count_resource[3] = {0, 0, 0};
        number_resources = number_resource_finished(player, state, count_resource);
        if (number_resources == 0) {
            printf("you have no resource finished to delete");
            sleep(3);

            break;
        }
       print_delete_resource(player);
        scanf("%d", &choice);
        fflush(stdin);

        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            system("cls");
            print_delete_resource(player);
            scanf("%d", &choice);
            fflush(stdin);

        }
        if (choice == number_resources + 1)
            break;
        if (1 <= choice && choice <= number_resources) {
            printf("are you sure to delete this resource %s level %d ?\n1.yes\n2.no",
                   name_resource[player->resources_generators[state[choice - 1]].resource],
                   player->resources_generators[state[choice - 1]].lvl);

            scanf("%d", &except_choice);
            fflush(stdin);

            while (except_choice != 1 && except_choice != 2) {
                printf("your choice is incorrect try again");
                system("cls");
                printf("are you sure to delete this resource %s level %d ?\n1.yes\n2.no",
                       name_resource[(int) player->resources_generators[state[choice - 1]].resource],
                       player->resources_generators[state[choice - 1]].lvl);
                scanf("%d", &except_choice);
                fflush(stdin);

            }
            switch (except_choice) {
                case 1:
                    printf("deleting resource..... \ready to delete in  1 minutes");
                    set_time(player, 1, state[choice - 1], 60);
                    player->resources_generators[state[choice - 1]].status = DELETING;
                    save_user(player);
                sleep(3);

                    break;
                case 2:
                    printf("process is cancelled");
                sleep(3);

                    break;
            }
        }
    }
}

#endif
