#ifndef SET_TIME_H
#define SET_TIME_H
#include <stdio.h>
#include "../user.h"
#include <time.h>
#include "../../headers/constants.h"
#include "../../file_management.h"
#include <stdbool.h>


//todo: fix later later
inline void set_time(user *player, int type, int state, int time_needed) {
    time_t now = time(NULL);
    switch (type) {
        case 1:
            player->resources_generators[state].change_time = now;
            player->resources_generators[state].finishing_time = now + time_needed;
        case 2:
            player->buildings[state].change_time = now;
            player->buildings[state].finishing_time = now + time_needed;
        break;
        case 3:
            player-> soldiers[state].change_time = now;
        player-> soldiers[state].finishing_time = now + time_needed;
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
            break;
        default:
            switch ((enum Buildings) type) {
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
                    //todo level
                    time_needed = barrack_reqs[level].time;
            }
    }
    return time_needed;
}
inline  int get_time_needed_soldiers(int level,enum Soldier  soldier) {
    int time_needed;
    switch ( soldier) {
        case WARRIOR:
            time_needed = time_build_soldier[level - 1].warrior;
        break;
        case RIDER:
            time_needed = time_build_soldier[level - 1].rider;
        break;
        case ARCHER:
            time_needed = time_build_soldier[level - 1].archer;
        break;


    }
    return time_needed;


}

#endif //SET_TIME_H
