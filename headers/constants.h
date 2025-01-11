#ifndef UPGRADE_REQUIREMENTS_H
#define UPGRADE_REQUIREMENTS_H

struct resource_requirements {
    int wood, stone, time;
};

struct barrack_requirements {
    int wood, stone, food, time;
};

struct soldier_requirements {
    int wood, stone, food;
};

struct soldier_stats {
    int strength, defence;
};

// food_reqs[i] => amount needed for upgrading i+2 to i+1

const struct resource_requirements wood_reqs[4] = {
    {100, 0, 120},
    {150, 50, 180},
    {200, 100, 300},
    {250, 150, 420}
};

const struct resource_requirements stone_reqs[4] = {
    {100, 0, 180},
    {150, 50, 240},
    {200, 100, 300},
    {250, 150, 480}
};

const struct resource_requirements food_reqs[4] = {
    {100, 0, 120},
    {150, 50, 240},
    {200, 100, 420},
    {250, 150, 600}
};

const struct resource_requirements wood_storage_reqs[4] = {
    {150, 75, 600},
    {200, 100, 900},
    {250, 125, 1200},
    {300, 150, 1500},
};

const struct resource_requirements stone_storage_reqs[4] = {
    {150, 75, 900},
    {200, 100, 1200},
    {250, 125, 1500},
    {300, 150, 1800},
};

const struct resource_requirements food_storage_reqs[4] = {
    {150, 75, 300},
    {200, 100, 600},
    {250, 125, 900},
    {300, 150, 1200},
};

// wood_rate[i] => wood rate of level i+1
const int wood_rate_per_minute[5] = {15,30,45,60,80};
const int stone_rate_per_minute[5] = {10,20,30,40,50};
const int food_rate_per_minute[5] = {35,50,75,90,120};

const int wood_storage_capacity[5] = {500, 1000, 1500, 2000, 2500};
const int stone_storage_capacity[5] = {400,800,1200,1600,2000};
const int food_storage_capacity[5] = {600,1000,1400,2000,2600};


// barrack_requirements[i] => upgrade from lvl i to lvl i+1
const struct barrack_requirements barrack_reqs[5] = {
    {100, 50, 50, 600},
    {150, 75, 90, 1800},
    {200, 100, 190, 2100},
    {250, 125, 250, 2400},
    {300, 150, 450, 3000},
};

const struct soldier_requirements warrior_requirements = {50, 30, 20};
const struct soldier_requirements archer_requirements = {75, 30, 30};
const struct soldier_requirements rider_requirements = {100, 50, 60};

const struct soldier_stats warrior_stats = {10, 5};
const struct soldier_stats archer_stats = {15, 4};
const struct soldier_stats rider_stats = {20, 7};


const char *name_resource[3] = {"WOOD", "FOOD", "STONE"};
const char *name_building[4] ={"FOOD_STORAGE", "WOOD_STORAGE", "STONE_STORAGE","BARRACK"};
const char *status_construct[4] = {"ADD", "UP", "DEL","-"};


#endif //UPGRADE_REQUIREMENTS_H
