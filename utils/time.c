#include "time.h"

#include <stdio.h>
#include<time.h>

void get_date_time(char output[] ,time_t *time) {
    struct tm *t = localtime(time);
    sprintf(output, "%d/%d/%d, %d:%d:%d",
        t->tm_mday, t->tm_mon, t->tm_year+1900, t->tm_hour, t->tm_min, t->tm_sec);
}
