
#ifndef STORAGE_PER_MIN_H
#define STORAGE_PER_MIN_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
void collect_source(user *player,enum Resouce  resource,int state,int level)
{switch(resource)
  {
    case WOOD:
      player->resources_generators[state].collect_rate = wood_rate_per_minute[level];
      break;


    case   STONE:
        player->resources_generators[state].collect_rate =stone_rate_per_minute[level];
      break;
    case FOOD:
        player->resources_generators[state].collect_rate =food_rate_per_minute[level];
break;










   }
   save_user(player);


}
#endif //STORAGE_PER_MIN_H
