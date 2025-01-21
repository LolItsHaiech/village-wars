#ifndef DELETE_BUILDING_H
#define DELETE_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include"../../headers/constants.h"
#include "set_time.h"
#include "number_of_building.h"

#include <unistd.h>
void print_delete_building(user *player) {
    int i, counter = 1,building_req[3]={0,0,0};;
    printf("\nbuilding:   \t level\tcapacity\t");
    for (i = 0; i < 6; i++)

        if (player->buildings[i].lvl != 0 && player->buildings[i].status == DEFAULT) {


            printf("\n  %d\t%s\t%d\t%d", counter, name_building[player->buildings[i].building_type],
                   player->buildings[i].lvl, player->buildings[i].storage);
            counter++;
        }

    printf("%d_return back\n", counter);
    printf("enter number of row to deleting  bulding or return back:\n");
}
inline void delete_building(user *player) {
    system("cls");
    //todo boolean
    int choice, except_choice;
    while (true) {
        int state[6] = {0, 0, 0, 0, 0, 0}, number_building, count_building[4] = {0, 0, 0, 0};
        number_building = number_buildings_finished(player, state, count_building);
        if (number_building == 0) {
            printf("you have no building finished to delete ");
            sleep(3);

            break;
        }


        print_delete_building(player);
        scanf("%d", &choice);
        fflush(stdin);

        while (1 > choice || choice > number_building + 1) {
            printf("your choice is incorect try again");
            sleep(2);
            system("cls");
            print_delete_building(player);
            scanf("%d", &choice);
            fflush(stdin);

        }
        if (choice == number_building + 1)
            break;
        printf("%d",count_building[(int)player->buildings[choice-1].building_type]);
        if (count_building[(int)player->buildings[choice-1].building_type]==1) {
            printf("you cant delete  main building ");
            sleep(2);
            break;
        }
        if (1 <= choice && choice <= number_building) {
            system("cls");
            printf("are you sure to delete this building %s level %d ?\n1.yes\n2.no\n",
                   name_building[(int) player->buildings[state[choice - 1]].building_type],
                   player->buildings[state[choice - 1]].lvl);

            scanf("%d", &except_choice);
            fflush(stdin);

            while (except_choice != 1 && except_choice != 2) {
                printf("your choice is incorect try again");
                scanf("%d", &except_choice);
                fflush(stdin);

            }
            switch (except_choice) {
                case 1:
                    system("cls");
                    printf("deleting building..... ready to delete in  2 minutes");
                    set_time(player, 2, state[choice - 1], 120);
                    player->buildings[state[choice - 1]].status = DELETING;
                    save_user(player);
                sleep(2);

                    break;

                case 2:
                    printf("process is cancelled");
                sleep(3);

                    break;
            }
        }
    }
}

#endif
