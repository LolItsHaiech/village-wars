#include<stdio.h>
#include "user.c"

enum MenuOptions { LOGIN = 1, REGISTER, EXIT };

int main(void) {
    printf(""
        "Main Menu\n"
        "1- Login\n"
        "2- Register\n"
        "3- Exit\n");
    enum MenuOptions input; // todo: if char or not 1-3 -> crash
    scanf("%d", &input);
    //todo: clear cache
    switch (input) {
        case LOGIN:
            login_user_ui();
            break;
        case REGISTER:
            register_user_ui();
            break;
        case EXIT:
            char inp;
            do {
                system("cls");
                printf("Are you sure?(y/n)\n");
                scanf("%c", &inp);
                if(input=='y') {
                    return 0;
                }
                if (input == 'n') {
                    main(); //todo: maybe no recursive?
                }
                //todo: clear cache
            } while(1);
    }
    return 0;
}
