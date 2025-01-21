#ifndef STORAGE_PER_MIN_H
#define STORAGE_PER_MIN_H
#include"../user.h"
#include"../../headers/constants.h"


//todo remove?
inline void collect_source(user *player, enum Resource resource, int state, int level) {
    switch (resource) {
        case WOOD:
            player->resources_generators[state].collect_rate = wood_rate_per_minute[level-1];
            break;
        case STONE:
            player->resources_generators[state].collect_rate = stone_rate_per_minute[level-1];
            break;
        case FOOD:
            player->resources_generators[state].collect_rate = food_rate_per_minute[level-1];

    }
    save_user(player);
}
#endif //STORAGE_PER_MIN_H
