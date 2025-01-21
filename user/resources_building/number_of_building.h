#ifndef NUMBER_OF_BUILDING_H
#define NUMBER_OF_BUILDING_H
#include"../user.h"

inline int find_Buildings(user *player) {
    int i, empty_building=0;
    for (i = 0; i < 6; i++) {
        if (player->buildings[i].lvl == 0)
            empty_building = i;
    }
    return empty_building;
}

inline int number_buildings(user *player, int state[], int count_building[]) {
    int i, number_building = 0;
    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0) {
            state[number_building] = i;
            number_building++;
            count_building[(int)player->buildings[i].building_type]++;
        }
    return number_building;
}
inline int number_buildings_finished(user *player, int state[], int  count_building[]) {
    int i, number_buildings = 0;
    for (i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0&&player->buildings[i].status==DEFAULT ) {
            state[number_buildings] = i;
            number_buildings++;
             count_building[(int)player->buildings[i].building_type]++;
        }
    return number_buildings;
}
#endif //NUMBER_OF_BUILDING_H
