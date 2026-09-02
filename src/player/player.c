// player.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling player data
//
// Also, death to Code::Blocks

// TODO: Document the code

#include "player.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Basic CRUD

FPlayer *player_create(uint16_t id, const char *name) {
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

  // Increment session counters
  session_enabledPlayerCount += 1;
  session_playerCount += 1;

  // Append to session array
  if (session_playerCount == 1) {
    session_playerDynamicArray = malloc(sizeof(FPlayer *) * session_playerCount);
    session_playerDynamicArray[0] = malloc(sizeof(FPlayer));
    *session_playerDynamicArray[0] = player;
  } else {
    FPlayer **temp = realloc(session_playerDynamicArray, session_playerCount * sizeof(FPlayer*));
    if (temp == NULL) {
        // Handle allocation failure safely
        fprintf(stderr, "Out of memory");
        session_exit();
        exit(1);
    }
    session_playerDynamicArray = temp;
    session_playerDynamicArray[session_playerCount - 1] = malloc(sizeof(FPlayer));
    if (session_playerDynamicArray[session_playerCount - 1] == NULL) {
        fprintf(stderr, "Out of memory");
        session_exit();
        exit(1);
    }
    *session_playerDynamicArray[session_playerCount - 1] = player;
  }

  return session_playerDynamicArray[session_playerCount - 1];
}

FPlayer *player_retrieve(uint16_t id) {
  for (int i = 0; i < session_playerCount; i++) {
    if (session_playerDynamicArray[i]->isActive) {
      if (session_playerDynamicArray[i]->id == id) {
        return session_playerDynamicArray[i];
      }
    }
  }
  return NULL;
}

void player_update(FPlayer *old, FPlayer *new) {
  // Basics
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);

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

void player_listPlayersWithoutTeam(void) {
  puts("\n+-------+----------------------+\n");
  puts("| ID    | Name                 |");
  puts("+-------+----------------------+");
  for (uint_fast8_t i = 0; i < session_playerCount; ++i) {
    if (session_playerDynamicArray[i]->isActive &&
        session_playerDynamicArray[i]->teamPtr == NULL) {
      printf("| %-5u | %-20.20s |\n", session_playerDynamicArray[i]->id,
             session_playerDynamicArray[i]->name);
    }
  }
  puts("+-------+----------------------+\n");
}

uint_fast8_t player_leaveTeam(FPlayer *player) {
  if (player == NULL || player->teamPtr == NULL) return 0;
  FTeam *team = player->teamPtr;
  for (uint_fast8_t i = 0; i < team->playerCount; ++i) {
    if (team->playerIDs[i] == player->id) {
      for (uint_fast8_t j = i + 1; j < team->playerCount; ++j)
        team->playerIDs[j - 1] = team->playerIDs[j];
      team->playerIDs[team->playerCount - 1] = 0;
      team->playerCount -= 1;
      player->teamPtr = NULL;
      team->playerPtrs[team->playerCount] = NULL;
      return 1;
    }
  }
  player->teamPtr = NULL;
  return 0;
}

uint_fast8_t player_disable(uint16_t id) {
  FPlayer *disableCandidate = player_retrieve(id);
  if (disableCandidate == NULL || !(disableCandidate->isActive)) {
    return 0;
  }
  disableCandidate->isActive = FALSE;
  session_enabledPlayerCount -= 1;
  return 1;
}
