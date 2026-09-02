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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Basic CRUD

FManager *manager_create(uint16_t id, const char *name) {
  FManager manager;

  // Basics
  manager.id = id;
  strncpy(manager.name, name, NAME_LENGTH);
  manager.isActive = TRUE;

  // Runtime data
  manager.teamPtr = NULL;

  // Increment session counters
  session_enabledAdminCount += 1;
  session_managerCount += 1;

  // Append to session array
  if (session_managerCount == 1) {
    session_managerDynamicArray =
        malloc(sizeof(FManager *) * session_managerCount);
    session_managerDynamicArray[0] = malloc(sizeof(FManager));
    *session_managerDynamicArray[0] = manager;
  } else {
    FManager **temp = realloc(session_managerDynamicArray,
                              session_managerCount * sizeof(int));
    if (temp == NULL) {
      // Handle allocation failure safely
      fprintf(stderr, "Out of memory");
      session_exit();
      exit(1);
    }
    session_managerDynamicArray = temp;
    *session_managerDynamicArray[session_managerCount - 1] = manager;
  }

  return session_managerDynamicArray[session_managerCount - 1];
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

  // TODO: Update runtime data accordingly
  old->teamPtr = NULL;
}

uint_fast8_t manager_disable(uint16_t id) {
  FManager *disableCandidate = manager_retrieve(id);
  if (!(disableCandidate->isActive)) {
    return 0;
  }
  disableCandidate->isActive = FALSE;
  session_enabledManagerCount -= 1;
  return 1;
}
