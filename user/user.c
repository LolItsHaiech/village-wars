#include "../headers/user.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/file_management.h"
#include "../headers/user_menu.h"
#include "../headers/utils.h"




void register_user_ui() {
    char username[11];
    char password[11], confirm_password[11];

    system("cls");

    printf("Register\n");


    while (1) {
        printf("Username: ");
        fgets(username, 11, stdin);
        fflush(stdin);
        if (strchr(username, ' ')) {
            printf("Username can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        end_string(username);
        break;
    }

    printf("Password: ");
    while (1) {
        fgets(password, 11, stdin);
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

        fgets(confirm_password, 11, stdin);
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

    end_string(password);
    end_string(confirm_password);


    user *player = register_user(username, password);
    user_menu_ui(player);
}

void login_user_ui(bool wrong_user) {
    char username[11];
    char password[11];

    system("cls");

    if (wrong_user) {
        printf("Wrong username or password.\n");
        printf("Try again.\n");
    }


    printf("Login\n");

    while (1) {
        printf("Username: "); // todo unique, no :
        fgets(username,11, stdin);
        fflush(stdin);
        if (strchr(username, ' ')) {
            printf("Username can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        end_string(username);
        break;
    }

    while (1) {
        printf("Password: ");
        fgets(password, 11, stdin);
        fflush(stdin);
        if (strchr(password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        end_string(password);
        break;
    }


    user *player = login_user(username, password);

    if(player == NULL) {
        login_user_ui(true);
    }


    user_menu_ui(player);
}

user *register_user(char username[11], char password[11]) {
    struct UserInfo user_info;
    user_info.id = get_last_user_id() + 1;
    strcpy(user_info.username, username);
    user_info.encrypted_password = encrypt_password(password);
    add_user(user_info);
    user *registered_user = (user *) malloc(sizeof(user));
    registered_user->id = user_info.id;
    strcpy(registered_user->username, username);
    get_village_name(registered_user->village_name, user_info.id);
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
    get_village_name(logged_in_user->village_name, id);



    return logged_in_user;
}
