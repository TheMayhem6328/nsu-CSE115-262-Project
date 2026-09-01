#include "admin.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <string.h>

FAdmin admin_create(uint16_t id, const char *name) {
  FAdmin user;
  user.id = id;
  strncpy(user.name, name, NAME_LENGTH);
  user.isActive = TRUE;

  return user;
}

FAdmin *admin_retrieve(uint16_t id) {
  for (int i=0; i < session_adminCount; i++) {
    if (session_adminDynamicArray[i]->id == id) {
      return session_adminDynamicArray[i];
    }
  }
  return NULL;
}