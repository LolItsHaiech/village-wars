#include <stdbool.h>
#include <stdlib.h>

struct user {
    int id;
    char username[10];
};


void login_user_ui(bool);
void login_user_ui();
void register_user_ui();

void login_user_ui(bool wrong_user) {
    char username[10];
    char password[10];

    system("cls");

    printf("Login\n");

    if (wrong_user) {
        printf("Wrong username or password.\n");
        printf("Try again.\n");
    }

    printf("Username: ");
    scanf("%s", username);
    //todo: clear cache
    printf("Password: "); // todo: not show password?
    scanf("%s", password);
    struct user* player = login_user(username, password);
    if(player==NULL) {
        login_user_ui(true);
    }


    // todo open game
}

void login_user_ui() {
    login_user_ui(false);
}

void register_user_ui() {
    char username[10];
    char password[10];

    printf("Register\n");

    printf("Username: ");
    scanf("%s", username);
    //todo: clear cache
    printf("Password: "); // todo: not show password?
    scanf("%s", password);
    struct user* player = create_user(username, password);
    if(player==NULL) {
        login_user_ui(true);
    }

    //todo open game
}
