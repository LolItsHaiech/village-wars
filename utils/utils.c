#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int encrypt_password(char *password) {
    int res = 0;
    int i;
    for (i = 0; password[i] != '\0'; ++i)
        res += pow(2, i + 1) * (int) password[i];
    return res;
}


void end_string(char* string) {
    int i=0;
    while(1) {
        if(string[i] == '\n' || string[i] == '\0') {

            string[i] = '\0';
            return;
        }
        i++;
    }
}


int open_menu(char* title, char** options, int options_count) {
    system("cls");
    printf("%s\n\n", title);
    int i;
    for (i = 0; i < options_count; ++i)
        printf("  %d - %s\n", i+1, options[i]);
    printf("\n");

    int input;
    scanf("%d", &input);
    fflush(stdin);
    return input;
}
