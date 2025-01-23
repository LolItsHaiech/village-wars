#ifndef CHECK_UP_BUILDING_H
#define CHECK_UP_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "set_time.h"
#include "capacity.h"
#include <unistd.h>
//todo enum eeq
inline  void building_requirement(enum Buildings building_type, int level,int req[]) {
    req[1]=0;
    switch (building_type) {
        case FOOD_STORAGE:

        req[0]=food_storage_reqs[level].wood;
        req[2]=food_storage_reqs[level].stone;
        break;
        case WOOD_STORAGE:


       req[0]= wood_storage_reqs[level].wood;
        req[2]= wood_storage_reqs[level ].stone;
        break;
        case STONE_STORAGE:

        req[0]= stone_storage_reqs[level].wood;
        req[2]= stone_storage_reqs[level].stone;
        break;
        case BARRACK:

       req[0]= barrack_reqs[level].wood;
        req[2]=barrack_reqs[level].stone;
       req[1]=barrack_reqs[level].food;
        break;
    }







}
inline void check_up_building(user *player, enum Buildings building_type, int state, int level) {
    system("cls");

    int result = 1, less_wood = 0, less_stone = 0, less_food = 0;

    if (level == 5)
        printf("this building  full upgrade choice another building\n");

    else {
        switch (building_type) {
            case FOOD_STORAGE:
                if (player->resources.wood_count < food_storage_reqs[level ].wood || player->resources.stone_count <
                    food_storage_reqs[level ].stone)
                    result = 0;
                less_wood = player->resources.wood_count - food_storage_reqs[level ].wood;
                less_stone = player->resources.stone_count - food_storage_reqs[level ].stone;
                break;
            case WOOD_STORAGE:

                if (player->resources.wood_count < wood_storage_reqs[level ].wood || player->resources.stone_count <
                    wood_storage_reqs[level ].stone)
                    result = 0;
                less_wood = player->resources.wood_count - wood_storage_reqs[level ].wood;
                less_stone = player->resources.stone_count - wood_storage_reqs[level ].stone;
                break;
            case STONE_STORAGE:
                if (player->resources.wood_count < stone_storage_reqs[level ].wood || player->resources.stone_count <
                    stone_storage_reqs[level ].stone)
                    result = 0;
                less_wood = player->resources.wood_count - stone_storage_reqs[level ].wood;
                less_stone = player->resources.stone_count - stone_storage_reqs[level ].stone;
                break;
            case BARRACK:
                if (player->resources.wood_count < barrack_reqs[level].wood || player->resources.stone_count <
                    barrack_reqs[level].stone || player->resources.food_count < barrack_reqs[level].food)
                    result = 0;
                less_wood = player->resources.wood_count - barrack_reqs[level].wood;
                less_stone = player->resources.stone_count - barrack_reqs[level].stone;
                less_food = player->resources.food_count - barrack_reqs[level].food;
                break;
        }

        if (result) {
            int time_needed = get_time_needed(true, building_type, player->buildings[state].lvl);
            set_time(player, 1, state, time_needed);
           // capacity(player, building_type, state,level);
            player->buildings[state].status = UPGRADING;

            if (building_type == BARRACK) {
                player->resources.food_count = less_food;
                player->buildings[state].is_working = false;
            }
            player->resources.wood_count = less_wood;
            player->resources.stone_count = less_stone;

            if (building_type== BARRACK&&player->buildings[state].lvl== 0) {
                printf("add BARRACK building is starting finish time 10 minute later\n");
                player->buildings[state].lvl= 1;
            }

            else
                printf("upgrade building..... \tready to upgrade in  %d secound  later\n", time_needed);
            save_user(player);
        } else {
            if (player->buildings[state].lvl== 0)
                printf("add barrack  didnt completed  resource not enough\n");

            else
            printf("upgrade didnt completed  resource not enough \n");
            if (less_stone < 0)
                printf("you need %d more stone(%d/%d) \n", -less_stone,player->resources.stone_count,player->resources.stone_count-less_stone);
            if (less_wood < 0)
                printf("you need %d more wood(%d/%d)\n", -less_wood,player->resources.wood_count,player->resources.wood_count-less_wood);
            if (less_food < 0)
                printf("you need %d more food(%d/%d)  \n", -less_food,player->resources.food_count,player->resources.food_count-less_food);
        }
    }
    sleep(3);

}

#endif //CHECK_UP_BUILDING_H
