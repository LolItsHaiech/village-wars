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

    printf("Register\n\n");


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

    while (1) {
        printf("Password: ");
        fgets(password, 11, stdin);
        fflush(stdin);
        if (strchr(password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Confirm password: ");
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


    printf("Login\n\n");

    while (1) {
        printf("Username: "); // todo unique, no :
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

    if (player == NULL) {
        login_user_ui(true);
    }


    user_menu_ui(player);
}


void change_password_ui(user* player) {
    char old_password[11];
    char new_password[11];
    char new_password_confirm[11];


    system("cls");
    printf("Change password\n\n");


    while (1) {
        printf("Old password: ");
        fgets(old_password, 11, stdin);
        fflush(stdin);
        if (strchr(old_password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }
    while (1) {
        printf("New password: ");
        fgets(new_password, 11, stdin);
        fflush(stdin);
        if (strchr(new_password, ' ')) {
            printf("Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }
    while (1) {
        printf("Confirm password: ");
        fgets(new_password_confirm, 11, stdin);
        fflush(stdin);
        if (strchr(new_password_confirm, ' ')) {
            printf("Confirm Password can't contain the character space. (' ')\n");
            printf("Try again.\n");
            continue;
        }
        if (strcmp(new_password, new_password_confirm) != 0) {
            printf("Password and confirm password do not match.\n");
            printf("Try again.\n");
            continue;
        }
        break;
    }

    end_string(old_password);
    end_string(new_password);
    end_string(new_password_confirm);

    if(change_password(player->id, old_password,new_password)) {
        user_menu_ui(player);
    } else {
        char inp;
        printf("\nPassword was not right\n");
        printf("Try again?(y/n)");
        scanf("%c", &inp);
        fflush(stdin);
        if(inp=='y') {
            change_password_ui(player);
        } else { //todo what if not n
            user_menu_ui(player);
        }
    }
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

    user* logged_in_user = (user *) malloc(sizeof(user));

    logged_in_user->id = id;
    strcpy(logged_in_user->username, username);
    get_village_name(logged_in_user->village_name, id);


    return logged_in_user;
}
