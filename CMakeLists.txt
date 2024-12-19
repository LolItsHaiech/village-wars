cmake_minimum_required(VERSION 3.29)
project(village_wars C)

set(CMAKE_C_STANDARD 90)

add_executable(village_wars main.c
        user/user.c
        file_management.c
        headers/user.h
        headers/file_management.h
        utils.c
        headers/utils.h
        user/user_menu.c
        headers/user_menu.h)
