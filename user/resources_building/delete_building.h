#ifndef DELETE_BUILDING_H
#define DELETE_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
#include "set_time.h"
#include "number_of_building.h"
#include "printboard_resource.h"
void delete_building(user* player)
{
    system("cls");
    int choice,return_back=0,exept_choice;
    while(return_back==0)
      {
        int state[6]={0,0,0,0,0,0},number_building,count_building[6]={0,0,0,0,0,0};
        number_building=number_buildings(player,state,count_building);
        if(number_building==0)
             {
                  printf("you have no building to delete");
          		  return_back=1;
      			  break;
	 		 }
   		printboard_delete_up_building( player);
   		scanf("%d",&choice);
  	    while(1>choice||choice>number_building+1)
       		{
              printf("your choice is incorect try again");
              system("cls");
              printboard_delete_up_building(player);
              scanf("%d",&choice);
            }
   		if(choice==number_building+1)
   			{
       			return_back=1;
       			break;
	   		}
   		if(1<=choice&&choice<=number_building)
			{
       			system("cls");
    			 printf("are you sure to delete this building %s level %d ?\n1.yes\n2.no",name_building[(int)player->buildings[state[choice-1]].building_type],player->buildings[state[choice-1]].lvl);
     			 scanf("%d",&exept_choice);
    			 while(exept_choice!=1&&exept_choice!=2)
        			 {
                        printf("your choice is incorect try again");
         				scanf("%d",&exept_choice);
			         }
     			 switch (exept_choice)
	 				 {
	   					case 1:
	     				  system("cls");
						  printf("deleting building..... \rready to delete in  2 minutes");
      					  player->buildings[state[choice-1]].lvl=0;
        				  set_time(player,2,state[choice-1],120);
       					  player->buildings[state[choice-1]].status=deleting;
                          save_user(player);
	                      break;

						case 2:
                            printf("process is cancelled");
							break;
                 }
            }
      }
}

#endif