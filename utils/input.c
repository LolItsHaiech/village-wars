#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool read_str_input(char *title, char *output, int output_size, bool (*filters[])(char *), int filter_count) {
    printf("%s:", title);
    fgets(output, output_size,stdin);
    fflush(stdin);
    end_string(output);
    int i;
    for (i = 0; i < filter_count; ++i) {
        if (!(*filters[i])(output))
            return false;
    }
    return true;
}

int read_int_input(char* title, int min, int max) {
    int res;
    while(1){
        printf("%s:", title);
        scanf("%d", &res);
        fflush(stdin);
        if (res>=min && res <= max)
            return res;
        printf("%s can't be less that %d or more than %d.", title, min, max);
    }
}

bool read_confirmation(char *title, bool cls) {
    char sure;
    while (1) {
        if (cls)
            system("cls");
        printf("%s(y/n)\n", title);
        scanf("%c", &sure);
        fflush(stdin);
        if (sure == 'y')
            return true;
        if (sure == 'n')
            return false;
    }
}
