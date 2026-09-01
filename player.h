// player.h
// Zahiruzzman Chowdhury
//
// Functions for handling player data
//
// Also, death to Code::Blocks

#ifndef M6328_PLAYER
#define M6328_PLAYER

#include "types.h" // IWYU pragma: keep
#include <stdint.h>

// Basic CRUD
FPlayer player_create(uint16_t id, const char *name);
FPlayer player_retrieve(uint16_t id);
uint_fast8_t player_update(uint16_t id, const char *name, EBoolean isActive);
uint_fast8_t player_remove(uint16_t id);

// Menu
void player_menu(void);

#endif