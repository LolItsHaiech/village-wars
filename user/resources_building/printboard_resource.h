#ifndef PRINTBOARD_RESOURCE
#define PRINTBOARD_RESOURCE

#include <stdio.h>
#include "../../headers/constants.h"
#include "../../utils/time.h"


inline void printview_resource(user *player) {
    int i, counter = 1;
    printf("resources");
    for (i = 0; i < 6; i++) {
        if (player->resources_generators[i].lvl != 0) {

            char finishing_time[32];
            get_date_time(finishing_time, &player->resources_generators[i].finishing_time);
            char change_time[32];
            get_date_time(change_time, &player->resources_generators[i].change_time);

            printf("\n  %-8d\t%-8s\t%-8d\t%-8d\t%-14s\t%-14s\t%-5s\n", counter,
                   name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].lvl, player->resources_generators[i].collect_rate
                   , finishing_time, change_time,
                   status_construct[(int) player->resources_generators[i].status]);


            counter++;
        }
    }
    printf("%d_return back\n", counter);
    printf("enter number of row to complete process resource after time finishing or return back:");
}

inline void printview_building(user *player) {
    int i, counter = 1;
    printf("building");
    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0) {

            char finishing_time[50];
            get_date_time(finishing_time, &player->buildings[i].finishing_time);
            char change_time[50];
            get_date_time(change_time, &player->buildings[i].change_time);

            printf("\n  %d\t%s\t%d\t%d\t%s\t%s\t%s\n", counter, name_building[player->buildings[i].building_type],
                   player->buildings[i].lvl, player->buildings[i].storage,
                   change_time, finishing_time,
                   status_construct[(int) player->buildings[i].status]);
            counter++;
        }


    printf("%d_return back\n", counter);
    printf("enter number of row to complete process resource after time finishing  or return back:");
}

inline void printboard_delete_up_resource(user *player) {
    int i, counter = 1;
    printf("resources:");
    for (i = 0; i < 6; i++)
        if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT) {
            printf("\n  %d\t%s\t%d\t%d\n", counter, name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].lvl, player->resources_generators[i].collect_rate);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting resource or return back:\n");
}

inline void printboard_delete_up_building(user *player) {
    int i, counter = 1;
    printf("building:");\
    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0 && player->buildings[i].status == DEFAULT) {
            printf("\n  %d\t%s\t%d\t%d\n", counter, name_building[player->buildings[i].building_type],
                   player->buildings[i].lvl, player->buildings[i].storage);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting  bulding or return back:\n");
}

inline void show_building(int count_buildings[]) {
    printf("your village has wood_warehouse %d food_warehouse %d stone_warehouse %d  military_house %d\n",
           count_buildings[0], count_buildings[1], count_buildings[2], count_buildings[3]);
}

inline void show_resource(int count_resource[]) {
    printf("your village has  resource_wood: %d   resource_food:%d  resource_stone:%d\n", count_resource[0],
           count_resource[1], count_resource[2]);
}

inline int print_collectboard(user *player, int state[], time_t now) {
    int i, counter = 1;
    printf("resources");
    for (i = 0; i < 6; i++)
        if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT) {
            state[counter - 1] = i;
            int number_of_collectnow = ((now - player->resources_generators[i].finishing_time)) *
                                       player->resources_generators[i].collect_rate;
            //todo   print time

            printf("\n  %d\t%s\t%d\t%lld\t%d\n", counter, name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].collect_rate
                   , now - player->resources_generators[i].finishing_time, number_of_collectnow);
            counter++;
        }
    printf("%d_return back\n", counter);
    printf("enter number of row to collect   resource after time finishing  or return back:");
    return counter - 1;
}

#endif
