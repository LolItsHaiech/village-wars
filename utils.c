#include "headers/utils.h"

#include <math.h>
#include <string.h>

int str2int(char* string, int length) {
    int result=0;
    int i;
    for (i = 0; i<length; ++i) {
        result = 10*result + ((int)string[i] - '0');
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


void add_whitespace(char* string, int fill) {
    int i;
    for (i = strlen(string); i < fill; ++i) {
        string[i] = ' ';
    }
    string[fill+1] = '\0';
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

