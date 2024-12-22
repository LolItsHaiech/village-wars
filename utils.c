#include "headers/utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str2int(char* string, int length) {
    int result=0;
    int i;
    for (i = 0; i<length; ++i) {
        result = 10*result + ((int)string[i] - (int)'0');
    }
    return result;
}


int encrypt_password(char *password) {
    int res = 0;
    int i;
    for (i = 0; password[i] != '\0'; ++i)
        res += pow(2, i + 1) * (int) password[i];
    return res;
}


void add_whitespace(char* string, int str_size) {
    int i;
    for (i = strlen(string); i < str_size; ++i) {
        string[i] = ' ';
    }
    string[str_size+1] = '\0';
}

void end_string(char* string) {
    int i=0;
    while(1) {
        if(string[i] == '\n' || string[i] == ' ' ||
            string[i] == '\0' || string[i] == ':') {

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

    int input;
    scanf("%d", &input);
    fflush(stdin);
    return input;
}
