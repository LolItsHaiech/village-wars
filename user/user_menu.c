#include <stdio.h>
#include <stdlib.h>

#include "../headers/user.h"

enum UserMenuOptions {
    RENAME_VILLAGE = 1,
    RESOURCES,
    BUILDINGS,
    MILITARIES,
    ATTACKS,
    CHANGE_PASSWORD,
    LOGOUT
};

void user_menu_ui(user *player) {
    system("cls");



    printf(""
        "User Menu(%s):\n"
        "1- Change village name\n"
        "2- Resources\n"
        "3- Building\n"
        "4- Militaries\n"
        "5- Attacks\n"
        "6- Change password\n"
        "7- Logout\n",
        player->village_name);

    enum UserMenuOptions input;
    scanf("%d", &input);
    fflush(stdin);
    switch (input) {
        case RENAME_VILLAGE:
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
            break;
        case LOGOUT: // todo are you sure?
            free(player);
            return;
    }


    free(player);
}
