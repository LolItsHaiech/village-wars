#include "headers/file_management.h"

#include <stdbool.h>

#include "headers/utils.h"

#include <stdio.h>
#include <string.h>

struct UserInfo;

enum UserFileLine {
    VILLAGE_NAME
};

void get_file_line(char *output, int output_size, FILE *file, int line) {
    int line_counter = 0;
    while (line_counter != line) {
        char ch = fgetc(file);
        if (ch == '\n') {
            line_counter++;
        }
    }

    char ch;
    int i = 0;

    while ((ch = fgetc(file))!='\n' && i < output_size) {
        output[i] = ch;
        i++;
    }
    // for (i = 0;  ; ++i)
    output[i]='\0';
}

int get_last_user_id() {
    FILE *user_file = fopen(USERS_FILE, "r");
    char user_string[22];
    int id = -1;
    while (fgets(user_string, 22, user_file)) {
        printf("%s", user_string);
        id = str2int(user_string, 2);
    }
    fclose(user_file);
    return id;
}

int get_user_id(char username[11], char password[11]) {
    FILE *users_file = fopen(USERS_FILE, "r");
    char user_string[22];
    while (fgets(user_string, 22, users_file)) {
        struct UserInfo user_info = get_user_info(user_string);
        if (strcmp(user_info.username, username) == 0 && user_info.encrypted_password == encrypt_password(password)) {
            fclose(users_file);
            return user_info.id;
        }
    }
    fclose(users_file);
    return -1;
}


struct UserInfo get_user_info(char string[21]) {
    struct UserInfo user_info;
    user_info.id = str2int(string, 2);
    strncpy(user_info.username, &string[3], 10);
    end_string(user_info.username);
    user_info.encrypted_password = str2int(string + 14, 6);
    return user_info;
}

void add_user_to_file(struct UserInfo user_info, FILE *file) {
    add_whitespace(user_info.username, 11);
    fprintf(file, "%02d:%s:%06d\n", user_info.id, user_info.username, user_info.encrypted_password);
}

void add_user(struct UserInfo user_info) {
    char file_name[50];
    sprintf(file_name, USER_FILE, user_info.id);
    FILE *user_file = fopen(file_name, "w");
    fprintf(user_file, "%s\n", user_info.username); // line 1: village name
    fclose(user_file);

    FILE *users_file = fopen(USERS_FILE, "a");
    add_user_to_file(user_info, users_file);
    fclose(users_file);
}

void get_village_name(char *output, int id) {
    // todo what if file is deleted/ there is more than 10 chars


    char file_name[50];
    sprintf(file_name, USER_FILE, id);
    FILE *user_file = fopen(file_name, "r");
    get_file_line(output, 11, user_file, VILLAGE_NAME);
    if (!user_file) {
        strcpy(output, "unknown");
        return;
    }
    int i;
    char current_char = fgetc(user_file);

    for (i = 0; current_char != '\n'; i++) {
        output[i] = current_char;
        current_char = fgetc(user_file);
    }


    output[i] = '\0';
    fclose(user_file);
}

void set_village_name(char *new_name, int id) {
    // todo temp later
    char file_name[50];
    sprintf(file_name, USER_FILE, id);
    FILE *user_file = fopen(file_name, "w");
    fprintf(user_file, new_name);
    fprintf(user_file, "\n");
    fclose(user_file);
}


bool change_password(int id, char old_password[11], char new_password[11]) {
    char user_string[22];
    bool found = false;
    FILE *users_file = fopen(USERS_FILE, "r");
    FILE *temp_file = fopen(TEMP_USERS_FILE, "w");

    while (fgets(user_string, 22, users_file)) {
        struct UserInfo user_info = get_user_info(user_string);
        if (user_info.id == id && user_info.encrypted_password == encrypt_password(old_password)) {
            user_info.encrypted_password = encrypt_password(new_password);
            found = true;
        }
        add_user_to_file(user_info, temp_file);
    }

    fclose(users_file);
    fclose(temp_file);

    remove(USERS_FILE);
    rename(TEMP_USERS_FILE, USERS_FILE);

    return found;
}
