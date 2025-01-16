#ifndef RESOURCE_H
#define RESOURCE_H
#include<stdio.h>
#include "view_resources.h"
#include "add_resource.h"
#include "collecting_resources.h"
#include "upgrade_resource.h"
#include "delete_resources.h"
#include <stdlib.h>

inline void resource_ui(user *player) {
    enum choice { view_resource = 1,collecting_resources, add_resource, upgrade_resource, delete_resource,  };
    int main_choice;
    while (true) {
        system("cls");
        //todo
        printf(
            "resources:\n  1_ view resources\n  2_ collecting resources\n  3_ add new resources\n  4_ upgrade resources\n  5_ delete resources\n  6_ return back");
        scanf("%d", &main_choice);
        fflush(stdin);
        if (main_choice == 6)
            break;
        switch ((enum choice) main_choice) {
            case view_resource:
                view_resources(player);
                break;
            case collecting_resources:
                collecting_resource(player);
                break;
            case add_resource:
                add_new_resources(player);
                break;
            case upgrade_resource:
                upgrade_resources(player);
                break;
            case delete_resource:
                delete_resources(player);
                break;
            default:
                printf("your choice incorrect please try again\n");
        }
    }
}
#endif
