#ifndef BUILDING_H
#define BUILDING_H
#include<stdio.h>
#include "view_building.h"
#include "add_building.h"
#include "upgrade_building.h"
#include "delete_building.h"
#include <stdlib.h>

inline void building_ui(user *player) {
    enum choice { view_buildings = 1, add_buildings, upgrade_buildings, delete_buildings };
    int main_choice;
    while (true) {
        system("cls");
        printf(
            "building:\n  1_ view building\n  2_ add new building\n  3_ update building\n  4_ delete building\n  5_ return back\n");
        scanf("%d", &main_choice);
        if (main_choice == 5) {
            break;
        }
        switch ((enum choice) main_choice) {
            case view_buildings:
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
            default:
                printf("your choice incorrect please try again\n");
        }
    }
}
#endif
