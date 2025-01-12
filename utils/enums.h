#ifndef ENUMS_H
#define ENUMS_H

enum MenuOptions { LOGIN = 1, REGISTER, EXIT };

enum Resource {
    WOOD,
    FOOD,
    STONE
};

enum building_status {
    ADDING,
    UPGRADING,
    DELETING,
    FINISHED
};

enum Buildings {
    FOOD_STORAGE,
    WOOD_STORAGE,
    STONE_STORAGE,
    BARRACK
};

enum AttackStatus { ON_THE_WAY, ON_THE_WAY_BACK, DONE };


enum UserMenuOptions {
    RENAME_VILLAGE = 1,
    RESOURCES,
    BUILDINGS,
    MILITARIES,
    ATTACKS,
    CHANGE_PASSWORD,
    LOGOUT
};

enum MilitaryMenuOptions {VIEW_MILITARIES, ADD_MILITARY, RETURN1};

#endif
