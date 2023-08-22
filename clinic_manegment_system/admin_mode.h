#ifndef ADMIN_MODE_H_INCLUDED
#define ADMIN_MODE_H_INCLUDED

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef enum EN_Error_t{
    n_ok,
    ok,
    wrong_pass,
    user_exist,
    user_not_exist,
    OutOfRange,
    not_found,
    closeSystem


}state_t;
typedef struct ST_use_data_t {
    u8 name[20];
    u8 gender;
    u32 age;
    u8 id[6];
    u8 slot[7];

}user_data_t;
extern user_data_t UserDataSaved[] ;
extern u32 index_;

state_t check_pass();
state_t add_new_patient_record(user_data_t *data,u32 inx);
state_t edit_patient_record(user_data_t *data);
state_t reserve_a_slot_with_the_doctor(user_data_t *data);
state_t cancel_reservation(user_data_t *data,u32 inx);
#endif // ADMIN_MODE_H_INCLUDED
