#include <stdio.h>
#include <stdlib.h>
#include "admin_mode.h"

#include  "user_mode.h"
#include "lib.h"
state_t viewUserMode(user_data_t *data){
    state_t l_error = n_ok;
    u8 p_id[6],flag,i,x;
    printf("Please enter your ID. \n");
    scanf("%s",p_id);
    for (i =0 ; i<index_;i++){
        if(strcmp(p_id, data[i].id) == 0){
            flag =1;
            x =i;
            break;
        }
        else {
            flag =0;
        }
    }
    if (flag == 1){


        printf("Patient Information. \n");
        printf("User %d:\n", x + 1);
        printf("Name: %s\n", data[x].name);
        printf("Gender: %c\n", data[x].gender);
        printf("Age: %d\n", data[x].age);
        printf("ID: %s\n", data[x].id);
        printf("Time: %s\n", data[x].slot);
        l_error = ok;
    }
    else {
        l_error = user_not_exist;
    }
    return l_error;
}
void viewAllReservation(user_data_t *data,u8 inx){
   u8 i;

    for ( i = 0; i <=inx; i++) {
        printf("User %d:\n", i + 1);
        printf("Name: %s\n", data[i].name);
        printf("Gender: %c\n", data[i].gender);
        printf("Age: %d\n", data[i].age);
        printf("ID: %s\n", data[i].id);
        printf("Time: %s\n", data[i].slot);
        printf("\n");
    }

}
