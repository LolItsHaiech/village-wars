#ifndef VIEW_BUILDING_H
#define VIEW_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include "capacity.h"

#include "printboard_resource.h"
#include"../../headers/constants.h"
#include <unistd.h>

inline void view_building(user *player) {
    system("cls");
    int state[6] = {0, 0, 0, 0, 0, 0}, choice;
    while (true) {
        system("cls");
        int i, numbers_building = 0;
        for (i = 0; i < 6; i++)
            if (player->buildings[i].lvl != 0) {
                state[numbers_building] = i;
                numbers_building++;

            }
        if (numbers_building == 0) {
            printf("your village dont have any building\n");
            sleep(2);
            break;
        }
        printf("view building\n\tbuild\t\tlevel\t\tsave source\trequset time\t\tfinish time\tstatus");
        printview_building(player);
        scanf("%d", &choice);
        fflush(stdin);

        while (1 > choice || choice > numbers_building + 1) {
            printf("your choice is incorrect try again");
            system("cls");
            printview_building(player);;
            scanf("%d", &choice);
            fflush(stdin);

        }
        if (choice == numbers_building + 1)
            break;

        if (1 <= choice && choice <= numbers_building) {
            time_t now = time(NULL);
            if (player->buildings[state[choice - 1]].status == DEFAULT)
                printf("your choice is finished");
            else if (now < player->buildings[state[choice - 1]].finishing_time)
                printf("the time to complete the process is not over yet");
            else {
                printf("build %s were successfully %s",
                       name_building[(int) player->buildings[state[choice - 1]].building_type],
                       status_construct[(int)player->buildings[state[choice - 1]].status]);
                if (player->buildings[state[choice - 1]].status ==ADDING)
                {       capacity(player,player->buildings[state[choice - 1]].building_type , state[choice - 1], 0);
                player->buildings[state[choice - 1]].is_working =true;
            }
                if (player->buildings[state[choice - 1]].status == DELETING)
                    player->buildings[state[choice - 1]].lvl = 0;
                if (player->buildings[state[choice - 1]].status == UPGRADING) {
                                        capacity(player, player->buildings[state[choice - 1]].building_type, state[choice - 1],player->buildings[state[choice - 1]].lvl);
                                        player->buildings[state[choice - 1]].is_working =true;
                    player->buildings[state[choice - 1]].lvl++;
                }
                player->buildings[state[choice - 1]].status = DEFAULT;
                player->buildings[state[choice - 1]].finishing_time = now;
                save_user(player);
            }
            sleep(3);

        }
    }
}


#endif
