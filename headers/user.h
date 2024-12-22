#ifndef USER_H
#define USER_H
#include <stdbool.h>

struct user {
    int id;
    char username[11];
};

typedef struct user user;


int encrypt_password(char [11]);
void login_user_ui(bool);
void register_user_ui();
void change_password_ui(user*);
user* register_user(char[11], char[11]);
user* login_user(char[11], char[11]);

#endif //USER_H
