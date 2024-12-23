#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define USERS_FILE "c:\\village_wars\\users.txt"
#define USER_FILE "c:\\village_wars\\user%02d.txt"
#define TEMP_FILE "c:\\village_wars\\temp.txt"
#include <stdbool.h>
#include <stdio.h>

enum UserFileLine {
    VILLAGE_NAME,
    WOOD_COUNT,
    STONE_COUNT,
    FOOD_COUNT,
    WOOD_LVL,
    STONE_LVL,
    FOOD_LVL
};

struct UserInfo {
    int id;
    char username[11];
    int encrypted_password;
};

int get_last_user_id();
int get_user_id(char[11], char[11]);
void get_user_info(struct UserInfo*, char[21]);
void add_user(struct UserInfo*);
void add_user_to_file(struct UserInfo*, FILE*);
void set_user_property(char*, int, enum UserFileLine);
void get_user_property(char*, int, int, enum UserFileLine);
int get_user_property(int, enum UserFileLine);
bool change_password(int, char[11], char[11]);

#endif //FILE_MANAGEMENT_H

