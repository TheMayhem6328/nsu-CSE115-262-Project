// team.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling team data
//
// Also, death to Code::Blocks

#ifndef M6328_TEAM
#define M6328_TEAM

#include "types.h"
#include <stdint.h>

// Basic CRUD
FTeam *team_create(uint16_t id, const char *name);
FTeam *team_retrieve(uint16_t id);
void team_update(FTeam *old, FTeam *new);
uint_fast8_t team_disable(uint16_t id);

// Team management
void team_listTeamsWithoutManager(void);

#endif