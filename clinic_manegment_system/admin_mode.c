#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "admin_mode.h"


static void Get_name(u8 *p_name,user_data_t *data,u8 inx);
static void Get_age(u32 p_age,user_data_t *data,u8 inx);
static void Get_gender(u8 p_gender,user_data_t *data,u8 inx);
static void Get_ID(u8 *p_id, user_data_t *data, state_t *err);
static void Print_data(user_data_t *data);
static void Print_1_userdata(user_data_t *data,u32 inx);


user_data_t UserDataSaved[] = {
                                    {"Ahmed" , 'm', 56, "12345","2:30pm"},
                                    {"mohamed", 'm', 59,"54321","4pm"},
                                    {"asmaa", 'f' , 45, "98765","3:30pm"},
                                    {"aya", 'f', 37, "56789","4:30pm"}
                                    };

u32 index_= sizeof(UserDataSaved)/ sizeof(user_data_t) ;


//user_data_t *NewData;
//u32 NUM_OF_SAVED_DATA = 4;//sizeof(UserDataSaved)/sizeof(user_data_t);
const u32 password =1234;
state_t check_pass(){
    state_t L_error = n_ok;
    u32 flage=1 ,i,pass;
    printf("Please Enter Password: ");
    scanf("%d",&pass);
    for (i =0;i<2;i++){
        if (pass== password){
            //printf("Welcome to our system...\n");
            L_error = ok;
            break;
        }
        else{
            flage++;
            printf("wrong password, try again..\n ");
            printf("Please Enter Password: \n");
            scanf("%d",&pass);
        }
    }
    if (flage == 3){
        L_error =  wrong_pass;
    }
    else {
        L_error = ok;
    }
    return L_error;
}
state_t add_new_patient_record(user_data_t *data,u32 inx){
    state_t L_error = n_ok;
   // u32 ind = inx-1;
    u8 p_name[20],p_id[6],p_gender,i,x =0;
    u32 p_age;

    printf("Please Enter Patient Name: ");
    Get_name(p_name,data,inx);
    //strcpy(data[inx].name,p_name);

    printf("Pleas Enter Patient Age: ");
    Get_age(p_age,data,inx);

    printf("Pleas Enter Patient Gender f/m: ");
    Get_gender(p_gender,data,inx);

    printf("Pleas Enter Patient ID it must be 5 digit: ");
    //Get_ID(p_id,data,&L_error);
    scanf("%s", p_id);
    for (i = 0; i <=inx; i++) {
        if (strcmp(p_id, data[i].id) == 0) {
            L_error = user_exist;

            break;
        }
    }

    if (L_error == user_exist){
        strcpy(data[inx].name,"");
        data[inx].age = 0;
        data[inx].gender = "";
        return user_exist;
    }
    else {
        strcpy(data[inx].id,p_id);

        L_error = ok;
    }
    for ( i = 0; i <=inx; i++) {
        printf("User %d:\n", i + 1);
        printf("Name: %s\n", data[i].name);
        printf("Gender: %c\n", data[i].gender);
        printf("Age: %d\n", data[i].age);
        printf("ID: %s\n", data[i].id);
        printf("Time: %s\n", data[i].slot);
        printf("\n");
    }
    return L_error;
}
state_t edit_patient_record(user_data_t *data){
    state_t L_error = n_ok;
    u8 i,x,flag =0,h;
    u8 p_name[20],p_id[6],p_gender;
    u32 p_age;
    printf("Please Enter Patient ID: \n");
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
        printf("Hello, There are your data.\n");
        printf("Patient Information. \n");
        printf("User %d:\n", x + 1);
        printf("Name: %s\n", data[x].name);
        printf("Gender: %c\n", data[x].gender);
        printf("Age: %d\n", data[x].age);
        printf("ID: %s\n", data[x].id);
        printf("Time: %s\n", data[x].slot);
        printf("************************************\n");
        printf(" which data you want to modify ? \n");
        printf("************************************\n");
        printf("1- Patient Name.\n");
        printf("2- Patient Age.\n");
        printf("3- Patient Gender.\n");
        printf("4- Patient ID.\n");
        scanf(" %c",&h);
        switch (h){
        case '1':
            printf("Please Enter New Name.\n");
            Get_name(p_name,data,x);
            //strcpy(data[inx].name,p_name);
            L_error = ok;
            break;
        case '2':
            printf("Please Enter New Age.\n");

            Get_age(p_age,data,x);
            L_error = ok;
            break;
        case '3':
            printf("Please Enter New Gender.\n");
            Get_gender(p_gender,data,x);
            L_error = ok;
            break;
        case '4':
            printf("Please Enter New ID.\n");
            //Get_ID(p_id,data,&L_error);
            scanf("%s", p_id);
            for (i = 0; i <255; i++) {
                if (strcmp(p_id, data[i].id) == 0) {
                    L_error = user_exist;

                    break;
                }
            }
            if (L_error == user_exist){

                return user_exist;
            }
            else {
                for (i =0;i< 5;i++){
                    data[x].id[i] = p_id[i];
                }
            }
            L_error = ok;
            break;
        default:
            L_error = OutOfRange;

        }

    }
    else {
        printf("This user is not exist..\n");
        printf("Thank you for using our system..\n");
        return user_not_exist;
    }
    printf("Patient Information. \n");
    printf("User %d:\n", x + 1);
    printf("Name: %s\n", data[x].name);
    printf("Gender: %c\n", data[x].gender);
    printf("Age: %d\n", data[x].age);
    printf("ID: %s\n", data[x].id);
    printf("Time: %s\n", data[x].slot);
    printf("\n");
    return L_error;


}

