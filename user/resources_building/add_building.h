#ifndef ADD_BUILDING_H
#define ADD_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include "check_up_building.h"
#include "set_time.h"
#include "number_of_building.h"
#include "capacity.h"
#include "printboard_resource.h"
#include "../../file_management.h"
#include <unistd.h>

inline void add_new_building(user *player) {

    int return_back = 0;

    while (return_back == 0) {
        int choice, numbers_building=0, count_building[4] = {0, 0, 0, 0}, state[6] = {0, 0, 0, 0, 0, 0}, empty_building;
        numbers_building = number_buildings(player, state, count_building);



        switch (numbers_building) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                system("cls");
                show_building(count_building);
                printf("building   capacity   request time  "
                   "\n1_ wood storage\t\t500\t\t3\n2_ food storage\t\t600\t\t3\n3_ stone storage\t\t400\t\t3\n4_ barrack\t\t2soldier creat\t10\n5_ return back");
                scanf("%d", &choice);
            fflush(stdin);

                while (choice < 1 || choice > 5) {
                    printf("your choic is incorect try again\n");
                    sleep(2);
                    system("cls");
                    show_building(count_building);
                    printf("    building                capacity           request time  "
                   "\n1_ wood storage\t\t500\t\t3\n2_ food storage\t\t600\t3\n3_ stone storage\t400\t\t3\n4_ barrack\t2soldier creat\t\t10\n5_ return back");

                    scanf("%d", &choice);
                    fflush(stdin);

                }
                if (choice == 5) {
                    return_back = 1;
                    break;
                }

                empty_building = find_Buildings(player);
                switch ((enum Buildings)(choice-1)) {
                    case WOOD_STORAGE:
                        printf("add woodstorage building is starting finish time 3 minute later\n");
                        player->buildings[empty_building].lvl = 1;
                        player->buildings[empty_building].building_type = WOOD_STORAGE;
                        set_time(player, 2, empty_building, 180);
                        player->buildings[empty_building].status = ADDING;
                     player->buildings[empty_building].storage = 0;

                        save_user(player);
                        break;

                    case FOOD_STORAGE:
                        printf("add foodstorage building is starting finish time 3 minute later\n");
                        player->buildings[empty_building].lvl = 1;
                        player->buildings[empty_building].building_type = FOOD_STORAGE;
                        set_time(player, 2, empty_building, 180);
                        player->buildings[empty_building].status = ADDING;
                         player->buildings[empty_building].storage = 0;

                        save_user(player);
                        break;
                    case STONE_STORAGE:
                        printf("add stonestorage building is starting finish time 3 minute later\n");
                        player->buildings[empty_building].lvl = 1;
                        player->buildings[empty_building].building_type = STONE_STORAGE;
                        set_time(player, 2, empty_building, 180);
                        player->buildings[empty_building].status = ADDING;
                    player->buildings[empty_building].storage = 0;

                        save_user(player);
                        break;
                    case BARRACK:
                        check_up_building(player, BARRACK, empty_building, 0);
                        if (player->buildings[empty_building].lvl == 1) {
                            player->buildings[empty_building].building_type = BARRACK;
                            player->buildings[empty_building].storage = 0;

                            player->buildings[empty_building].status = ADDING;
                            save_user(player);
                        }
                        break;

                }

            sleep(3);
            break;
            case 6:
                system("cls");
                show_building(count_building);
                printf("your village currently has 6 building.therefore,it not possible to create a new building! ");
                return_back = 1;
            sleep(3);
        }
    }
}
#endif
