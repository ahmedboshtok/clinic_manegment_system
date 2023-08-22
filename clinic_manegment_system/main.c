#include <stdio.h>
#include <stdlib.h>
#include "admin_mode.h"
#include "user_mode.h"
#include "app.h"
#include "lib.h"
user_data_t *New_Data;


int main()
{
    state_t app_state;
    char c;
    int inxx = index_ -2;
    while(1 ){
        c = stard_app();
        app_state = app(c,++inxx);
        if (app_state == closeSystem){
            break;
        }
    }


    return 0;
}
