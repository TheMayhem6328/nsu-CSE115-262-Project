// manager.h
// Zahiruzzman Chowdhury
//
// Functions for handling manager data
//
// Also, death to Code::Blocks

#ifndef M6328_MANAGER
#define M6328_MANAGER

#include "types.h"
#include <stdint.h>

// Basic CRUD
FManager manager_create(uint16_t id, const char *name);
FManager *manager_retrieve(uint16_t id);
void manager_update(FManager *old, FManager *new);
void manager_disable(uint16_t id); // TODO: Stop accessing disabled anywhere,
                                   // including lookups and file write

// Team Management
void manager_addPlayerToTeam(uint16_t id);

// Menu
void manager_menu(void);

#endif