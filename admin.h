// admin.h
// Zahiruzzman Chowdhury
//
// Functions for handling admin data
//
// Also, death to Code::Blocks

#ifndef M6328_ADMIN
#define M6328_ADMIN

#include "types.h"
#include <stdint.h>

// Basic CRUD
FAdmin admin_create(uint16_t id, const char *name);
FAdmin admin_retrieve(uint16_t id);
uint_fast8_t admin_update(uint16_t id, const char *name, EBoolean isActive);
uint_fast8_t admin_remove(uint16_t id); // TODO: Do NOT let user remove last admin

// Menu
void admin_menu(void);

#endif