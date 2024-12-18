#ifndef USER_H
#define USER_H
#include <stdbool.h>

typedef struct user user;

int encrypt_password(char [11]);
void login_user_ui(bool);
void register_user_ui();
user* register_user(char username[11], char password[11]);
user* login_user(char username[11], char password[11]);

#endif //USER_H
