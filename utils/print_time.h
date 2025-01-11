#include "time.h"
#include <stdio.h>
#include <time.h>


void get_date_time(char output[] ,time_t *time) {
    struct tm *dt = localtime(time);
    sprintf(output, "%d-%d-%d*%02d:%02d:%02d\n",
           dt->tm_mday, dt->tm_mon + 1, dt->tm_year + 1900,
           dt->tm_hour, dt->tm_min, dt->tm_sec);
}