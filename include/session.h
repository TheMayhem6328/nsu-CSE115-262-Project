// session.h
// Zahiruzzman Chowdhury
//
// Functions for managing current session
//
// Also, death to Code::Blocks

#ifndef M6328_SESSION
#define M6328_SESSION

#include "types.h"
#include <stdint.h>

//// Counter variables

extern uint_fast8_t session_adminCount;
extern uint_fast8_t session_teamCount;
extern uint_fast8_t session_managerCount;
extern uint_fast8_t session_playerCount;

//// Arrays to store users
//// To be assigned with malloc()
extern FAdmin **session_adminDynamicArray;
extern FTeam **session_teamDynamicArray;
extern FManager **session_managerDynamicArray;
extern FPlayer **session_playerDynamicArray;

//// Enumerates

typedef enum userType {
    USER_ADMIN,
    USER_MANAGER,
    USER_PLAYER,
    USER_UNDEFINED
} EUserType;

//// Structs

typedef struct user {
    EUserType type;
    void *userObj;
} FUser;

extern FUser USER_CURRENT;

//// Functions

uint_fast8_t session_login(EUserType type, uint16_t id);
uint16_t session_getCurrentUserID(void);
const char *session_getCurrentUserName(void);
uint_fast8_t session_exit(void);

#endif