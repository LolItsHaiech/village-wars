#ifndef COLLECTING_RESOURCE_H
#define COLLECTING_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include "printboard_resource.h"
#include "set_time.h"

#include "max_capacity.h"

inline void collecting_resource(user *player) {
    system("cls");
    int choice, number_resources, capacity[3] = {0, 0, 0}, state[6] = {0, 0, 0, 0, 0, 0};
    while (true) {
        max_capacity(player, capacity);
        //todo print wood count max capacty
        time_t now = time(0);
        number_resources = print_collectboard(player, state, now);
        if (number_resources == 0) {
            printf("you have no finished resource to collect source");
            break;
        }
        printview_resource(player);
        scanf("%d", &choice);
        while (1 > choice || choice > number_resources + 1) {
            printf("your choice is incorect try again");
            printview_resource(player);
            scanf("%d", &choice);
        }
        if (choice == number_resources + 1)
            break;
        long long int elapsed_time = (now - player->resources_generators[state[choice - 1]].finishing_time);
        switch (player->resources_generators[state[choice - 1]].resource) {

            //todo?
            case WOOD:
                player->resources.wood_count += (
                    elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                if (player->resources.wood_count > capacity[0])
                    player->resources.wood_count = capacity[0];
                break;
            case STONE:
                player->resources.stone_count += (
                    elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                if (player->resources.stone_count > capacity[1])
                    player->resources.stone_count = capacity[1];
                break;
            case FOOD:
                player->resources.food_count += (
                    elapsed_time * player->resources_generators[state[choice - 1]].collect_rate) / 60;
                if (player->resources.food_count > capacity[2])
                    player->resources.food_count = capacity[2];
        }
        save_user(player);
    }
}

#endif
