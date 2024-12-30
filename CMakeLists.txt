cmake_minimum_required(VERSION 3.29)
project(village_wars C)

set(CMAKE_C_STANDARD 90)

add_executable(village_wars main.c
        user/user.c
        file_management.c
        user/user.h
        file_management.h
        utils/utils.c
        utils/utils.h
        user/user_menu.c
        user/user_menu.h
        utils/input.c
        utils/input.h
        headers/constants.h
        user/military/miliraty.c
        user/military/miliraty.h
        user/attacks/attacks.c
        user/attacks/attacks.h
        utils/time.c
        utils/time.h
)
