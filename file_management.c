#include "headers/file_management.h"
#include <stdbool.h>
#include "headers/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    output[i]='\0';
}

void set_file_line(char* new_value, char* file_address, int line) {
    FILE* file = fopen(file_address, "r");
    FILE* temp_file = fopen(TEMP_FILE, "w");
    int line_counter = 0;
    while (line_counter != line) {
        char ch = fgetc(file);
        if (ch == '\n') {
            line_counter++;
        }
        fputc(ch, temp_file);
    }
    char ch;
    fprintf(temp_file , "%s\n", new_value);
    while(fgetc(file)!='\n') {}
    while((ch = fgetc(file)) != EOF) {
        fputc(ch, temp_file);
    }

    fclose(temp_file);
    fclose(file);
    remove(file_address);
    rename(TEMP_FILE, file_address);
}

void get_user_property(char* output, int output_size, int id, enum UserFileLine property) {
    // todo what if file is deleted

    char file_name[50];
    sprintf(file_name, USER_FILE, id);
    FILE *user_file = fopen(file_name, "r");
    get_file_line(output, output_size, user_file, (int)property);
    fclose(user_file);
}

void set_user_property(char *new_name, int id, enum UserFileLine property) {
    char file_name[50];
    sprintf(file_name, USER_FILE, id);
    set_file_line(new_name, file_name, (int) property);
}

int get_user_property(int id, enum UserFileLine property);

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
        struct UserInfo* user_info = (struct UserInfo*)malloc(sizeof(struct UserInfo));
        get_user_info(user_info, user_string);
        if (strcmp(user_info->username, username) == 0 && user_info->encrypted_password == encrypt_password(password)) {
            fclose(users_file);
            int res = user_info->id;
            free(user_info);
            return res;
        }
        free(user_info);
    }
    fclose(users_file);
    return -1;
}


void get_user_info(struct UserInfo* user_info, char string[22]) {
    user_info->id = str2int(string, 2);
    strncpy(user_info->username, &string[3], 10);
    end_string(user_info->username);
    user_info->encrypted_password = str2int(string + 14, 6);
}

void add_user_to_file(struct UserInfo* user_info, FILE *file) {
    add_whitespace(user_info->username, 11);
    fprintf(file, "%02d:%s:%06d\n", user_info->id, user_info->username, user_info->encrypted_password);
}

void add_user(struct UserInfo* user_info) {
    char file_name[50];
    sprintf(file_name, USER_FILE, user_info->id);
    FILE *user_file = fopen(file_name, "w");

    fprintf(user_file, "%s\n", user_info->username); // village name
    fprintf(user_file, "0\n"); //                      wood count
    fprintf(user_file, "0\n"); //                      stone count
    fprintf(user_file, "0\n"); //                      food count
    fprintf(user_file, "1\n"); //                      wood lvl
    fprintf(user_file, "1\n"); //                      stone lvl
    fprintf(user_file, "1\n"); //                      food lvl

    fclose(user_file);

    FILE *users_file = fopen(USERS_FILE, "a");
    add_user_to_file(user_info, users_file);
    fclose(users_file);
}


bool change_password(int id, char old_password[11], char new_password[11]) {
    char user_string[22];
    bool successful = false;
    FILE *users_file = fopen(USERS_FILE, "r");
    FILE *temp_file = fopen(TEMP_FILE, "w");

    while (fgets(user_string, 22, users_file)) {
        struct UserInfo* user_info = (struct UserInfo*)malloc(sizeof(struct UserInfo));
        get_user_info(user_info, user_string);
        if (user_info->id == id && user_info->encrypted_password == encrypt_password(old_password)) {
            user_info->encrypted_password = encrypt_password(new_password);
            successful = true;
        }
        add_user_to_file(user_info, temp_file);
        free(user_info);
    }

    fclose(users_file);
    fclose(temp_file);

    remove(USERS_FILE);
    rename(TEMP_FILE, USERS_FILE);

    return successful;
}
