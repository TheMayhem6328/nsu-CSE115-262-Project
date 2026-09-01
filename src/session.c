#include "session.h"
#include "admin.h"
#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

FUser USER_CURRENT = {USER_UNDEFINED, NULL};

//// Counter variables

uint_fast8_t session_adminCount = 0;
uint_fast8_t session_teamCount = 0;
uint_fast8_t session_managerCount = 0;
uint_fast8_t session_playerCount = 0;

//// Arrays to store content

FAdmin **session_adminDynamicArray = NULL;
FTeam **session_teamDynamicArray = NULL;
FManager **session_managerDynamicArray = NULL;
FPlayer **session_playerDynamicArray = NULL;

//// Functions

uint_fast8_t session_login(EUserType type, uint16_t id) {
  void *retrievedId;

  USER_CURRENT.type = type;

  switch (type) {
  case USER_ADMIN:
    retrievedId = admin_retrieve(id);
    if (admin_retrieve(id) == NULL) {
      return 0;
    }
    USER_CURRENT.userObj = retrievedId;
    return 1;
  default:
    return 0;
  }
}

uint16_t session_getCurrentUserID(void) {
  if (USER_CURRENT.userObj == NULL) {
    return 0;
  }

  switch (USER_CURRENT.type) {
  case USER_ADMIN:
    return ((FAdmin *)USER_CURRENT.userObj)->id;
  case USER_MANAGER:
    return ((FManager *)USER_CURRENT.userObj)->id;
  case USER_PLAYER:
    return ((FPlayer *)USER_CURRENT.userObj)->id;
  default:
    return 0;
  }
}

const char *session_getCurrentUserName(void) {
  if (USER_CURRENT.userObj == NULL) {
    return NULL;
  }

  switch (USER_CURRENT.type) {
  case USER_ADMIN:
    return ((FAdmin *)USER_CURRENT.userObj)->name;
  case USER_MANAGER:
    return ((FManager *)USER_CURRENT.userObj)->name;
  case USER_PLAYER:
    return ((FPlayer *)USER_CURRENT.userObj)->name;
  default:
    return NULL;
  }
}

uint_fast8_t session_exit(void) {
  free(session_adminDynamicArray);
  free(session_teamDynamicArray);
  free(session_managerDynamicArray);
  free(session_playerDynamicArray);

  return 0;
}