#include <stdio.h>
#include <stdlib.h>

#include "../headers/file_management.h"
#include "../headers/user.h"
#include "../headers/utils.h"

enum UserMenuOptions {
    RENAME_VILLAGE = 1,
    RESOURCES,
    BUILDINGS,
    MILITARIES,
    ATTACKS,
    CHANGE_PASSWORD,
    LOGOUT
};


void rename_village_ui(user*);

void user_menu_ui(user *player) {
    char user_menu_title[30];
    char village_name[11];
    get_user_property(village_name, 11, player->id, VILLAGE_NAME);
    sprintf(user_menu_title, "User Menu(%s)", village_name);


    char* user_menu_options[7] = {
        "Change village name",
        "Resources",
        "Building",
        "Militaries",
        "Attacks",
        "Change password",
        "Logout", //todo remove account
    };
    enum UserMenuOptions input = (enum UserMenuOptions)open_menu(user_menu_title, user_menu_options, 7);
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
            break;
        case CHANGE_PASSWORD:
            change_password_ui(player);
            break;
        case LOGOUT: // todo are you sure?,
            free(player);
            return;
    }


    free(player);
}

void rename_village_ui(user* player) {
    char new_name[11];
    system("cls");
    printf("Change village name\n\n");
    printf("Enter new village name: ");
    fgets(new_name, 11, stdin);
    fflush(stdin);
    end_string(new_name);
    set_user_property(new_name, player->id, VILLAGE_NAME);
    user_menu_ui(player);
}
