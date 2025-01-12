#ifndef VIEW_BUILDING_H
#define VIEW_BUILDING_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>
#include <time.h>
#include"../../headers/constants.h"

inline void view_building(user *player) {
    system("cls");
    int state[6] = {0, 0, 0, 0, 0, 0}, choice;
    while (true) {
        int i, numbers_building = 0;
        for (i = 0; i < 6; i++)
            if (player->buildings[i].lvl != 0 || player->buildings[i].status == DELETING) {
                numbers_building++;
                state[numbers_building] = i;
            }
        if (numbers_building == 0) {
            printf("your village dont have any building\n");
            break;
        }
        printf("view building\n\tbuild\tlevel  \tsave source\trequset time\tfinish time\tstatus");
        printview_building(player);
        scanf("%d", &choice);
        while (1 > choice || choice > numbers_building + 1) {
            printf("your choice is incorrect try again");
            system("cls");
            printview_building(player);;
            scanf("%d", &choice);
        }
        if (choice == numbers_building + 1)
            break;

        if (1 <= choice && choice <= numbers_building) {
            time_t now = time(NULL);
            if (player->buildings[state[choice - 1]].status == FINISHED)
                printf("your choice is finished");
            else if (now < player->buildings[state[choice - 1]].finishing_time)
                printf("the time to complete the process is not over yet");
            else {
                printf("build %s were successfully %s",
                       name_building[(int) player->buildings[state[choice - 1]].building_type],
                       status_construct[(int)player->buildings[state[choice - 1]].status]);
                player->buildings[state[choice - 1]].status = 4;
                player->buildings[state[choice - 1]].finishing_time = now;
                save_user(player);
            }
        }
    }
}


#endif
