#ifndef USER_MODE_H_INCLUDED
#define USER_MODE_H_INCLUDED

extern user_data_t UserDataSaved[] ;
extern u32 index_;
state_t viewUserMode(user_data_t *data);
void viewAllReservation(user_data_t *data,u8 inx);
#endif // USER_MODE_H_INCLUDED
