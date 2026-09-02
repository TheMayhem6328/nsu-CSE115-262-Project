// team.c
// Zahiruzzman Chowdhury
//
// Functions for handling team data
//
// Also, death to Code::Blocks

#include "team.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Basic CRUD

FTeam *team_create(uint16_t id, const char *name) {
  FTeam team;

  // Basics
  team.id = id;
  strncpy(team.name, name, NAME_LENGTH);
  team.isActive = TRUE;

  // Location metadata
  strncpy(team.city, "", NAME_LENGTH);
  strncpy(team.stadium, "", NAME_LENGTH);

  // Season stats
  team.matchesPlayed = 0;
  team.wins = 0;
  team.draws = 0;
  team.losses = 0;
  team.goalsFor = 0;
  team.goalsAgainst = 0;
  team.points = 0;

  // Team information
  team.managerID = 0;
  team.playerCount = 0;
  // Player IDs
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team.playerIDs[i] = 0;
  }

  // Runtime data
  team.manager = NULL;
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team.playerPtrs[i] = NULL;
  }

  // Increment session counters
  session_enabledTeamCount += 1;
  session_teamCount += 1;

  // Append to session array
  if (session_teamCount == 1) {
    session_teamDynamicArray = malloc(sizeof(FTeam *) * session_teamCount);
    session_teamDynamicArray[0] = malloc(sizeof(FTeam));
    *session_teamDynamicArray[0] = team;
  } else {
    FTeam **temp = realloc(session_teamDynamicArray, session_teamCount * sizeof(FTeam*));
    if (temp == NULL) {
        // Handle allocation failure safely
        fprintf(stderr, "Out of memory");
        session_exit();
        exit(1);
    }
    session_teamDynamicArray = temp;
    session_teamDynamicArray[session_teamCount - 1] = malloc(sizeof(FTeam));
    if (session_teamDynamicArray[session_teamCount - 1] == NULL) {
        fprintf(stderr, "Out of memory");
        session_exit();
        exit(1);
    }
    *session_teamDynamicArray[session_teamCount - 1] = team;
  }

  return session_teamDynamicArray[session_teamCount - 1];
}

FTeam *team_retrieve(uint16_t id) {
  for (int i = 0; i < session_teamCount; i++) {
    if (session_teamDynamicArray[i]->isActive) {
      if (session_teamDynamicArray[i]->id == id) {
        return session_teamDynamicArray[i];
      }
    }
  }
  return NULL;
}

void team_update(FTeam *old, FTeam *new) {
  // Basics
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);

  // Location metadata
  strncpy(old->city, new->city, NAME_LENGTH);
  strncpy(old->stadium, new->stadium, NAME_LENGTH);

  // Season stats
  old->matchesPlayed = new->matchesPlayed;
  old->wins = new->wins;
  old->draws = new->draws;
  old->losses = new->losses;
  old->goalsFor = new->goalsFor;
  old->goalsAgainst = new->goalsAgainst;
  old->points = new->points;

  // Team information
  old->managerID = new->managerID;
  old->playerCount = new->playerCount;
  // Player IDs
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    old->playerIDs[i] = new->playerIDs[i];
  }

  // TODO: Update runtime data accordingly
  old->manager = NULL;
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    old->playerPtrs[i] = NULL;
  }
}

uint_fast8_t team_disable(uint16_t id) {
  FTeam *disableCandidate = team_retrieve(id);
  if (disableCandidate == NULL || !(disableCandidate->isActive)) {
    return 0;
  }
  disableCandidate->isActive = FALSE;
  session_enabledTeamCount -= 1;
  return 1;
}
