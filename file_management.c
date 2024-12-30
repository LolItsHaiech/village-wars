#include "file_management.h"

#include <locale.h>

#include "user/attacks/attacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user/user.h"

// todo ask before removing file

void save_user(user* input_user) {
    FILE *users_file = fopen(USERS_FILE, "r");

    if (users_file == NULL) {
        users_file = fopen(USERS_FILE, "w");
        if (users_file == NULL) {
            return;
        }
        fwrite(input_user, sizeof(user), 1, users_file);
        fclose(users_file);
        return;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");

    if (temp_file == NULL) {
        remove(TEMP_FILE);
        temp_file = fopen(TEMP_FILE, "w");
    }

    while (!feof(users_file)) {
        user temp_user;
        fread(&temp_user, sizeof(user), 1, users_file);
        if (input_user->id == temp_user.id) {
            fwrite(input_user, sizeof(user), 1, temp_file);
        } else {
            fwrite(&temp_user, sizeof(user), 1, temp_file);
        }
    }

    fclose(users_file);
    fclose(temp_file);

    remove(USERS_FILE);
    rename(TEMP_FILE, USERS_FILE);
}

int get_last_user_id() {
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

user *get_user(char username[11], char password[11]) {
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

void get_username_by_id(char output[], int id) {
    FILE *users_file = fopen(USERS_FILE, "r");

    if (users_file == NULL) {
        strcpy(output, "<Unknown>");
        return;
    }

    while (!feof(users_file)) {
        user cur_user;
        fread(&cur_user, sizeof(user), 1, users_file);
        if (cur_user.id == id) {
            strcpy(output, cur_user.username);
            fclose(users_file);
            return;
        }
    }
    fclose(users_file);
}

void add_user(user *player) {
    FILE *users_file = fopen(USERS_FILE, "a");
    if (users_file == NULL) {
        remove(USERS_FILE);
        users_file = fopen(USERS_FILE, "a");
    }
    fwrite(player, sizeof(user), 1, users_file);
    fclose(users_file);
}

bool unique_username_filter(char *username) {
    FILE *users_file = fopen(USERS_FILE, "r");
    if (users_file == NULL)
        return true;
    while (!feof(users_file)) {
        user temp_user;
        fread(&temp_user, sizeof(user), 1, users_file);
        if (strcmp(temp_user.username, username) == 0) {
            fclose(users_file);
            puts("Username is already taken,\ntry again.\n");
            return false;
        }
    }
    fclose(users_file);
    return true;
}

user *get_all_users_expect(int *output_count, user *excluded_user) {
    *output_count = 0;
    FILE *users_file = fopen(USERS_FILE, "r");
    if (users_file == NULL)
        return NULL;
    user *output = NULL; //todo?
    while (feof(users_file)) {
        user temp;
        fread(&temp, sizeof(user), 1, users_file);
        if (temp.id != excluded_user->id) {
            output = realloc(output, ((*output_count) + 1) * sizeof(user));
            output[(*output_count)++] = temp;
        }
    }
    return output;
}

void add_attack(attack input_attack) {
    FILE *attacks_file = fopen(ATTACKS_FILE, "a");
    if (attacks_file == NULL) {
        remove(ATTACKS_FILE);
        attacks_file = fopen(ATTACKS_FILE, "a");
    }
    fwrite(&input_attack, sizeof(attack), 1, attacks_file);
    fclose(attacks_file);
}


attack *get_user_attacks(int *attacks_count, int id, bool done) {
    attack *attack_arr = NULL;
    *attacks_count = 0;
    FILE *attacks_file = fopen(ATTACKS_FILE, "r");
    if (attacks_file == NULL)
        return NULL;
    if (!feof(attacks_file)) {
        attack_arr = realloc(attack_arr, (*attacks_count + 1) * sizeof(attack));
        fread(&attack_arr[*attacks_count], sizeof(attack), 1, attacks_file);
        //todo like this?
        if ((attack_arr[*attacks_count].attacker_user_id == id || attack_arr[*attacks_count].attacked_user_id == id) &&
            ((done && attack_arr[*attacks_count].status == DONE) ||
            ((!done && attack_arr[*attacks_count].status != DONE)))) {

            (*attacks_count)++;
        }
    }
    return attack_arr;
}

int get_last_attack_id() {
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

void save_attack(attack* input_attack) {
    FILE *attacks_file = fopen(ATTACKS_FILE, "r");

    if (attacks_file == NULL) {
        attacks_file = fopen(ATTACKS_FILE, "w");
        if (attacks_file == NULL) {
            return;
        }
        fwrite(input_attack, sizeof(attack), 1, attacks_file);
        fclose(attacks_file);
        return;
    }

    FILE *temp_file = fopen(TEMP_FILE, "w");

    if (temp_file == NULL) {
        remove(TEMP_FILE);
        temp_file = fopen(TEMP_FILE, "w");
    }

    while (!feof(attacks_file)) {
        attack temp_attack;
        fread(&temp_attack, sizeof(attack), 1, attacks_file);
        if (input_attack->id == temp_attack.id) {
            fwrite(input_attack, sizeof(attack), 1, temp_file);
        } else {
            fwrite(&temp_attack, sizeof(attack), 1, temp_file);
        }
    }

    fclose(attacks_file);
    fclose(temp_file);

    remove(USERS_FILE);
    rename(TEMP_FILE, USERS_FILE);
}
