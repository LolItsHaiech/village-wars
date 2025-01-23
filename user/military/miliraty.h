#ifndef MILIRATY_H
#define MILIRATY_H
#include "../user.h"
#include<stdio.h>

#include <stdlib.h>
#include "add_military.h"
#include "view_military.h"
#include <unistd.h>

void military_ui(user* player){
    enum choice { view_resource = 1, add_resource };
    int main_choice;
    while (true) {
        system("cls");
        printf(
            "military:\n1_ view military\n2_ add new military\n3_ return back");
        scanf("%d", &main_choice);
        if (main_choice == 3)
            break;
        switch ((enum choice) main_choice) {
            case view_resource:
             view_military(player);
            break;

            case add_resource:
                add_military(player);
             break;
            default:
                printf("your choice incorrect please try again\n");
                sleep(1);
            }
    }
}
#endif //MILIRATY_H
