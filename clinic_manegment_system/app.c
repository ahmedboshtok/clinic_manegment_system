#include <stdio.h>
#include <stdlib.h>
#include "admin_mode.h"
#include "app.h"

/*
    stard app function ask user to choose mode
    1 for admin mode
    2 for user mode
    */

char stard_app(){
    char mode;
    while(1){
        printf("Please Choose  Mode..\n");
        printf("1- Admin Mode.\n");
        printf("2- User mode.\n");
        printf("3- Close system.\n");
        scanf(" %c",&mode);
        if (mode == '1' || mode == '2'){

            return mode;
        }
        else {
            printf("invalid input ..\n");

        }
    }
}
state_t app(u8 mode,u32 inx){
    state_t checkPass,add,edit,reserve,cancel;
    u8 w;
    lol:
    if (mode == '1'){
        checkPass = check_pass();
        if (checkPass == wrong_pass){
            return closeSystem;
        }
        else {
            labe:
            printf("Welcome to our system:\n");
            printf("1. Add new patient record:\n");
            printf("2. Edit patient record:\n");
            printf("3. Reserve a slot with the doctor:\n");
            printf("4. Cancel reservation:\n");
            printf("5. Close system.\n");
            scanf(" %c",&w);
            switch(w){
            case '1':
                //indd = index_ -1;
                add =add_new_patient_record(UserDataSaved,++inx);
                if (add == user_exist){
                    printf("User is already exist .\n");
                    return 0;
                }


                break;
            case '2':
                edit = edit_patient_record(UserDataSaved);
                if(edit == user_exist ){
                    printf("This user is already exist..\n");
                    //printf("Thank you for using our system..\n");
                    return 0;
                }
                else if(edit == OutOfRange){
                    printf("invalid input please try again\n");
                    goto labe;
                }
                else {
                    printf("\n");
                }

                break;
            case '3':
                reserve = reserve_a_slot_with_the_doctor(UserDataSaved);
                if (edit == user_not_exist){
                    printf("This user is not exist..\n");
                    goto labe;
                }

                break;

            case '4':
                cancel = cancel_reservation(UserDataSaved,inx);
                if (cancel== user_not_exist){
                    printf("This user is not exist..\n");
                    goto labe;
                }

                break;
            case '5':
                return closeSystem;
                break;
            default:
                printf("invalid input..\n");
                break;


            }



        }
    }

    else {

        u8 o;
        state_t view;
        printf("Welcome to our system:\n");
        printf("1. View patient record.\n");
        printf("2. View today’s reservations.\n");
        printf("3. Close system.\n");
        scanf(" %c",&o);
        switch(o){
            case '1':
               view = viewUserMode(UserDataSaved);
               if (view == user_not_exist){
                printf("Sorry, User not exist.\n");
                goto lol;
               }
                break;
            case '2':
                viewAllReservation(UserDataSaved,inx);
                break;
            case '3':
                return closeSystem;
            default:
                printf("invalid input, try again..\n");
                goto lol;
                break;


        }
    }


    return 0;
}
