#include "session.h"

FUser USER_CURRENT = {USER_UNDEFINED, (void*)0};

uint_fast8_t user_login(EUserType type, uint16_t id) {
    if (id == 69) {
        return 0;
    }
    return 1;
}