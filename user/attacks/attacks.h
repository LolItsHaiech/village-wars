#ifndef ATTACKS_H
#define ATTACKS_H
#include <time.h>

#include "../user.h"

enum AttackStatus { ON_THE_WAY, ON_THE_WAY_BACK, DONE };

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

void attack_ui(user *player);
void new_attack_ui(user *player);
void view_attacks_ui(user *player);
void attacks_history_ui(user *player);
bool proceed_attack(user *player, attack *input_attack);

#endif //ATTACKS_H
