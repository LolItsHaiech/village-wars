#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headers/user.h"

enum MenuOptions { LOGIN = 1, REGISTER, EXIT };

enum MenuOptions main_menu_ui();

int main() {
    enum MenuOptions input = main_menu_ui();

    switch (input) {
        case LOGIN:
            login_user_ui(false);
            break;
        case REGISTER:
            register_user_ui();
            break;
        case EXIT:
            char sure;
            while (1) {
                system("cls");
                printf("Are you sure?(y/n)\n");
                scanf("%c", &sure);
                fflush(stdin);
                if (sure == 'y') {
                    return 0;
                }
                if (sure == 'n') {
                    main();
                }
            }
    }

    return 0;
}

enum MenuOptions main_menu_ui() {
    system("cls");

    printf(""
        "Main Menu\n"
        "1- Login\n"
        "2- Register\n"
        "3- Exit\n");
    enum MenuOptions input;
    scanf("%d", &input);
    fflush(stdin);
    return input;
}
