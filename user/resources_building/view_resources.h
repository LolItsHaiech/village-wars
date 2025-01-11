#ifndef VIEW_RESOURCE_H
#define VIEW_RESOURCE_H
#include<stdio.h>
#include <time.h>
#include "../../file_management.h"
#include "../user.h"
#include "printboard_resource.h"


//todo arrname
void view_resources(user *player) {
    int state[6] = {0, 0, 0, 0, 0, 0}, counter_resources[6] = {0, 0, 0, 0, 0, 0};
    int return_back = 0, choice;
    int i, number_resources = 0;
    for (i = 0; i < 6; i++)
        if (player->resources_generators[i].lvl != 0 || player->resources_generators[i].status == DELETING) {
            number_resources++;
            state[number_resources] = i;
        }
    puts("view resources\n\tresources\tlevel  production per min\trequset time\tfinish time\tstatus");


    while (return_back == 0) {
        printview_resource(player);
        scanf("%d", &choice);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            printview_resource(player);
            scanf("%d", &choice);
        }
        if (choice == number_resources + 1) {
            return_back = 1;
            break;
        }

        if (1 <= choice && choice <= number_resources) {
            time_t now = time(NULL);
            if (player->resources_generators[state[choice - 1]].status == FINISHED)
                printf("your choice is finished");

            else if (now < player->resources_generators[state[choice - 1]].finishing_time) {
                printf("the time to comlete the process is not over yet");
            } else {
                //todo resorsename .h
                printf("resores %s were successfuly %s",
                       name_resource[(int) player->resources_generators[state[choice - 1]].resource],
                       player->resources_generators[state[choice - 1]].status);
                player->resources_generators[state[choice - 1]].status = FINISHED;
                player->resources_generators[state[choice - 1]].finishing_time = now;
                save_user(player);
            }
        }
    }
}


#endif
