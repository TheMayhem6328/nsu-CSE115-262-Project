// session.h
// Zahiruzzman Chowdhury
//
// Functions for managing current session
//
// Also, death to Code::Blocks

#ifndef M6328_SESSION
#define M6328_SESSION

#include "types.h" // IWYU pragma: keep
#include <stdint.h>

typedef enum userType {
    USER_ADMIN,
    USER_MANAGER,
    USER_PLAYER,
    USER_UNDEFINED
} EUserType;

typedef struct user {
    EUserType type;
    void *userObj;
} FUser;

extern FUser USER_CURRENT;

uint_fast8_t user_login(EUserType type, uint16_t id);
uint_fast8_t user_exit(void);

#endif