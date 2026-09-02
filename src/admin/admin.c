// admin.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling admin data
//
// Also, death to Code::Blocks

#include "admin.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Basic CRUD

FAdmin *admin_create(uint16_t id, const char *name) {
  FAdmin admin;

  // Basics
  admin.id = id;
  strncpy(admin.name, name, NAME_LENGTH);
  admin.isActive = TRUE;

  // Increment session counters
  session_enabledAdminCount += 1;
  session_adminCount += 1;

  // Append to session array
  if (session_adminCount == 1) {
    session_adminDynamicArray = malloc(sizeof(FAdmin *) * session_adminCount);
    session_adminDynamicArray[0] = malloc(sizeof(FAdmin));
    *session_adminDynamicArray[0] = admin;
  } else {
    FAdmin **temp =
        realloc(session_adminDynamicArray, session_adminCount * sizeof(FAdmin*));
    if (temp == NULL) {
      // Handle allocation failure safely
      fprintf(stderr, "Out of memory");
      session_exit();
      exit(1);
    }
    session_adminDynamicArray = temp;
    session_adminDynamicArray[session_adminCount - 1] = malloc(sizeof(FAdmin));
    if (session_adminDynamicArray[session_adminCount - 1] == NULL) {
      fprintf(stderr, "Out of memory");
      session_exit();
      exit(1);
    }
    *session_adminDynamicArray[session_adminCount - 1] = admin;
  }

  return session_adminDynamicArray[session_adminCount - 1];
}

FAdmin *admin_retrieve(uint16_t id) {
  for (int i = 0; i < session_adminCount; i++) {
    if (session_adminDynamicArray[i]->isActive) {
      if (session_adminDynamicArray[i]->id == id) {
        return session_adminDynamicArray[i];
      }
    }
  }
  return NULL;
}

void admin_update(FAdmin *old, FAdmin *new) {
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);
}

uint_fast8_t admin_disable(uint16_t id) {
  // Do not let user disable all admins
  if (session_enabledAdminCount == 1) {
    return 0;
  }

  FAdmin *disableCandidate = admin_retrieve(id);
  if (disableCandidate == NULL || !(disableCandidate->isActive)) {
    return 0;
  }
  disableCandidate->isActive = FALSE;
  session_enabledAdminCount -= 1;
  return 1;
}
