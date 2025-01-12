#include <stdbool.h>
#include "user/user.h"
#include "utils/input.h"
#include "utils/utils.h"


int main() {
    bool exited = false;
    while (!exited) {
        char *main_menu_options[3] = {
            "Login",
            "Register",
            "Exit"
        };
        enum MenuOptions input = (enum MenuOptions) open_menu("Main Menu", main_menu_options, 3);

        switch (input) {
            case LOGIN:
                login_user_ui();
                break;
            case REGISTER:
                register_user_ui();
                break;
            case EXIT:
                exited = read_confirmation("Are you sure?", true);
        }
    }
    return 0;
}
