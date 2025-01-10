#ifndef ADD_BUILDING_H
#define ADD_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
#include "printboard_resource.h"
#include "check_up_building.h"
#include "set_time.h"
#include "number_of_building.h"
#include "capcity.h"
void add_new_building(user* player)
{int  return_back=0;
  //todo enum choice
while(return_back==0)
   {
       int choic,numbers_building,count_building[4]={0,0,0,0},state[6]={0,0,0,0,0,0},empty_building;
	numbers_building=number_buildings(player,state,count_building);


    switch(numbers_building) {
        case 0 ... 5:
        system("cls");

            show_building(count_building);
              printf("witch building do you need to add?\n1_wood_warehouse\n2_  food_warehouse\n3_ stone_warehouse\n4_ military_house  \n5_ return back");
            scanf("%d",&choic);
            while(choic<1||choic>5)
              {  printf("your choic is incorect try again\n");
              system("cls");
            	show_building(count_building);

            printf("witch building do you need to add?\n1_wood_warehouse\n2_  food_warehouse\n3_ stone_warehouse\n4_ military_house  \n5_ return back");
                 scanf("%d",&choic);
               }
           if (choic==5)
             {return_back=1;
           break;}
          switch((Buildings)choic)
		  {        system("cls");

            empty_building =find_Buildings(player);
           	case WOOD_STORAGE:              printf("add woodstorage building is starting finish time 3 minute later\n");
           		player->buildings[empty_building].lvl=1;
           		player->buildings[empty_building].building_type=WOOD_STORAGE;

          	set_time(player,2,empty_building,180);
          	player->buildings[empty_building].status=adding;
          	capcity(player,WOOD_STORAGE,empty_building,1);
          	save_user(player);

 			  break;
 		
 	        case FOOD_STORAGE:
                                printf("add foodstorage building is starting finish time 3 minute later\n");
              	player->buildings[empty_building].lvl=1;


              	player->buildings[empty_building].building_type=FOOD_STORAGE;
          	      	set_time(player,2,empty_building,180);

          	player->buildings[empty_building].status=adding;
          	capcity(player,FOOD_STORAGE,empty_building,1);
          	save_user(player);

 			  break;
 	        case STONE_STORAGE:
                                printf("add stonestorage building is starting finish time 3 minute later\n");
 	            player->buildings[empty_building].lvl=1;

 	            player->buildings[empty_building].building_type=STONE_STORAGE;
          	set_time(player,2,empty_building,180);
          	player->buildings[empty_building].status=adding;
          	capcity(player,STONE_STORAGE,empty_building,1);
          	save_user(player);

 	           case BARRACK:

                 check_up_building(player,BARRACK,empty_building,0);

                 if(player->buildings[empty_building].lvl==1)
                   {	player->buildings[empty_building].building_type=BARRACK;
          	    capcity(player,BARRACK,empty_building,1);

 	                player->buildings[empty_building].lvl=1;
          	player->buildings[empty_building].status=adding;
                 	save_user(player);

}

 		      break;
 		    default:  
			 return_back=1;
			 break; 
          }
 
 
       default :
         system("cls");
            show_building(count_building);
         printf("your village currently has 6 building.therefore,it not possible to create a new building! ");
         return_back=1;
          }


    }
}
#endif