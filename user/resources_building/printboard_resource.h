#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
void printview_resource(user* player)
{
  int i,counter=1;
  printf("resources");
  for(i=0;i<6;i++)
     {
       if (player->resources_generators[i].lvl!=0||player->resources_generators[i].status==deleting)
         {
//todo   pint time
            printf("\n  %d\t%s\t%d\t%d\t%d\t%d\t%s\n",counter, name_resource[(int)  player->resources_generators[i].resource],
                                                         player->resources_generators[i].lvl,    player->resources_generators[i].collect_rate
                                                                   ,  player->resources_generators[i].change_time,  player->resources_generators[i].finishing_time,status_construct[(int)  player->resources_generators[i].status]);
            counter++;
        }
    }
  printf("%d_return back\n",counter);
  printf("enter number of row to complate prosses  resouceor after time finishing  or return back:");
}
void printview_building(user* player)
{
    int i,counter=1;
    printf("building");
    for(i=0;i<6;i++)
        if (player->buildings[i].lvl!=0||player->buildings[i].status==deleting)
           {
             printf("\n  %d\t%s\t%d\t%d\t%d\t%d\t%s\n",counter, name_building[player->buildings[i].building_type],
                                                       player->buildings[i].lvl,player->buildings[i].storage,
                                                                   player->buildings[i].change_time,player->buildings[i].finishing_time,status_construct[(int)player->buildings[i].status]);
             counter++;
           }

    printf("%d_return back\n",counter);
    printf("enter number of row to complate prosses  resouceor after time finishing  or return back:");
}
void printboard_delete_up_resource(user* player)
{
    int i,counter=1;
    printf("resources:");
    for(i=0;i<6;i++)
        if (player->resources_generators[i].lvl!=0&&player->resources_generators[i].status==finished)
            {
              printf("\n  %d\t%s\t%d\t%d\n",counter,name_resource[(int)player->resources_generators[i].resource],player->resources_generators[i].lvl,player->resources_generators[i].collect_rate );
              counter++;
            }

    printf("%d_return back\n",counter);
    printf("enter number of row to deleting  resouce or return back:\n");
}
void printboard_delete_up_building(user* player)
{
    int i,counter=1;
     printf("building:");
    for(i=0;i<6;i++)
        if (player->buildings[i].lvl!=0&&player->buildings[i].status==finished)
          {
                printf("\n  %d\t%s\t%d\t%d\n",counter,name_building[player->buildings[i].building_type],player->buildings[i].lvl,player->buildings[i].storage);
                counter++;
          }

    printf("%d_return back\n",counter);
    printf("enter number of row to deleting  bulding or return back:\n");
}
void show_building( int count_buildings[])
{
  printf("your village has wood_warehouse %d food_warehouse %d stone_warehouse %d  military_house %d\n",count_buildings[0],count_buildings[1],count_buildings[2],count_buildings[3]);
}
void show_resource(int count_resource[])
{
    printf("your village has  resource_stone %d resource_wood %dresource_food %d\n",count_resource[0],count_resource[1],count_resource[2]);
  }
int print_collectboard(user* player,int state[],time_t now)
{
  int i,counter=1;
  printf("resources");
  for(i=0;i<6;i++)
      if (player->resources_generators[i].lvl!=0&&player->resources_generators[i].status==finished)
        {state[counter-1]=i;
              int number_of_collectnow=((now-player->resources_generators[i].finishing_time)/CLOCKS_PER_SEC)*player->resources_generators[i].collect_rate;
            //todo   pint time
            printf("\n  %d\t%s\t%d\t%d\t%d\n",counter, name_resource[(int)player->resources_generators[i].resource],
                                                      player->resources_generators[i].collect_rate
                                                                   ,now-player->resources_generators[i].finishing_time,number_of_collectnow);
            counter++;
        }
  printf("%d_return back\n",counter);
  printf("enter number of row to collect   resourceo after time finishing  or return back:");
  return counter-1;
  }
