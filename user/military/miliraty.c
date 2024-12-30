#include "miliraty.h"
#include "../user.h"
#include "../../utils/utils.h"
#include <stdbool.h>

enum MilitaryMenuOptions {VIEW_MILITARIES, ADD_MILITARY, RETURN};

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
                break;
            case ADD_MILITARY:
                break;
            case RETURN:
                exited = true;
        }
    }
}
