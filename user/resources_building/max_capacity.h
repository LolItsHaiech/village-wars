#ifndef MAX_CAPACITY_H
#define MAX_CAPACITY_H
#include"../user.h"

inline void max_capacity(user *player, int capacity[]) {
    for (int i = 0; i < 6; i++)
        if (player->buildings[i].lvl != 0 && player->buildings[i].status == FINISHED)
            switch (player->buildings[i].building_type) {
                case WOOD_STORAGE: capacity[0] += player->buildings[i].storage;
                    break;
                case FOOD_STORAGE: capacity[1] += player->buildings[i].storage;
                    break;
                case STONE_STORAGE: capacity[2] += player->buildings[i].storage;
                default:
            }
}


#endif //MAX_CAPACITY_H
