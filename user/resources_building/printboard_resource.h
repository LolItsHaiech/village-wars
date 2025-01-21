#ifndef PRINTBOARD_RESOURCE
#define PRINTBOARD_RESOURCE

#include <stdio.h>
#include "../../headers/constants.h"
#include "../../utils/time.h"
#include <strings.h>
#include "check_up_building.h"
#include "check_up_resources.h"
inline void printview_resource(user *player) {
    int i, counter = 1;
    printf("resources:");
    for (i = 0; i < 6; i++) {
        if (player->resources_generators[i].lvl != 0) {
              char up_level='\0';
             char finishing_time[32];
             char change_time[32];
            if (player->resources_generators[i].status ==UPGRADING)
                up_level=(char)(player->resources_generators[i].lvl+49);
          if (player->resources_generators[i].status !=DEFAULT) {
              get_date_time(finishing_time, player->resources_generators[i].finishing_time);
              get_date_time(change_time, player->resources_generators[i].change_time);
          }
            else {
                strcpy(finishing_time,"       -     ");strcpy(change_time,"     -    ");
            }
            printf("\n%-2d\t%-12s\t%-12d\t%-8d\t%-15s\t%-15s\t%5s%c\n", counter,
                   name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].lvl, player->resources_generators[i].collect_rate
                   , change_time ,finishing_time,
                   status_construct[(int) player->resources_generators[i].status],up_level);


            counter++;
        }
    }
    printf("%d_return back\n",counter);
    printf("enter number of row to complete process resource after time finishing or return back:\n");
}

inline void printview_building(user *player) {
    int i, counter = 1;
    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0) {
            char up_level='\0';
            char finishing_time[32];
            char change_time[32];
            if (player->buildings[i].status ==UPGRADING)
                up_level=(char)(player->buildings[i].lvl+49);
            if (player->buildings[i].status !=DEFAULT) {
                get_date_time(finishing_time, player->buildings[i].finishing_time);
                get_date_time(change_time, player->buildings[i].change_time);
            }
            else {
                strcpy(finishing_time,"     -        ");strcpy(change_time,"      -      ");
            }
            printf("\n%-2d\t%-15s\t%-15d\t%-15d\t%-15s\t%-15s\t%5s%c\n", counter, name_building[player->buildings[i].building_type],
                   player->buildings[i].lvl, player->buildings[i].storage,
                   change_time, finishing_time,
                   status_construct[(int) player->buildings[i].status],up_level);
            counter++;
        }


    printf("%d_return back\n", counter);
    printf("enter number of row to complete process resource after time finishing  or return back:\n");
}

inline void printboard_delete_up_resource(user *player) {
    int i, counter = 1,resource_req[3]={0,0,0};
    printf("\nresources:   \t level\t\tproduction\twood req up  food req up  stone req up ");
    for (i = 0; i < 6; i++)


        if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT) {
            resource_requirements(player->resources_generators[i].resource,player->resources_generators[i].lvl-1,resource_req);
            printf("\n  %d\t%s\t%d\t%d\t%d\t%d\t%d\n", counter, name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].lvl, player->resources_generators[i].collect_rate,resource_req[0],resource_req[1],resource_req[2]);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting resource or return back:\n");
}

