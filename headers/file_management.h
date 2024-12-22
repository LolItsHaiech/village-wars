#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define USERS_FILE "c:\\village_wars\\users.txt"
#define TEMP_USERS_FILE "c:\\village_wars\\temp_users.txt"
#define USER_FILE "c:\\village_wars\\user%02d.txt"
#include <stdbool.h>
#include <stdio.h>


struct UserInfo {
    int id;
    char username[11];
    int encrypted_password;
};

int get_last_user_id();
int get_user_id(char[11], char[11]);
struct UserInfo get_user_info(char[21]);
void add_user(struct UserInfo);
void add_user_to_file(struct UserInfo, FILE*);
void get_village_name(char* ,int);
void set_village_name(char*, int);
bool change_password(int, char[11], char[11]);

#endif //FILE_MANAGEMENT_H
