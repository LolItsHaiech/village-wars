#ifndef VIEW_BUILDING_H
#define VIEW_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"
#include"../../utils/print_time.h"
#include "printboard_resource.h"
//todo arr name

// todo arr
//todo arr name
 void view_building(user *player)
 { system("cls");
   int state[6]={0,0,0,0,0,0},count_buildings[6]={0,0,0,0,0,0};
   int return_back=0,choice;
printf("view building\n\tbuild\tlevel  \tsave source\trequset time\tfinish time\tstatus");
 while(return_back==0)
 { int i,numbers_building=0;
   for(i=0;i<6;i++)
            if (player->buildings[i].lvl!=0||player->buildings[i].status==deleting)
               {numbers_building++;
              state[numbers_building]=i;

                }

printview_building(player);
       scanf("%d",&choice);
  while(1>choice||choice>numbers_building+1)
  {printf("your choice is incorect try again");
   system("cls");

printview_building(player); ;
   scanf("%d",&choice);
  }
  if(choice==numbers_building+1)
  {
   return_back=1;
   break;
  }
  if(1<=choice&&choice<=numbers_building)
  {time_t now=time(NULL);
    if(player->buildings[state[choice-1]].status==finished)
       printf("your choice is finished");
   else if(now<player->buildings[state[choice-1]].finishing_time)
   {

    printf("the time to comlete the process is not over yet");

   }
   //todo build name .h
   //save this process
   printf("build %s were successfuly %s",name_building[(int)player->buildings[state[choice-1]].building_type], player->buildings[state[choice-1]].status);
    player->buildings[state[choice-1]].status=4;
   player->buildings[state[choice-1]].finishing_time=now;
   save_user(player);

      	      }

 }
}
}


#endif