#ifndef VIEW_MILITARY_H
#define VIEW_MILITARY_H
#include<stdio.h>
#include"../user.h"
#include <stdlib.h>

#include "../resources_building/printboard_resource.h"
#include "../../file_management.h"
#include "../../headers/constants.h"
#include "../../file_management.h"
#include <unistd.h>
inline void view_military(user *player) {
    system("cls");

    while (true) {
        system("cls");
        int  choice,state[18]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int i, numbers_military = 0,number_soldier_creating;
        for (i = 0; i < 6; i++)
            if (player->buildings[i].building_type ==BARRACK&&player->buildings[i].lvl != 0&&player->buildings[i].status ==DEFAULT)
            {numbers_military++;

            }
        if (numbers_military == 0) {
            printf("your village dont have any  barack building\n");
            sleep(2);
            break;
        }

        printview_military(player);
        print_power_of_village(player);
        number_soldier_creating=numbers_soldiers_creating(player);
        if (number_soldier_creating!=0)
        { printf("\nsoldiers name\tnumber in create\tchange time\t\tfinishtime\n");
            print_soldiers_creating(player,state);
            printf("%d_return back",number_soldier_creating+1);
            //todo counter
            scanf("%d", &choice);
            while (1 > choice || choice > number_soldier_creating + 1) {
                printf("your choice is incorrect try again");
                system("cls");
                printview_military(player);
                print_power_of_village(player);
                printf("\nsoldiers name\tnumber in create\tchange time\t\tfinishtime\n");
                print_soldiers_creating(player,state);;
                scanf("%d", &choice);
            }
            if (choice == number_soldier_creating + 1)
                break;






            if (1 <= choice && choice <= number_soldier_creating ) {
                time_t now = time(NULL);

                if (now < player->soldiers[state[choice - 1]].finishing_time)
                    printf("\nthe time to complete the process is not over yet\n");
                else {
                    printf("\n %d soldier %s were successfully created\n",
                           player->soldiers[state[choice - 1]].number_soldiers,name_soldiers[(int) player->soldiers[state[choice - 1]].soldier]
                          );
                    switch(player->soldiers[state[choice - 1]].soldier)
                    {
                        case WARRIOR:
                            player->soldiers_count.warrior+=player->soldiers[state[choice - 1]].number_soldiers;
                        break;
                        case RIDER:
                            player->soldiers_count.rider+=player->soldiers[state[choice - 1]].number_soldiers;
                        break;
                        case ARCHER:
                            player->soldiers_count.archer+=player->soldiers[state[choice - 1]].number_soldiers;
                        break;


                    }

                    player->buildings[player->soldiers[state[choice - 1]].state_barrack].storage+=player->soldiers[state[choice - 1]].number_soldiers;

                    player->soldiers[state[choice - 1]].number_soldiers =0;
                    save_user(player);
                }
            }
        }
        else {
            printf("\nyour vilage dont have soldier in creating plese any kay to leave");
            getch();
            break;
        }
    }
}


#endif //VIEW_MILITARY_H
