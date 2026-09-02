// player.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling player data
//
// Also, death to Code::Blocks

// TODO: Document the code

#ifndef M6328_PLAYER
#define M6328_PLAYER

#include "types.h"
#include <stdint.h>

// Basic CRUD
FPlayer *player_create(uint16_t id, const char *name);
FPlayer *player_retrieve(uint16_t id);
void player_update(FPlayer *old, FPlayer *new);
void player_listPlayersWithoutTeam(void);
uint_fast8_t player_leaveTeam(FPlayer *player);
uint_fast8_t player_disable(uint16_t id);

// Menu
void player_menu(void);

#endif