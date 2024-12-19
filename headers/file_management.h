#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define USERS_FILE "c:\\village_wars\\users.txt"
#define USER_FILE "c:\\village_wars\\user%02d.txt"

struct UserInfo {
    int id;
    char username[11];
    int encrypted_password;
};

int get_last_user_id();
int get_user_id(char username[11], char password[11]);
struct UserInfo get_user_info(char string[21]);
void add_user(struct UserInfo user_info);
void get_village_name(char* output,int id);

#endif //FILE_MANAGEMENT_H
