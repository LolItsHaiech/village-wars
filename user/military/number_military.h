

#ifndef NUMBER_MILITARY_H
#define NUMBER_MILITARY_H
#include"../user.h"
inline int find_empty_soldier_builder(user *player) {
    int i;
    for (i = 0; i < 18; i++) {
        if (player->soldiers[i].number_soldiers== 0 )
             return i;
    }

}
inline int numbers_soldiers_creating(user *player) {
    int i,number_soldier_create=0;
    for (i = 0; i < 18; i++) {
        if (player->soldiers[i].number_soldiers!= 0 )
            number_soldier_create++;
    }
return number_soldier_create;
}
//todo number empty state
#endif //NUMBER_MILITARY_H