inline void printboard_delete_up_building(user *player) {
    int i, counter = 1,building_req[3]={0,0,0};
    printf("\nbuilding:   \t level\tcapacity\twood req up  food req up  stone req up ");
    for (i = 0; i < 6; i++)

        if (player->buildings[i].lvl != 0 && player->buildings[i].status == DEFAULT) {

           building_requirement(player->buildings[i].building_type,player->buildings[i].lvl-1,building_req);
            printf("\n  %d\t%s\t%d\t%d\t%d\t%d\t%d\n", counter, name_building[player->buildings[i].building_type],
                   player->buildings[i].lvl, player->buildings[i].storage,building_req[0],building_req[1],building_req[2]);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting  bulding or return back:\n");
}


inline void show_building(int count_buildings[]) {
    printf("your village has wood_warehouse %d food_warehouse %d stone_warehouse %d  military_house %d\n",
           count_buildings[0], count_buildings[1], count_buildings[2], count_buildings[3]);
}

inline void show_resource(int count_resource[]) {
    printf("your village has  resource_wood: %d   resource_food:%d  resource_stone:%d\n", count_resource[0],
           count_resource[1], count_resource[2]);
}

inline int print_collectboard(user *player, int state[], time_t now) {
    int i, counter = 1;
    printf("resources");
    for (i = 0; i < 6; i++)
        if (player->resources_generators[i].lvl != 0 && player->resources_generators[i].status == DEFAULT) {
            state[counter - 1] = i;
              int elpased = now - player->resources_generators[i].finishing_time;
              int number_of_collectnow = (((elpased)) *
                                       player->resources_generators[i].collect_rate)/60;

            char finishing_time[32];
            get_date_time(finishing_time,player->resources_generators[state[counter - 1]].finishing_time);

            printf("\n%4d\t%12s\t%5d\t%s\t%14d\n", counter, name_resource[(int) player->resources_generators[i].resource],
                   player->resources_generators[i].collect_rate
                   , finishing_time, number_of_collectnow);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to collect   resource after time finishing  or return back:\n");
    return counter - 1;

}
inline void print_storage(user* player,int capacity[]) {
    printf("\nstorage resources: wood:%d/%d\tfood:%d/%d\tstone:%d/%d",player->resources.wood_count,capacity[0],player->resources.food_count,capacity[1],player->resources.stone_count,capacity[2]);



}
inline void print_power_of_village(user *player) {
int attack,defence;
    defence=player->soldiers_count.archer*4+player->soldiers_count.warrior*5+player->soldiers_count.rider*7;
    attack=player->soldiers_count.archer*15+player->soldiers_count.warrior*10+player->soldiers_count.rider*20;
    printf("\ndefence power of village:%d\tattack power of village%d",defence,attack );
}
inline  int print_soldiers_creating(user *player, int state[]) {
    int i, counter = 0;
for (i = 0; i < 12; i++) {
    char finishing_time[50];
    get_date_time(finishing_time, player->soldiers[i].finishing_time);
    char change_time[50];
    get_date_time(change_time, player->soldiers[i].change_time);

    if (player->soldiers[i].number_soldiers!=0) {

        printf("soldier  name:%s\tnumbers :%d\t change time:%s\tfinishing time:%s\t",name_soldiers[(int)player->soldiers[i].soldier],player->soldiers->number_soldiers,change_time,finishing_time);
         state[counter] =i;
        counter++;
    }
    }
    return counter;

}
inline void printview_military(user *player) {
    int i, counter = 1;
    printf(" number of military");

    printf(" number archer:%d",player->soldiers_count.archer);
    printf(" number rider:%d",player->soldiers_count.rider);
    printf(" number warior:%d",player->soldiers_count.warrior);
    print_power_of_village(player);

}
inline void print_add_soldier(user *player,int state[],int numbers_military) {
    printf("choose your barrack building or return back\n:");
    if (state[0]!=-1 )
        printf("1_ barrack building  level =%d the rate of creating soldiers per minute:%d,number of bulidable soldiers now:%d",player->buildings[state[0]].lvl,player->buildings[state[0]].lvl+1,player->buildings[state[0]].storage);
    if (state[1]!=-1 )
        printf("\n2_barrack building  level =%d the rate of creating soldiers per minute:%d,number of bulidable soldiers now:%d",player->buildings[state[1]].lvl,player->buildings[state[1]].lvl+1,player->buildings[state[1]].storage);
        if (state[2]!=-1 )
            printf("\n2_barrack building  level =%d the rate of creating soldiers per minute:%d,number of bulidable soldiers now:%d",player->buildings[state[2]].lvl,player->buildings[state[2]].lvl+1,player->buildings[state[2]].storage);



    printf("\n%d_retuen back:\n",numbers_military+1);

}

inline  int print_check_can_creating_soldier(user *player,int level,int requirment_ ) {





}
#endif
