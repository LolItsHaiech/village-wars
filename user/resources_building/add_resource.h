#ifndef ADD_RESOURCE_H
#define ADD_RESOURCE_H
#include<stdio.h>

#include"../user.h"
#include <stdlib.h>
#include "set_time.h"
#include "number_of_resources.h"
#include "production_per_min.h"
#include <unistd.h>

inline void add_new_resources(user *player) {
    int choice,i, return_back = 0,exist_building[4]={0,0,0,0};
    //todo is exist build
    for (i=0; i<6; i++)
        if (player->buildings[i].lvl!=0&&player->buildings[i].status==DEFAULT)
            exist_building[(int)player->buildings[i].building_type]=1;

    while (return_back == 0) {
        system("cls");
        int number_resources, count_resource[3] = {0, 0, 0}, empty_resource, state[6] = {-1, -1, -1, -1, -1, -1};
        number_resources = number_resource(player, state, count_resource);

        switch (number_resources) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                empty_resource = find_resource(player);
                show_resource(count_resource);
                printf("Resource   \tproduction per min \t  request time  "
                       "\n1_ wood resource\t\t15\t\t2\n2_ food resource\t\t35\t\t2\n3_ stone resource\t\t10\t\t2\n4_return back\n"

                     );
                scanf("%d", &choice);
                fflush(stdin);
                while (choice < 1 || choice > 4) {
                    printf("your choic is incorect try again\n");
                    system("cls");
                    show_resource(count_resource);
                    printf("Resource   \tproduction per min \t  request time  "
                    "\n1_ wood resource\t\t15\t\t2\n2_ food resource\t\t35\t\t2\n3_ stone resource\t\t10\t\t2\n4_return back\n"

                    );
                    scanf("%d", &choice);
                    fflush(stdin);
                }
                if (choice == 4) {
                    return_back = 1;
                    break;
                }
                switch ((enum Resource) (choice-1)) {
                    case WOOD: if (exist_building[0]==1){
                        printf("add wood resource is starting finish time 2 minute later\n");
                        player->resources_generators[empty_resource].lvl = 1;
                        player->resources_generators[empty_resource].resource = WOOD;
                        set_time(player, 1, empty_resource, 120);
                        player->resources_generators[empty_resource].status = ADDING;
                        player->resources_generators[empty_resource].collect_rate=0;
                        save_user(player);
                    }
                    else {printf("you have no wood storage  becouse you can build wood resource \n");}
                    break;
                    case FOOD:
                        if (exist_building[1]==1) {
                            printf("add food resource is starting finish time 2 minute later\n");
                            player->resources_generators[empty_resource].lvl = 1;
                            player->resources_generators[empty_resource].resource = FOOD;
                            set_time(player, 1, empty_resource, 120);
                            player->resources_generators[empty_resource].status = ADDING;
                            player->resources_generators[empty_resource].collect_rate=0;
                            save_user(player);
                        }
                        else {printf("you have no food storage  becouse you can build food resource \n");}
                    break;
                    case STONE:
                        if (exist_building[2]==1) {
                            printf("add stone resource is starting finish time 2 minute later\n");
                            player->resources_generators[empty_resource].lvl = 1;
                            player->resources_generators[empty_resource].resource = STONE;
                            set_time(player, 1, empty_resource, 120);
                            player->resources_generators[empty_resource].status = ADDING;
                            player->resources_generators[empty_resource].collect_rate=0;
                            save_user(player);
                        }
                    else {printf("you have no stone storage  becouse you can build stone resource \n");}
                    break;

                }
            sleep(3);
            break;
            default:
                printf("your village has  resource_wood=%d resource_food=%dresource_stone %d \n", count_resource[0],
                       count_resource[1], count_resource[2]);
                printf(" village currently has 6 resources.therefore,it not possible to create a new resource! ");
                return_back = 1;
            sleep(3);
        }

    }
}
#endif
