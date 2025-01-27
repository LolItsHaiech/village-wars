#ifndef VIEW_RESOURCE_H
#define VIEW_RESOURCE_H
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "printboard_resource.h"
#include "production_per_min.h"
#include "../user.h"
#include "../../headers/constants.h"
#include <unistd.h>

inline void view_resources(user *player) {


    while (true) {
        int state[6] = {-1, -1, -1, -1, -1, -1}, i, number_resources = 0, choice;

        system("cls");

        for (i = 0; i < 6; i++)
            if (player->resources_generators[i].lvl != 0) {
                state[number_resources] = i;
                number_resources++;

            }

        if (number_resources == 0) {
            printf("your village dont have any resources\n");
            printf("Press <Enter> to continue...\n");
            getchar();
            break;
        }
        printf("view resources\n\tresources\tlevel\tproduction per min\trequset_time\t\tfinish_time\tstatus");
        printview_resource(player);
        scanf("%d", &choice);
        fflush(stdin);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            sleep(2);
            system("cls");

            printview_resource(player);
            scanf("%d", &choice);
            fflush(stdin);

        }
        if (choice == number_resources + 1)
            break;

        if (1 <= choice && choice <= number_resources) {
            time_t now = time(NULL);
            if (player->resources_generators[state[choice - 1]].status == DEFAULT)
                printf("your choice is finished\n");
            else if (now < player->resources_generators[state[choice - 1]].finishing_time)
                printf("the time to complete the process is not over yet\n");
            else {
                printf("resource %s was successfully %s\n",
                       name_resource[(int) player->resources_generators[state[choice - 1]].resource],
                       status_construct[(int) player->resources_generators[state[choice - 1]].status]);
                //todo switch
                if (player->resources_generators[state[choice - 1]].status == ADDING)
                    collect_source(player,player->resources_generators[state[choice - 1]].resource ,state[choice - 1] , 1);

                if (player->resources_generators[state[choice - 1]].status == DELETING)
                    player->resources_generators[state[choice - 1]].lvl = 0;
                else if (player->resources_generators[state[choice - 1]].status == UPGRADING) {
                    player->resources_generators[state[choice - 1]].lvl++;
                    collect_source(player, player->resources_generators[state[choice - 1]].resource, state[choice - 1],
                                   player->resources_generators[state[choice - 1]].lvl);
                }
                player->resources_generators[state[choice - 1]].status = DEFAULT;
                player->resources_generators[state[choice - 1]].finishing_time = now;
                save_user(player);
            }
sleep(3);
        }
    }
}

#endif
