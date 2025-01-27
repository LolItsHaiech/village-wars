#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define USERS_FILE "users.txt"
#define ATTACKS_FILE "attacks.txt"
#define TEMP_FILE "temp.txt"

#include <inttypes.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/input.h"
#include "utils/utils.h"
#include "utils/structs.h"



inline bool save_user(user *input_user) {
    FILE *users_file = fopen(USERS_FILE, "r");

    if (users_file == NULL) {
        users_file = fopen(USERS_FILE, "w");
        if (users_file == NULL) {
            return false;
        }
        fwrite(input_user, sizeof(user), 1, users_file);
        fclose(users_file);
        return false;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");

    if (temp_file == NULL) {
        remove(TEMP_FILE);
        temp_file = fopen(TEMP_FILE, "w");
    }


    bool saved = false;

    user temp_user;
    while (fread(&temp_user, sizeof(user), 1, users_file)) {
        if (input_user->id == temp_user.id) {
            saved = true;
            fwrite(input_user, sizeof(user), 1, temp_file);
        } else {
            fwrite(&temp_user, sizeof(user), 1, temp_file);
        }
    }

    fclose(users_file);
    fclose(temp_file);

    remove(USERS_FILE);
    rename(TEMP_FILE, USERS_FILE);
    return saved;
}

inline int get_last_user_id() {
    FILE *users_file = fopen(USERS_FILE, "r");
    if (users_file == NULL)
        return -1;
    int id = -1;
    while (!feof(users_file)) {
        user temp_user;
        fread(&temp_user, sizeof(user), 1, users_file);
        id = temp_user.id;
    }
    fclose(users_file);
    return id;
}

inline user *get_user(char username[11], char password[11]) {
    FILE *users_file = fopen(USERS_FILE, "r");

    if (users_file == NULL) {
        return NULL;
    }

    while (!feof(users_file)) {
        user *cur_user = (user *) malloc(sizeof(user));
        fread(cur_user, sizeof(user), 1, users_file);
        if (strcmp(cur_user->username, username) == 0 &&
            cur_user->encrypted_password == encrypt_password(password)) {
            fclose(users_file);
            return cur_user;
        }
        free(cur_user);
    }
    fclose(users_file);
    return NULL;
}

inline user *get_user_by_id(int id) {
    FILE *users_file = fopen(USERS_FILE, "r");

    if (users_file == NULL) {
        return NULL;
    }

    while (!feof(users_file)) {
        user *cur_user = (user *) malloc(sizeof(user));
        fread(cur_user, sizeof(user), 1, users_file);
        if (cur_user->id == id) {
            fclose(users_file);
            return cur_user;
        }
    }
    fclose(users_file);
    return NULL;
}

inline bool add_user(user *player) {
    FILE *users_file = fopen(USERS_FILE, "a");
    if (users_file == NULL) {
        remove(USERS_FILE);
        if (read_confirmation("Users file cannot be accessed,\nRemove the file and try again?", false))
            users_file = fopen(USERS_FILE, "a");
        else
            return false;
    }
    bool success = fwrite(player, sizeof(user), 1, users_file);
    fclose(users_file);
    return success;
}

inline bool unique_username_filter(char *username) {
    FILE *users_file = fopen(USERS_FILE, "r");
    if (users_file == NULL)
        return true;
    while (!feof(users_file)) {
        user temp_user;
        fread(&temp_user, sizeof(user), 1, users_file);
        if (strcmp(temp_user.username, username) == 0) {
            fclose(users_file);
            printf("Username is already taken.\n");
            return false;
        }
    }
    fclose(users_file);
    return true;
}

inline user *get_all_users_expect(int *output_count, user *excluded_user) {
    *output_count = 0;
    FILE *users_file = fopen(USERS_FILE, "r");
    if (users_file == NULL)
        return NULL;
    user *output = NULL;
    user temp;
    while (fread(&temp, sizeof(user), 1, users_file)) {
        if (temp.id != excluded_user->id) {
            output = realloc(output, ((*output_count) + 1) * sizeof(user));
            output[(*output_count)++] = temp;
        }
    }
    fclose(users_file);
    return output;
}

inline void add_attack(attack input_attack) {
    FILE *attacks_file = fopen(ATTACKS_FILE, "a");
    if (attacks_file == NULL) {
        remove(ATTACKS_FILE);
        attacks_file = fopen(ATTACKS_FILE, "a");
    }
    fwrite(&input_attack, sizeof(attack), 1, attacks_file);
    fclose(attacks_file);
}

inline attack *get_user_attacks(int *attacks_count, int id, bool done, bool only_user_attacks) {
    attack *attack_arr = NULL;

    *attacks_count = 0;

    FILE *attacks_file = fopen(ATTACKS_FILE, "r");
    if (attacks_file == NULL)
        return NULL;


    attack temp;

    while (fread(&temp, sizeof(attack), 1, attacks_file)) {
        if ((temp.attacker_user_id == id || (!only_user_attacks && temp.attacked_user_id == id)) &&
            ((done && temp.status == DONE) || (!done && temp.status != DONE))) {


            attack_arr = realloc(attack_arr, (*attacks_count + 1) * sizeof(attack));
            attack_arr[*attacks_count] = temp;
            (*attacks_count)++;
        }
    }

    fclose(attacks_file);
    return attack_arr;
}

inline int get_last_attack_id() {
    FILE *attacks_file = fopen(ATTACKS_FILE, "r");
    if (attacks_file == NULL)
        return -1;
    int id = -1;
    while (!feof(attacks_file)) {
        user temp_attack;
        fread(&temp_attack, sizeof(attack), 1, attacks_file);
        id = temp_attack.id;
    }
    fclose(attacks_file);
    return id;
}

// inline void save_attack(attack* input_attack) {
//     FILE *attacks_file = fopen(ATTACKS_FILE, "r");
//
//     if (attacks_file == NULL) {
//         attacks_file = fopen(ATTACKS_FILE, "w");
//         if (attacks_file == NULL) {
//             return;
//         }
//         fwrite(input_attack, sizeof(attack), 1, attacks_file);
//         fclose(attacks_file);
//         return;
//     }
//
//     FILE *temp_file = fopen(TEMP_FILE, "w");
//
//     if (temp_file == NULL) {
//         remove(TEMP_FILE);
//         temp_file = fopen(TEMP_FILE, "w");
//     }
//
//     while (!feof(attacks_file)) {
//         attack temp_attack;
//         fread(&temp_attack, sizeof(attack), 1, attacks_file);
//         if (input_attack->id == temp_attack.id) {
//             fwrite(input_attack, sizeof(attack), 1, temp_file);
//         } else {
//             fwrite(&temp_attack, sizeof(attack), 1, temp_file);
//         }
//     }
//
//     fclose(attacks_file);
//     fclose(temp_file);
//
//     remove(ATTACKS_FILE);
//     rename(TEMP_FILE, ATTACKS_FILE);
// }


inline bool save_attack(attack *input_attack) {
    FILE *attacks_file = fopen(ATTACKS_FILE, "r");

    if (attacks_file == NULL) {
        attacks_file = fopen(ATTACKS_FILE, "w");
        if (attacks_file == NULL) {
            return false;
        }
        fwrite(input_attack, sizeof(attack), 1, attacks_file);
        fclose(attacks_file);
        return false;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");

    if (temp_file == NULL) {
        remove(TEMP_FILE);
        temp_file = fopen(TEMP_FILE, "w");
    }


    bool saved = false;

    attack temp_attack;
    while (fread(&temp_attack, sizeof(attack), 1, attacks_file)) {
        if (input_attack->id == temp_attack.id) {
            saved = true;
            fwrite(input_attack, sizeof(attack), 1, temp_file);
        } else {
            fwrite(&temp_attack, sizeof(attack), 1, temp_file);
        }
    }

    fclose(attacks_file);
    fclose(temp_file);

    remove(ATTACKS_FILE);
    rename(TEMP_FILE, ATTACKS_FILE);
    return saved;
}


#endif //FILE_MANAGEMENT_H
