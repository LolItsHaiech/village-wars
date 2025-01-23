#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>
#include "enums.h"

typedef struct user {
    int id;
    char username[11];
    char village_name[11];
    int encrypted_password;

    struct {
        int wood_count;
        int food_count;
        int stone_count;
    } resources;


    struct {
        int warrior;
        int archer;
        int rider;
    } soldiers_count;

    struct {
        enum Resource resource;
        int lvl;

        enum building_status status;
        time_t change_time;
        time_t finishing_time;
        int collect_rate;
    } resources_generators[6];

    struct {
        bool is_working;
        enum Buildings building_type;
        int lvl;
        time_t change_time;
        time_t finishing_time;
        int storage;
        enum building_status status;
    } buildings[6];

    struct {
        enum Soldier soldier;
        time_t change_time;
        time_t finishing_time;
        int number_soldiers;
    } soldiers[18];
} user;


struct Soldiers {
    int warrior;
    int archer;
    int rider;
};

typedef struct attack {
    int id;

    struct Soldiers soldiers_count;
    struct Soldiers surviving_soldiers;

    time_t request_time;
    time_t start_attack_time;
    int attacker_user_id;
    int attacked_user_id;
    enum AttackStatus status;
    bool attackers_won;
} attack;

#endif
