
#ifndef CAPCITY_H
#define CAPCITY_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
void capcity(user *player,enum Buildings building_type  ,int state,int level)
{switch(building_type)
    {
  case  FOOD_STORAGE:
      player->buildings[state].storage =food_storage_capacity[level];
      break;
   case  WOOD_STORAGE:
    player->buildings[state].storage =wood_storage_capacity[level];
    break;
    case  STONE_STORAGE:
        player->buildings[state].storage =stone_storage_capacity[level];

       break;
    case  BARRACK:
 player->buildings[state].storage=level+1;
 break;
  }
    save_user(player);



}
#endif //CAPCITY_H
