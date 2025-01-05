#include <stdio.h>
#include <stdlib.h>

#include "../file_management.h"
#include "../utils/input.h"
#include "user.h"
#include "../utils/utils.h"

enum UserMenuOptions {
    RENAME_VILLAGE = 1,
    RESOURCES,
    BUILDINGS,
    MILITARIES,
    ATTACKS,
    CHANGE_PASSWORD,
    LOGOUT
};


void rename_village_ui(user *);

void user_menu_ui(user *player) {
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
                break;
            case BUILDINGS:
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

void rename_village_ui(user *player) {
    system("cls");
    printf("Change village name\n\n");
    while (!read_str_input("New village name", player->village_name, 11, NULL, 0));
    save_user(player);
}
