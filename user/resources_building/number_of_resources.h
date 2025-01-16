#ifndef NUMBER_OF_RESOURCE_H
#define NUMBER_OF_RESOURCE_H
#include"../user.h"

inline int find_resource(user *player) {
    int i;
    for (i = 0; i < 6; i++) {
        if (player->resources_generators[i].lvl == 0)
            return i;
    }
}

inline int number_resource(user *player, int state[], int count_resource[]) {
    int i, number_resources = 0;
    for (i = 0; i < 6; i++)
        if (player->resources_generators[i].lvl != 0) {
            state[number_resources] = i;
            number_resources++;
            count_resource[player->resources_generators[i].resource]++;
        }
    return number_resources;
}
#endif
