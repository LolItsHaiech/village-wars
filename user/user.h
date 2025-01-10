#ifndef USER_H
#define USER_H
#include <stdbool.h>
#include <time.h>
enum Resouce {
    WOOD,
    FOOD,
    STONE

};
enum staus{
  adding,
  upgrading,
  deleting,
  finished


};

enum Buildings {
    FOOD_STORAGE,
    WOOD_STORAGE,
    STONE_STORAGE,
    BARRACK
};

typedef struct user {
    int id;
    char username[11];
    char village_name[11];
    int encrypted_password;

    struct {
        int wood_count;
        int food_count;
        int stone_count;
    } resources;


    struct {
        int warrior;
        int archer;
        int rider;
    } soldiers_count;

    struct {
        enum Resouce resource;
        int lvl;
        bool is_working;
        enum staus status;
        time_t change_time;
        time_t finishing_time;
         int collect_rate;
    } resources_generators[6];

    struct {
        enum Buildings building_type;
        int lvl;
        time_t change_time;
     time_t finishing_time;
        int storage;
        enum staus status;
    } buildings[6];
} user;



int encrypt_password(char [11]);
void login_user_ui();
void register_user_ui();
void change_password_ui(user *);
user *register_user(char [11], char [11]);

user *login_user(char [11], char [11]);

#endif //USER_H
