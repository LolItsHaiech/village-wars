#ifndef CHECK_UP_H
#define CHECK_UP_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "set_time.h"
#include "production_per_min.h"

int check_up_resource(user *player, enum Resouce resource, int state, int level) {
    int time_needed, result = 1, less_wood = 0, less_stone = 0;

    system("cls");

    if (level == 5) {
        printf("this resource  full upgrade chice another resource\n");
    } else {
        switch (resource) {
            case FOOD:

                if (player->resources.wood_count < food_reqs[level - 1].wood || player->resources.stone_count <
                    food_reqs[level - 1].stone)
                    result = 0;
                less_wood = -player->resources.wood_count - food_reqs[level - 1].wood;


                less_stone = -player->resources.stone_count - food_reqs[level - 1].stone;

            case WOOD:

                if (player->resources.wood_count < wood_reqs[level - 1].wood || player->resources.stone_count <
                    wood_reqs[level - 1].stone)
                    result = 0;
                less_wood = player->resources.wood_count - wood_reqs[level - 1].wood;

                less_stone = player->resources.stone_count - wood_reqs[level - 1].stone;


            case STONE:

                if (player->resources.wood_count < stone_reqs[level - 1].wood || player->resources.stone_count <
                    stone_reqs[level - 1].stone)
                    result = 0;
                less_wood = player->resources.wood_count - stone_reqs[level - 1].wood;


                less_stone = player->resources.stone_count - stone_reqs[level - 1].stone;
        }

        if (result) {
            time_needed = get_time_needed(player, 1, resource, player->resources_generators[state].lvl);
            set_time(player, 1, state, time_needed);
            player->resources_generators[state].lvl++;

            collect_source(player, state, resource, level + 1);
            player->resources_generators[state].status = upgrading;

            player->resources.wood_count = less_wood;
            player->resources.stone_count = less_stone;
            printf("upgrade resource..... \tready to upgrade  in %d later\n ", time_needed);
            //todo print time
            //get_date_time(temp,now+time_needed);
            save_user(player);
        } else {
            printf("upgrade didnt complated  resource not enough ");
            if (less_stone < 0)
                printf("you need %d  more stone \n", -1 * less_stone);
            if (less_wood < 0)
                printf("you need %d  more wood \n", -1 * less_wood);
            return result;
        }
    }
}

#endif //CHECK_UP_H
