#ifndef NUMBER_OF_RESOURCE_H
  #define NUMBER_OF_RESOURCE_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
int find_resource(user *player)
{
  int empty_resource=-1,i;
  for(i=0;i<6;i++)
     {
       if (player->resources_generators[i].lvl==0&&player->resources_generators[i].status==finished)
           empty_resource=i;
     }
  return empty_resource;
}

int number_resource(user *player,int state[],int count_resource[])
    {
  int i,number_resources=0;
  for(i=0;i<6;i++)
      if (player->resources_generators[i].lvl!=0&&player->resources_generators[i].status==finished)
         {
           state[number_resources]=i;
           number_resources++;
           count_resource[player->resources_generators[i].resource]++;
         }
  return number_resources;
}
  #endif