state_t reserve_a_slot_with_the_doctor(user_data_t *data){
    state_t L_error = n_ok;
    u8 c,i,*g,found =0,p_id[6],x;
    printf("please enter patient ID.\n");
   // Get_ID(p_id,data,&L_error);
    scanf("%s", p_id);
    for (i = 0; i <255; i++) {
        if (strcmp(p_id, data[i].id) == 0) {
            L_error = user_exist;
;
            break;
        }
    }
    if (L_error == user_exist){
        for (i =0 ; i<255;i++){
            if(strcmp(p_id, data[i].id) == 0){
                x =i;
                break;
            }
        }
    }
    else{
        return user_not_exist;
    }
label:
    printf("please,Book the right date: \n");
    printf("1- 2pm.\n");
    printf("2- 2:30pm.\n");
    printf("3- 3pm.\n");
    printf("4- 3:30pm.\n");
    printf("5- 4pm.\n");

    scanf(" %c",&c);
    switch(c){
    case '1':
        g = "2pm";
        for (i =0 ; i<255; i++){
            if (strcmp(data[i].slot,g) == 0){
                printf("Sorry choose another date \n");
                found =1;
                break;
            }
        }
        if (found == 0){
            strcpy(data[x].slot, g);
            Print_1_userdata(data,x);
        }
        else{
            found =0;
            goto label;
        }
        break;
    case '2':
        g = "2:30pm";
        for (i =0 ; i<255; i++){
            if (strcmp(g,data[i].slot) == 0){
                printf("Sorry choose another date \n");
                found =1;
                break;
            }
        }
        if (found == 0){
            strcpy(data[x].slot, g);
            Print_1_userdata(data,x);
        }
        else{
            found =0;
            goto label;
        }
        break;
     case '3':
        g = "3pm";
        for (i =0 ; i<255; i++){
            if (strcmp(g,data[i].slot) == 0){
                printf("Sorry choose another date \n");
                found =1;
                break;
            }
        }
        if (found == 0){
            strcpy(data[x].slot, g);
            Print_1_userdata(data,x);
        }
        else{
            found =0;
            goto label;
        }
        break;
     case '4':
        g = "3:30pm";
        for (i =0 ; i<255; i++){
            if (strcmp(g,data[i].slot) == 0){
                printf("Sorry choose another date \n");
                found =1;
                break;
            }
        }
        if (found == 0){
            strcpy(data[x].slot, g);
            Print_1_userdata(data,x);
        }
        else{
            found =0;
            goto label;
        }
        break;
    case '5':
        g = "4pm";
        for (i =0 ; i<255; i++){
            if (strcmp(g,data[i].slot )== 0){
                printf("Sorry choose another date \n");
                found =1;
                break;
            }
        }
        if (found == 0){
            strcpy(data[x].slot, g);

            Print_1_userdata(data,x);
        }
        else{
            found =0;
            goto label;
        }
        break;
    default:
        printf("This time not available.\n");
        goto label;
    }

}
state_t cancel_reservation(user_data_t *data,u32 inx){
    state_t L_error = n_ok;
    u8 p_id[6],i,x,index_1;
    u8 g[] = "";
    printf("Enter the ID.\n");
   // Get_ID(p_id,data,&L_error);
    scanf("%s", p_id);
    for (i = 0; i <inx; i++) {
        if (strcmp(p_id, data[i].id) == 0) {
            L_error = user_exist;
            break;
        }
    }

    if (L_error == user_not_exist){
        return user_not_exist;
    }
    else{
        for (i =0 ; i<inx;i++){
            if(strcmp(p_id, data[i].id) == 0){
                x =i;
                L_error = ok;
                break;
            }

        }

    }
    strcpy(data[x].slot , g);
    printf("These are the appointments booked today\n");


    for ( i = 0; i <inx; i++) {
        printf("User %d:\n", i + 1);
        printf("Name: %s\n", data[i].name);
        printf("Gender: %c\n", data[i].gender);
        printf("Age: %d\n", data[i].age);
        printf("ID: %s\n", data[i].id);
        printf("Time: %s\n", data[i].slot);
        printf("\n");
    }
    return L_error;
}
/* Static Function*/
/////////////////////////////
////////////////////////////
//////////////////////////
//
//
static void Get_name(u8 *p_name,user_data_t *data, u8 inx){
    u8 i,x=0;
    for (i =0 ;i< 20;i++){
        p_name[i] ='\0';
    }
    scanf(" %[^\n]s", p_name);
/*
    while (p_name[x] != '\0') {
        x++;
    }

    for (i = 0; i < x; i++) {
        data->name[i] = p_name[i];
    }*/
        strcpy(data[inx].name,p_name);

}
static void Get_age(u32 p_age,user_data_t *data,u8 inx){
    scanf("%d",&p_age);
    data[inx].age = p_age;

}
static void Get_gender(u8 p_gender,user_data_t *data,u8 inx){

    scanf(" %c",&p_gender);
    if (p_gender != 'f' && p_gender != 'm'){
        p_gender = 'm';//default
    }
    data[inx].gender = p_gender;
}
 /*static void Get_ID(u8 *p_id, user_data_t *data, state_t *err) {
    u8 i, f = 0;
    scanf("%s", p_id); // Read up to 5 characters to match the ID size
    printf("xxxxxxxxxxxxxxxxxxxxxx%d",index_);

    for (i = 0; i <20; i++) {
        if (strcmp(p_id, data[i].id) == 0) {
            *err = user_exist;
            f = 1;
            break;
        }
    }
    if (f == 0) {
        *err = user_not_exist;
    }
    printf("-------------%d",*err);
}*/
/*static void Print_data(user_data_t *data){
    u8 i;
    for ( i = 0; i <index_; i++) {
        printf("User %d:\n", i + 1);
        printf("Name: %s\n", data[i].name);
        printf("Gender: %c\n", data[i].gender);
        printf("Age: %d\n", data[i].age);
        printf("ID: %s\n", data[i].id);
        printf("Time: %s\n", data[i].slot);
        printf("\n");
    }
}*/
static void Print_1_userdata(user_data_t *data,u32 inx){
            printf("Hello, There are your data.\n");
            printf("Patient Information. \n");
            printf("User %d:\n", inx + 1);
            printf("Name: %s\n", data[inx].name);
            printf("Gender: %c\n", data[inx].gender);
            printf("Age: %d\n", data[inx].age);
            printf("ID: %s\n", data[inx].id);
            printf("Time: %s\n", data[inx].slot);
}
