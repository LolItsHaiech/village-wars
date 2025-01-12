#ifndef SET_TIME_H
#define SET_TIME_H
#include <stdio.h>
#include "../user.h"
#include <time.h>
#include "../../headers/constants.h"
#include "../../file_management.h"
#include <stdbool.h>


//todo: fix later
inline void set_time(user *player, int type, int state, int time_needed) {
    time_t now = time(NULL);
    switch (type) {
        case 1:
            player->resources_generators[state].change_time = now;
            player->resources_generators[state].finishing_time = now + time_needed;
        case 2:
            player->buildings[state].change_time = now;
            player->buildings[state].finishing_time = now + time_needed;
    }
    save_user(player);
}

inline int get_time_needed(bool is_build, int type, int level) {
    int time_needed;
    switch (is_build) {
        case false:
            switch ((enum Resource) type) {
                case WOOD:
                    time_needed = wood_reqs[level - 1].time;
                    break;
                case STONE:
                    time_needed = stone_reqs[level - 1].time;
                    break;
                case FOOD:
                    time_needed = food_reqs[level - 1].time;
                    break;
            }
        default:
            switch ((enum buildings) type) {
                case FOOD_STORAGE:
                    time_needed = food_storage_reqs[level - 1].time;
                    break;
                case WOOD_STORAGE:
                    time_needed = wood_storage_reqs[level - 1].time;
                    break;
                case STONE_STORAGE:
                    time_needed = stone_storage_reqs[level - 1].time;
                    break;
                case BARRACK:
                    time_needed = barrack_reqs[level - 1].time;
            }
    }
    return time_needed;
}

#endif //SET_TIME_H
