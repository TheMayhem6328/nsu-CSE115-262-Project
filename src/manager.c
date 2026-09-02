// manager.c
// Zahiruzzman Chowdhury
//
// Functions for handling manager data
//
// Also, death to Code::Blocks

#include "manager.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <string.h>

//// Basic CRUD

FManager manager_create(uint16_t id, const char *name) {
  FManager manager;

  // Basics
  manager.id = id;
  strncpy(manager.name, name, NAME_LENGTH);
  manager.isActive = TRUE;

  // Runtime data
  manager.teamPtr = NULL;

  return manager;
}

FManager *manager_retrieve(uint16_t id) {
  for (int i = 0; i < session_managerCount; i++) {
    if (session_managerDynamicArray[i]->isActive) {
      if (session_managerDynamicArray[i]->id == id) {
        return session_managerDynamicArray[i];
      }
    }
  }
  return NULL;
}

void manager_update(FManager *old, FManager *new) {
  // Basics
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);
  old->isActive = new->isActive;

  // TODO: Update runtime data accordingly
  old->teamPtr = NULL;
}

uint_fast8_t manager_disable(uint16_t id) {
  FManager *disableCandidate = manager_retrieve(id);
  disableCandidate->isActive = FALSE;
  return 1;
  // TODO:
  // Adjust arrays and counts accordingly
}
