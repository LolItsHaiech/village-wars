#ifndef TIME_H
#define TIME_H
#include <time.h>
#include <stdio.h>

inline void get_date_time(char output[] ,time_t time) {
    struct tm *t = localtime(&time);
    sprintf(output, "%d/%d/%d, %d:%d:%d",
       t->tm_year+1900, t->tm_mon+1, t->tm_mday,  t->tm_hour, t->tm_min,t->tm_sec);
}

#endif //TIME_H

