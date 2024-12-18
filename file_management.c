#include "headers/file_management.h"
#include "headers/utils.h"

#include <stdio.h>
#include <string.h>

struct UserInfo;


int get_last_user_id() {
    FILE *user_file = fopen(USERS_FILE, "r");
    char user_string[22];
    int id = -1;
    while (fgets(user_string, 21, user_file)) {
        id = str2int(user_string, 2);
    }
    fclose(user_file);
    return id;
}

int get_user_id(char username[11], char password[11]) {
    FILE *user_file = fopen(USERS_FILE, "r");
    char user_string[22];
    while (fgets(user_string, 21, user_file)) {
        struct UserInfo user_info = get_user_info(user_string);
        if(strcmp(user_info.username, username) == 0 && user_info.encrypted_password == encrypt_password(password)) {
            fclose(user_file);
            return user_info.id;
        }
    }
    fclose(user_file);
    return -1;
}


struct UserInfo get_user_info(char string[21]) {
    struct UserInfo user_info;
    user_info.id = str2int(string, 2);
    strncpy(user_info.username, &string[3], 10);
    int i;
    for (i = 0; i < 10; ++i) {
        if(user_info.username[i] == ' ') {
            user_info.username[i] = '\0';
            break;
        }
    }
    user_info.encrypted_password = str2int(string+14, 6);
    return user_info;
}

void add_user(struct UserInfo user_info) {
    FILE *user_file = fopen(USERS_FILE, "a");
    add_whitespace(user_info.username, 10);
    fprintf(user_file, "%02d:%s:%06d\n", user_info.id, user_info.username, user_info.encrypted_password);
    fclose(user_file);
}
