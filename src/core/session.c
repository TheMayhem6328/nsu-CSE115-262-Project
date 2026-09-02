// session.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for managing current session
//
// Also, death to Code::Blocks

#include "session.h"
#include "admin.h"
#include "manager.h"
#include "player.h"
#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

FUser USER_CURRENT = {USER_UNDEFINED, NULL};

//// Counter variables

uint_fast8_t session_enabledAdminCount = 0;
uint_fast8_t session_enabledTeamCount = 0;
uint_fast8_t session_enabledManagerCount = 0;
uint_fast8_t session_enabledPlayerCount = 0;
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

// Session management

uint_fast8_t session_login(EUserType type, uint16_t id) {
  void *retrievedId;

  USER_CURRENT.type = type;

  switch (type) {
  case USER_ADMIN:
    retrievedId = admin_retrieve(id);
    break;
  case USER_MANAGER:
    retrievedId = manager_retrieve(id);
    break;
  case USER_PLAYER:
    retrievedId = player_retrieve(id);
    break;
  default:
    return 0;
  }

  if (retrievedId == NULL) {
    USER_CURRENT.type = USER_UNDEFINED;
    return 0;
  }
  USER_CURRENT.userObj = retrievedId;
  return 1;
}

uint_fast8_t session_exit(void) {
//// Clean up dynamically allocated memory

// Macro function for cleanup
#define CLEANUP_ARRAY(arr, count)                                              \
  if ((arr) != NULL) {                                                         \
    for (int i = 0; i < (count); i++) {                                        \
      free((arr)[i]);                                                          \
    }                                                                          \
    free(arr);                                                                 \
  }

  // Actually clean up the arrays
  CLEANUP_ARRAY(session_adminDynamicArray, session_adminCount);
  CLEANUP_ARRAY(session_teamDynamicArray, session_teamCount);
  CLEANUP_ARRAY(session_managerDynamicArray, session_managerCount);
  CLEANUP_ARRAY(session_playerDynamicArray, session_playerCount);
#undef CLEANUP_ARRAY

  return 0;
}

// Current session info retrieval

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