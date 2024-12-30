#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

bool read_str_input(char*, char*, int, bool (*[])(char*), int);
bool read_confirmation(char *title, bool cls);
int read_int_input(char* title, int min, int max);

#endif //INPUT_H
