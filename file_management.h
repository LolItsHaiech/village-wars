#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define USERS_FILE "c:\\village_wars\\users.txt"
#define ATTACKS_FILE "c:\\village_wars\\attacks.txt"
#define TEMP_FILE "c:\\village_wars\\temp.txt"
#include <stdbool.h>

#include "user/attacks/attacks.h"
#include "user/user.h"

int get_last_user_id();
user* get_user(char[11], char[11]);
void get_username_by_id(char output[], int id);
void add_user(user*);
bool unique_username_filter(char*);
user* get_all_users_expect(int* , user* );
void save_user(user*);
void add_attack(attack input_attack);
attack *get_user_attacks(int *, int, bool);
int get_last_attack_id();
void save_attack(attack* input_attack);

#endif //FILE_MANAGEMENT_H

