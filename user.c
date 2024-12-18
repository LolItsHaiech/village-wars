#include "headers/user.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/file_management.h"


typedef struct user {
    int id;
    char username[10];
} user;


void login_user_ui(bool wrong_user) {
    char username[11];
    char password[11], confirm_password[11];

    system("cls");

    printf("Login\n");

    if (wrong_user) {
        printf("Wrong username or password.\n");
        printf("Try again.\n");
    }

    while (1) {
        gets(username);
        fflush(stdin);
        if (strchr(username, ' ')) {
            printf("Username can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    printf("Password: ");
    while (1) {
        gets(password);
        fflush(stdin);
        if (strchr(password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    printf("Confirm password: ");
    while (1) {
        gets(confirm_password);
        fflush(stdin);
        if (strchr(confirm_password, ' ')) {
            printf("Confirm Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        if (strcmp(password, confirm_password) != 0) {
            printf("Password and confirm password do not match.\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    user *player = login_user(username, password);
    if (player == NULL) {
        login_user_ui(true);
    }

    free(player);

    // todo open game
}

void register_user_ui() {
    char username[11];
    char password[11];

    printf("Register\n");

    printf("Username: ");
    while (1) {
        gets(username);
        fflush(stdin);
        if (strchr(username, ' ')) {
            printf("Username can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    printf("Password: ");
    while (1) {
        gets(password);
        fflush(stdin);
        if (strchr(password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }
    user *player = register_user(username, password);

    free(player); //todo open game
}

user *register_user(char username[11], char password[11]) {
    int index = 0;
    struct UserInfo user_info;
    user_info.id = get_last_user_id() + 1;
    strcpy(user_info.username, username);
    user_info.encrypted_password = encrypt_password(password);
    add_user(user_info);
    user *registered_user = (user *) malloc(sizeof(user));
    registered_user->id = index;
    strcpy(registered_user->username, username);
    return registered_user;
}

user *login_user(char username[11], char password[11]) {
    int id = get_user_id(username, password);
    if (id == -1) {
        return NULL;
    }

    user *logged_in_user = (user *) malloc(sizeof(user));
    logged_in_user->id = id;
    strcpy(logged_in_user->username, username);

    return logged_in_user;
}
