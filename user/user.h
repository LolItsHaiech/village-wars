#ifndef USER_H
#define USER_H
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_management.h"
#include "../utils/input.h"
#include "../utils/utils.h"
#include "attacks/attacks.h"
#include "resources_building/resource.h"
#include "resources_building/building.h"


inline user *register_user(char username[11], char password[11]);

inline void user_menu_ui(user *player);


inline void register_user_ui() {
    system("cls");

    while (1) {
        char username[11];
        char password[11], confirm_password[11];


        printf("Register\n\n");

        printf(""
               "  *Username and password should at least be 5 characters long.\n"
               "  *Username should be unique.\n\n");

        while (!read_str_input("Username", username, 11, (bool (*[])(char *)){
                                   &unique_username_filter,
                                   &min_length_filter
                               }, 2)) {
            if (!read_confirmation("Bad input, try again?", false)) {
                return;
            }
        }

        while (!read_str_input("Password", password, 11, (bool (*[])(char *)){&min_length_filter}, 1)) {
            if (!read_confirmation("Bad input, try again?", false)) {
                return;
            }
        }
        while (!read_str_input("Confirm password", confirm_password, 11, (bool (*[])(char *)){&min_length_filter}, 1)) {
            if (!read_confirmation("Bad input, try again?", false)) {
                return;
            }
        }

        if (strcmp(password, confirm_password) == 0) {
            user *player = register_user(username, password);
            if (player == NULL) {
                system("cls");
                printf("Something went wrong!\n");
                sleep(1);
                return;
            }
            user_menu_ui(player);
            break;
        }

        printf("Password and confirm password didn't match.\n\n");
    }
}


inline void login_user_ui() {
    while (1) {
        char username[11];
        char password[11];

        system("cls");

        printf("Login\n\n");

        while (!read_str_input("Username", username, 11, NULL, 0)) {
        }
        while (!read_str_input("Password", password, 11, NULL, 0)) {
        }


        user *player = get_user(username, password);

        if (player == NULL) {
            printf("Username or password is wrong!\n");
            if (!read_confirmation("Try again?", false)) {
                return;
            }
        } else {
            user_menu_ui(player);
            return;
        }
    }
}


inline void change_password_ui(user *player) {
    bool exited = false;
    while (!exited) {
        char old_password[11];
        char new_password[11];
        char new_password_confirm[11];

        system("cls");

        printf("Change password\n\n");


        while (!read_str_input("Old password", old_password, 11, NULL, 0)) {
        }
        while (!read_str_input("New password", new_password, 11, NULL, 0)) {
        }
        while (!read_str_input("Confirm New password", new_password_confirm, 11, NULL, 0)) {
        }

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

inline user *register_user(char username[11], char password[11]) {
    user *registered_user = (user *) malloc(sizeof(user));
    registered_user->id = get_last_user_id() + 1;
    strcpy(registered_user->username, username);
    strcpy(registered_user->village_name, username);
    registered_user->encrypted_password = encrypt_password(password);
    registered_user->resources.food_count = 0;
    registered_user->resources.wood_count = 0;
    registered_user->resources.stone_count = 0;

    // todo dont forget
    registered_user->soldiers_count.warrior = 100;
    registered_user->soldiers_count.archer = 100;
    registered_user->soldiers_count.rider = 100;
    int i;
    for (i = 0; i < 6; ++i) {
        registered_user->buildings[i].lvl = 0;
        registered_user->buildings[i].status = DEFAULT;
        registered_user->resources_generators[i].lvl = 0;
        registered_user->resources_generators[i].status = DEFAULT;
    }

    for (i = 0; i < 16; ++i)
        registered_user->soldiers[i].number_soldiers=0;

    bool success = add_user(registered_user);
    if (!success) {
        free(registered_user);
        return false;
    }
    return registered_user;
}


inline void rename_village_ui(user *);

inline void user_menu_ui(user *player) {
    bool exited = false;
    while (!exited) {
        char user_menu_title[30];
        sprintf(user_menu_title, "User Menu(%s)", player->village_name);


        char *user_menu_options[7] = {
            "Change village name",
            "Resources",
            "Building",
            "Militaries",
            "Attacks",
            "Change password",
            "Logout", //todo remove account
        };
        enum UserMenuOptions input = (enum UserMenuOptions) open_menu(user_menu_title, user_menu_options, 7);
        switch (input) {
            case RENAME_VILLAGE:
                rename_village_ui(player);
                break;
            case RESOURCES:
                resource_ui(player);
                break;
            case BUILDINGS:
                building_ui(player);
                break;
            case MILITARIES:
                break;
            case ATTACKS:
                attack_ui(player);
                break;
            case CHANGE_PASSWORD:
                change_password_ui(player);
                break;
            case LOGOUT:
                if (read_confirmation("Are you sure?", true)) {
                    save_user(player);
                    free(player);
                    exited = true;
                }
        }
    }
}

inline void rename_village_ui(user *player) {
    system("cls");
    printf("Change village name\n\n");
    while (!read_str_input("New village name", player->village_name, 11, NULL, 0)) {
    }
    save_user(player);
}


#endif //USER_H
