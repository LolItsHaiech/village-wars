#include "resources.h"
#include "../user.h"
#include "stdbool.h"
#include "../../file_management.h"


bool add_resource(user *player, int count, enum Resource resource) {
    switch (resource) {
        case WOOD:
            player->resources.wood_count+=count;
            break;
        case FOOD:
            player->resources.food_count+=count;
            break;
        case STONE:
            player->resources.stone_count+=count;
            break;
    }
    return save_user(player);
}
