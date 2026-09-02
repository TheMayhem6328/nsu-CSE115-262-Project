// team.h
// Zahiruzzman Chowdhury
//
// Functions for handling team data
//
// Also, death to Code::Blocks

#ifndef M6328_TEAM
#define M6328_TEAM

#include "types.h"
#include <stdint.h>

// Basic CRUD
FTeam team_create(uint16_t id, const char *name);
FTeam *team_retrieve(uint16_t id);
void team_update(FTeam *old, FTeam *new);
void team_disable(uint16_t id); // TODO: Stop accessing disabled anywhere,
                                // including lookups and file write

// Team management
void team_listTeamsWithoutManager(void);

#endif