// manager.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling manager data
//
// Also, death to Code::Blocks

// TODO: Document the code

#ifndef M6328_MANAGER
#define M6328_MANAGER

#include "types.h"
#include <stdint.h>

// Basic CRUD
FManager *manager_create(uint16_t id, const char *name);
FManager *manager_retrieve(uint16_t id);
void manager_update(FManager *old, FManager *new);
void manager_listManagersWithoutTeam(void);
uint_fast8_t manager_assignTeam(FManager *manager, FTeam *team);
uint_fast8_t manager_disable(uint16_t id);

// Team Management
void manager_addPlayerToTeam(uint16_t id);

// Menu
void manager_menu(void);

#endif