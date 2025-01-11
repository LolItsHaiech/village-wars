#ifndef CHECK_UP_BUILDING_H
#define CHECK_UP_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
#include "set_time.h"
#include "capcity.h"

void check_up_building(user* player,enum Buildings building_type ,int state,int level)
{
  system("cls");

  int result=1,less_wood=0,less_stone=0,less_food=0;

  if(level==5)
    printf("this building  full upgrade choice another building\n");


  else
    {
      switch(building_type)
        {
           case FOOD_STORAGE:
             if(player->resources.wood_count<food_storage_reqs[level-1].wood||player->resources.stone_count<food_storage_reqs[level-1].stone)
               result=0;
             less_wood=player->resources.wood_count-food_storage_reqs[level-1].wood;
             less_stone=player->resources.stone_count-food_storage_reqs[level-1].stone;
             break;
           case WOOD_STORAGE:

              if(player->resources.wood_count<wood_storage_reqs[level-1].wood||player->resources.stone_count<wood_storage_reqs[level-1].stone)
                 result=0;
              less_wood=-player->resources.wood_count-wood_storage_reqs[level-1].wood;
              less_stone=-player->resources.stone_count-wood_storage_reqs[level-1].stone;
              break;
           case STONE_STORAGE:
              if(player->resources.wood_count<stone_storage_reqs[level-1].wood||player->resources.stone_count<stone_storage_reqs[level-1].stone)
                    result=0;
              less_wood=player->resources.wood_count-stone_storage_reqs[level-1].wood;
              less_stone=player->resources.stone_count-stone_storage_reqs[level-1].stone;
              break;
           case BARRACK:
              if(player->resources.wood_count<barrack_requirement[level].wood||player->resources.stone_count<barrack_requirement[level].stone||player->resources.food_count<barrack_requirement[level].food)
              result=0;
              less_wood=player->resources.wood_count-barrack_requirement[level].wood;
              less_stone=player->resources.stone_count-barrack_requirement[level].stone;
              less_food=player->resources.food_count-barrack_requirement[level].food;
              break;
        }

      if(result)
        {
          int time_needed=get_time_needed(player,1,building_type, player->buildings[state].lvl);
          set_time(player,1,state,time_needed);
          player->buildings[state].lvl++;
          capcity(player,building_type,state,level+1);
          player->buildings[state].status=upgrading;
          save_user(player);
          if(building_type==BARRACK)
            player->resources.food_count=less_food;
          player->resources.wood_count=less_wood;
          player->resources.stone_count=less_stone;
          save_user(player);
          if(player->buildings[state].lvl!=1)
            printf("upgrade resource..... \tready to upgrade in  %d  later\n",time_needed);
          else if(player->buildings[state].lvl==1)
            printf("add BARRACK building is starting finish time 10 minute later\n");
        }
      else
        {
          printf("upgrade didnt complated  resource not enough ");
          if(less_stone<0)
            printf("you need %d  more stone \n",less_stone);
          if(less_wood<0)
            printf("you need %d  more wood \n",less_wood);
          if(less_food<0)
            printf("you need %d  more food  \n",less_food);
        }
  }
}

#endif //CHECK_UP_BUILDING_H
