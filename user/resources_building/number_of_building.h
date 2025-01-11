#ifndef NUMBER_OF_BUILDING_H
#define NUMBER_OF_BUILDING_H
#include"../user.h"

int find_Buildings(user *player) {
    int i, empty_building;
    for (i = 0; i < 6; i++) {
        if (player->buildings[i].lvl == 0 && player->buildings[i].status == finished)
            empty_building = i;
    }
    return empty_building;
}

int number_buildings(user *player, int state[], int count_building[]) {
    int i, number_building = 0;


    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0 && player->buildings[i].status == finished) {
            state[number_building] = i;
            number_building++;
            count_building[player->buildings[i].building_type]++;
        }

    return number_building;
}


#endif //NUMBER_OF_BUILDING_H
