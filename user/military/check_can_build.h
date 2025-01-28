#ifndef CHECK_CAN_UP_H
#define CHECK_CAN_UP_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "../../file_management.h"


int check_can_up(user*player,enum Soldier soldiers_type,int numbers_of_soldiers)
{   system("cls");

    int result = 1, less_wood = 0, less_stone = 0, less_food = 0;





        switch (soldiers_type) {
            case WARRIOR:
                if (player->resources.wood_count < warrior_requirements.wood*numbers_of_soldiers || player->resources.stone_count <
                    warrior_requirements.stone*numbers_of_soldiers || player->resources.food_count < warrior_requirements.food*numbers_of_soldiers)
                    result = 0;
            less_wood = player->resources.wood_count - warrior_requirements.wood*numbers_of_soldiers;
            less_stone = player->resources.stone_count - warrior_requirements.stone*numbers_of_soldiers ;
            less_food = player->resources.food_count - warrior_requirements.food*numbers_of_soldiers;
                break;
            case RIDER:
                if (player->resources.wood_count < rider_requirements.wood*numbers_of_soldiers || player->resources.stone_count <
                                 rider_requirements.stone*numbers_of_soldiers || player->resources.food_count < rider_requirements.food*numbers_of_soldiers)
                    result = 0;
            less_wood = player->resources.wood_count - rider_requirements.wood*numbers_of_soldiers;
            less_stone = player->resources.stone_count - rider_requirements.stone*numbers_of_soldiers ;
            less_food = player->resources.food_count - rider_requirements.food*numbers_of_soldiers;
            break;
            case ARCHER:

    if (player->resources.wood_count < archer_requirements.wood*numbers_of_soldiers || player->resources.stone_count <
       archer_requirements.stone*numbers_of_soldiers || player->resources.food_count < archer_requirements.food*numbers_of_soldiers)
        result = 0;
            less_wood = player->resources.wood_count -  archer_requirements.wood*numbers_of_soldiers ;
            less_stone = player->resources.stone_count - archer_requirements.stone*numbers_of_soldiers;
            less_food = player->resources.food_count - archer_requirements.food*numbers_of_soldiers;

        }
//todo enum
        if (result) {

            player->resources.food_count = less_food;
            player->resources.wood_count = less_wood;
            player->resources.stone_count = less_stone;
            save_user(player);

        } else {
            printf("you have no enough resources to build soldiers\n");
            if (less_stone < 0)
                printf("you need %d more stone(%d/%d) \n", -less_stone,player->resources.stone_count,player->resources.stone_count-less_stone);
            if (less_wood < 0)
                printf("you need %d more wood(%d/%d)\n", -less_wood,player->resources.wood_count,player->resources.wood_count-less_wood);
            if (less_food < 0)
                printf("you need %d more food(%d/%d)  \n", -less_food,player->resources.food_count,player->resources.food_count-less_food);

       sleep(2);
        }
return result;
}
#endif //CHECK_CAN_UP_H
