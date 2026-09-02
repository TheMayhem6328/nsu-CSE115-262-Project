// session.c
// Zahiruzzman Chowdhury
//
// Functions for managing current session
//
// Also, death to Code::Blocks

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

// Session management

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

uint_fast8_t session_exit(void) {
  //// Clean up dynamically allocated memory

  // Admin
  for (int i = 0; i < session_adminCount; i++) {
    free(session_adminDynamicArray[i]);
  }
  free(session_adminDynamicArray);

  // Team
  for (int i = 0; i < session_teamCount; i++) {
    free(session_teamDynamicArray[i]);
  }
  free(session_teamDynamicArray);

  // Manager
  for (int i = 0; i < session_managerCount; i++) {
    free(session_managerDynamicArray[i]);
  }
  free(session_managerDynamicArray);

  // Player
  for (int i = 0; i < session_playerCount; i++) {
    free(session_playerDynamicArray[i]);
  }
  free(session_playerDynamicArray);

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