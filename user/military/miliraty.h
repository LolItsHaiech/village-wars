#ifndef MILIRATY_H
#define MILIRATY_H
#include "../user.h"
#include "add_military.h"
#include "view_military.h"

void military_ui(user* player) {
    bool exited = false;
    while(!exited){
        enum MilitaryMenuOptions input = (enum MilitaryMenuOptions) open_menu("Militaries", (char*[]){
           "View militaries",
           "Add militaries",
           "Return back"
       }, 3);

        switch (input) {
            case VIEW_MILITARIES:
                view_military(player);
                break;
            case ADD_MILITARY:
              add_military(player);
                break;
            case RETURN1:
                exited = true;
        }
    }
}


#endif //MILIRATY_H
