// player.c
// Zahiruzzman Chowdhury
//
// Functions for handling player data
//
// Also, death to Code::Blocks

#include "player.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <string.h>

//// Basic CRUD

FPlayer player_create(uint16_t id, const char *name) {
  FPlayer player;

  // Basics
  player.id = id;
  strncpy(player.name, name, NAME_LENGTH);
  player.isActive = TRUE;

  // Field identifier
  player.position = 0;
  player.shirtNumber = 0;

  // Personal metadata
  player.rating = 0;
  player.fitness = 0;
  player.isInjured = FALSE;

  // Season stats
  player.appearances = 0;
  player.goals = 0;
  player.assists = 0;

  // Runtime data
  player.teamPtr = NULL;

  return player;
}

FPlayer *player_retrieve(uint16_t id) {
  for (int i = 0; i < session_playerCount; i++) {
    if (session_playerDynamicArray[i]->id == id) {
      return session_playerDynamicArray[i];
    }
  }
  return NULL;
}

void player_update(FPlayer *old, FPlayer *new) {
  // Basics
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);
  old->isActive = new->isActive;

  // Field identifier
  old->position = new->position;
  old->shirtNumber = new->shirtNumber;

  // Personal metadata
  old->rating = new->rating;
  old->fitness = new->fitness;
  old->isInjured = new->isInjured;

  // Season stats
  old->appearances = new->appearances;
  old->goals = new->goals;
  old->assists = new->assists;

  // TODO: Update runtime data accordingly
  old->teamPtr = NULL;
}

void player_disable(uint16_t id) {
  FPlayer *disableCandidate = player_retrieve(id);
  disableCandidate->isActive = FALSE;
  // TODO:
  // Stop accessing disabled anywhere, including lookups and file write
  // Also adjust arrays and counts
}
