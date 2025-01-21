#ifndef COLLECTING_RESOURCE_H
#define COLLECTING_RESOURCE_H
#include<stdio.h>

#include <stdlib.h>
#include <time.h>
#include "printboard_resource.h"

#include <unistd.h>

#include "max_capacity.h"

inline void collecting_resource(user *player) {
    system("cls");
 while (true) {
    int choice, number_resources=0,i, capacity[3] = {0, 0, 0}, state[6] = {0, 0, 0, 0, 0, 0};

        //todo number
        for (i = 0; i<6; i++)
            if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT)
                    number_resources++;
                if (number_resources==0) {
                    printf("you have no finished resource to collect source");
                    sleep(3);
                    break;
                }



                max_capacity(player, capacity);

            print_storage(player, capacity);
              time_t now = time(0);
                number_resources = print_collectboard(player, state, now);

                scanf("%d", &choice);
                fflush(stdin);

                while (1 > choice || choice > number_resources + 1) {
                    printf("your choice is incorect try again");
                    printview_resource(player);
                    scanf("%d", &choice);
                    fflush(stdin);

                }
                if (choice == number_resources + 1)
                    break;
                 int elapsed_time = (now - player->resources_generators[state[choice - 1]].finishing_time);
                switch (player->resources_generators[state[choice - 1]].resource) {

                    //todo?
                    case WOOD:
                        player->resources.wood_count += (
                            elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                    if (player->resources.wood_count > capacity[0])
                        player->resources.wood_count = capacity[0];
                    player->resources_generators[state[choice - 1]].finishing_time = now;
                    save_user(player);
                    break;


                    case FOOD:
                        player->resources.food_count += (
                            elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                    if (player->resources.food_count > capacity[1])
                        player->resources.food_count = capacity[1];
                    player->resources_generators[state[choice - 1]].finishing_time = now;
                    save_user(player);
                    break;
                     case STONE:
                        player->resources.stone_count += (
                            elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                    if (player->resources.stone_count > capacity[2])
                        player->resources.stone_count = capacity[2];
                    player->resources_generators[state[choice - 1]].finishing_time = now;
                    save_user(player);
                    break;

                }
            sleep(3);
                save_user(player);

            }
    }


#endif
