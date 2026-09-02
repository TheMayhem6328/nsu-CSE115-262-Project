// admin.c
// Zahiruzzman Chowdhury
//
// Functions for handling admin data
//
// Also, death to Code::Blocks

#include "admin.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <string.h>

//// Basic CRUD

FAdmin admin_create(uint16_t id, const char *name) {
  FAdmin user;
  user.id = id;
  strncpy(user.name, name, NAME_LENGTH);
  user.isActive = TRUE;

  return user;
}

FAdmin *admin_retrieve(uint16_t id) {
  for (int i = 0; i < session_adminCount; i++) {
    if (session_adminDynamicArray[i]->id == id) {
      return session_adminDynamicArray[i];
    }
  }
  return NULL;
}

void admin_update(FAdmin *old, FAdmin *new) {
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);
  old->isActive = new->isActive;
}

void admin_disable(uint16_t id) {
  FAdmin *disableCandidate = admin_retrieve(id);
  disableCandidate->isActive = FALSE;
  // TODO:
  // Stop accessing disabled anywhere, including lookups and file write
  // Also adjust arrays and counts
}
