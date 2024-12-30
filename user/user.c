#include "user.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../file_management.h"
#include "../utils/input.h"
#include "user_menu.h"
#include "../utils/utils.h"


void register_user_ui() {
    system("cls");

    while (1) {
        char username[11];
        char password[11], confirm_password[11];


        printf("Register\n\n");

        while (!read_str_input("Username", username, 11, (bool (*[])(char *)){&unique_username_filter}, 1));
        while (!read_str_input("Password", password, 11, NULL, 0)); //todo minimum length filter
        while (!read_str_input("Confirm password", confirm_password, 11, NULL, 0));

        if (strcmp(password, confirm_password) == 0) {
            user *player = register_user(username, password);
            user_menu_ui(player);
            break;
        }

        printf("Password and confirm password didn't match.\n\n");
    }
}


void login_user_ui() {
    while (1) {
        char username[11];
        char password[11];

        system("cls");

        printf("Login\n\n");

        while (!read_str_input("Username", username, 11, NULL, 0));
        while (!read_str_input("Password", password, 11, NULL, 0));


        user *player = get_user(username, password);

        if (player == NULL) {
            printf("Username or password is wrong!\n");
            if(!read_confirmation("Try again?", false)) {
                return;
            }
        } else {
            user_menu_ui(player);
            return;
        }
    }
}


void change_password_ui(user *player) {
    bool exited = false;
    while (!exited) {
        char old_password[11];
        char new_password[11];
        char new_password_confirm[11];

        system("cls");

        printf("Change password\n\n");


        while (!read_str_input("Old password", old_password, 11, NULL, 0));
        while (!read_str_input("New password", new_password, 11, NULL, 0));
        while (!read_str_input("Confirm New password", new_password_confirm, 11, NULL, 0));

        if (strcmp(new_password, new_password_confirm) != 0) {
            printf("New password and its confirmation are not the same.\n");
            exited = !read_confirmation("Try Again?", false);
            continue;
        }

        if (player->encrypted_password != encrypt_password(old_password)) {
            printf("Old password is incorrect.\n");
            exited = !read_confirmation("Try Again?", false);
            continue;
        }

        player->encrypted_password = encrypt_password(new_password);
        save_user(player);
        break;
    }
}

user *register_user(char username[11], char password[11]) {
    user *registered_user = (user *) malloc(sizeof(user));
    registered_user->id = get_last_user_id() + 1;
    strcpy(registered_user->username, username);
    strcpy(registered_user->village_name, username);
    registered_user->encrypted_password = encrypt_password(password);
    registered_user->resources.food_count = 0;
    registered_user->resources.wood_count = 0;
    registered_user->resources.stone_count = 0;
    add_user(registered_user);
    return registered_user;
}
