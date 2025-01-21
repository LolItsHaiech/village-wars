#ifndef CHECK_UP_H
#define CHECK_UP_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "set_time.h"
#include "production_per_min.h"
#include <unistd.h>
inline  void resource_requirements( enum Resource resource, int level,int req[]) {
    switch (resource) {
        //todo?
        case FOOD:


            req[0]= food_reqs[level ].wood;
        req[2]= food_reqs[level ].stone;
        break;
        case WOOD:

            req[0]= wood_reqs[level ].wood;
        req[2]= wood_reqs[level ].stone;
        break;
        case STONE:

            req[0]= stone_reqs[level ].wood;
        req[2]= stone_reqs[level ].stone;
    }




}

inline void check_up_resource(user *player, enum Resource resource, int state, int level) {
    int time_needed, result = 1, less_wood = 0, less_stone = 0;
    system("cls");
    if (level == 5)
        printf("this resource  full upgrade choice another resource\n");
    else {

        switch (resource) {

            case FOOD:
                if (player->resources.wood_count < food_reqs[level - 1].wood || player->resources.stone_count <
                    food_reqs[level - 1].stone)
                    result = 0;

                less_wood = player->resources.wood_count - food_reqs[level - 1].wood;
                less_stone = player->resources.stone_count - food_reqs[level - 1].stone;
            break;
            case WOOD:
                if (player->resources.wood_count < wood_reqs[level - 1].wood || player->resources.stone_count <
                    wood_reqs[level - 1].stone)
                    result = 0;
                less_wood = player->resources.wood_count - wood_reqs[level - 1].wood;
                less_stone = player->resources.stone_count - wood_reqs[level - 1].stone;
                break;
            case STONE:
                if (player->resources.wood_count < stone_reqs[level - 1].wood || player->resources.stone_count <
                    stone_reqs[level - 1].stone)
                    result = 0;
                less_wood = player->resources.wood_count - stone_reqs[level - 1].wood;
                less_stone = player->resources.stone_count - stone_reqs[level - 1].stone;
        }

        if (result) {
            system("cls");
            time_needed = get_time_needed(false, resource, player->resources_generators[state].lvl);
            set_time(player, 1, state, time_needed);
            player->resources_generators[state].status = UPGRADING;
            player->resources.wood_count = less_wood;
            player->resources.stone_count = less_stone;
            printf("upgrade resource..... \tready to upgrade  in %d later\n ", time_needed);

            save_user(player);
        } else {
            system("cls");
            printf("upgrade didnt completed  resource not enough\n ");
            if (less_stone < 0)
                printf("you need %d more stone(%d/%d) \n", -less_stone,player->resources.stone_count,player->resources.stone_count-less_stone);
            if (less_wood < 0)
                printf("you need %d more wood(%d/%d)\n", -less_wood,player->resources.wood_count,player->resources.wood_count-less_wood);

        }
    }
    sleep(3);

}

#endif //CHECK_UP_H
