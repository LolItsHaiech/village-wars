#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headers/user.h"
#include "headers/utils.h"

enum MenuOptions { LOGIN = 1, REGISTER, EXIT };

int main() {
    bool exited = false;
    while(!exited){
        char* main_menu_options[3] = {
            "Login",
            "Register",
            "Exit"
        };
        enum MenuOptions input = (enum MenuOptions) open_menu("Main Menu", main_menu_options , 3);

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
                    exited=true;
                    break;
                }
                if (sure == 'n') {
                    break;
                }
            }
        }
    }
    return 0;
}
