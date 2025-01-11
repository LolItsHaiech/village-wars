#ifndef ADD_RESOURCE_H
#define ADD_RESOURCE_H
#include<stdio.h>

#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
#include "printboard_resource.h"

#include "set_time.h"
#include "number_of_resources.h"
void add_new_resources(user* player)
{int choic,i,return_back=0;

while(return_back==0)
   {        system("cls");

       int number_resources, choic,i,count_resource[3]={0,0,0},empty_resource, state[6]={0,0,0,0,0,0};
	number_resources=number_resource(player,state,count_resource);

    switch(number_resources) {
        case 0 ... 5:
        	empty_resource=find_resource(player);
    	show_resource(count_resource);
            printf("witch source do you need to add?\n1_stone resource\n2_  wood resource\n3_ food resource\n4_  return back");
            scanf("%d",&choic);
            while(choic<1||choic>4)
              {  printf("your choic is incorect try again\n");
        system("cls");

            	show_resource(count_resource);
                scanf("%d",&choic);
               }
            if(choic==4)
              {return_back=1;
            break;}
          switch((Resouce)(choic))
		  {

           	case WOOD:


              printf("add wood resource is starting finish time 2 minute later\n");

           		player->resources_generators[empty_resource].lvl=1;
           		player->resources_generators[empty_resource].resource=WOOD;
          	set_time(player,1,empty_resource,120);
          	player->resources_generators[empty_resource].status=adding;

          	collect_source(player,empty_resource,WOOD,1);
          	save_user(player);
break;
 	        case FOOD:
                              printf("add food resource is starting finish time 2 minute later\n");

              	player->resources_generators[empty_resource].lvl=1;
              	player->resources_generators[empty_resource].resource=FOOD;
          	set_time(player,1,empty_resource,120);
          	player->resources_generators[empty_resource].status=adding;
          	collect_source(player,empty_resource,FOOD,1);
          	save_user(player);


 			  break;
 	        case STONE:
            printf("add stone resource is starting finish time 2 minute later\n");

 	            player->resources_generators[empty_resource].lvl=1;
 	            player->resources_generators[empty_resource].resource=STONE;
          	set_time(player,1,empty_resource,120);
          	player->resources_generators[empty_resource].status=adding;
          	collect_source(player,empty_resource,STONE,1);
                          	save_user(player);



          }
 
 
       default :
       	  printf("your village has  resource_stone %d resource_wood %dresource_food %d\n",count_resource[0],count_resource[1],count_resource[2]);
         printf(" village currently has 6 resources.therefore,it not possible to create a new resource! ");
         return_back=1;
          }
    }
}
#endif