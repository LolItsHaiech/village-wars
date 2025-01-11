#ifndef BUILDING_H
#define BUILDING_H
#include<stdio.h>
#include "view_building.h"
#include "add_building.h"
#include "upgrade_building.h"
#include "delete_building.h"
#include "printboard_resource.h"
#include <stdlib.h>
int building_ui(user* player)
{
    enum choice {view_buildings=1,add_buildings,upgrade_buildings,delete_buildings} ;
    int return_back=0,main_choice;
    while(return_back==0)
    {
        system("cls");
        printf("building:\n  1_ view building\n  \n  2_ add new building\n  3_ update building\n  4_ delete building\n  5_ return back");

        scanf("%d",&main_choice);
        if(main_choice==5)
          {return_back=1;
        break;}
        switch((choice)main_choice)
        {case view_buildings:
            view_building(player);
            break;



            case add_buildings:
                add_new_building(player);
            break;

            case upgrade_buildings:
                upgrade_building(player);
                          break;
            case delete_buildings:
                delete_building(player);
            break;


            default :
              printf("your choice incorect please try again\n");

           }
    }
}
#endif //BUILDING_H
