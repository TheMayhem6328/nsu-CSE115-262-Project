// team.h
// Zahiruzzman Chowdhury
//
// Functions for handling team data
//
// Also, death to Code::Blocks

#ifndef M6328_TEAM
#define M6328_TEAM

#include "types.h" // IWYU pragma: keep
#include <stdint.h>

// Basic CRUD
FTeam team_create(uint16_t id, const char *name);
FTeam team_retrieve(uint16_t id);
uint_fast8_t team_update(uint16_t id, const char *name, EBoolean isActive);
uint_fast8_t team_remove(uint16_t id);

// Team management
void team_listTeamsWithoutManager(void);

#endif