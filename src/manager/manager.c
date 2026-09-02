// manager.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Functions for handling manager data
//
// Also, death to Code::Blocks

// TODO: Document the code

#include "manager.h"
#include "session.h"
#include "player.h"
#include "types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Basic CRUD

FManager *manager_create(uint16_t id, const char *name) {
  FManager manager;

  // Basics
  manager.id = id;
  strncpy(manager.name, name, NAME_LENGTH);
  manager.isActive = TRUE;

  // Runtime data
  manager.teamPtr = NULL;

  // Increment session counters
  session_enabledManagerCount += 1;
  session_managerCount += 1;

  // Append to session array
  if (session_managerCount == 1) {
    session_managerDynamicArray =
        malloc(sizeof(FManager *) * session_managerCount);
    session_managerDynamicArray[0] = malloc(sizeof(FManager));
    *session_managerDynamicArray[0] = manager;
  } else {
    FManager **temp = realloc(session_managerDynamicArray,
                              session_managerCount * sizeof(FManager*));
    if (temp == NULL) {
      // Handle allocation failure safely
      fprintf(stderr, "Out of memory");
      session_exit();
      exit(1);
    }
    session_managerDynamicArray = temp;
    session_managerDynamicArray[session_managerCount - 1] = malloc(sizeof(FManager));
    if (session_managerDynamicArray[session_managerCount - 1] == NULL) {
      fprintf(stderr, "Out of memory");
      session_exit();
      exit(1);
    }
    *session_managerDynamicArray[session_managerCount - 1] = manager;
  }

  return session_managerDynamicArray[session_managerCount - 1];
}

FManager *manager_retrieve(uint16_t id) {
  for (int i = 0; i < session_managerCount; i++) {
    if (session_managerDynamicArray[i]->isActive) {
      if (session_managerDynamicArray[i]->id == id) {
        return session_managerDynamicArray[i];
      }
    }
  }
  return NULL;
}

void manager_update(FManager *old, FManager *new) {
  // Basics
  old->id = new->id;
  strncpy(old->name, new->name, NAME_LENGTH);

  // TODO: Update runtime data accordingly
  old->teamPtr = NULL;
}

void manager_listManagersWithoutTeam(void) {
  puts("\n+-------+----------------------+\n");
  puts("| ID    | Name                 |");
  puts("+-------+----------------------+");
  for (uint_fast8_t i = 0; i < session_managerCount; ++i) {
    if (session_managerDynamicArray[i]->isActive &&
        session_managerDynamicArray[i]->teamPtr == NULL) {
      printf("| %-5u | %-20.20s |\n", session_managerDynamicArray[i]->id,
             session_managerDynamicArray[i]->name);
    }
  }
  puts("+-------+----------------------+\n");
}

uint_fast8_t manager_assignTeam(FManager *manager, FTeam *team) {
  if (manager == NULL || team == NULL || !manager->isActive ||
      !team->isActive || (manager->teamPtr != NULL && manager->teamPtr != team))
    return 0;
  if (team->manager != NULL && team->manager != manager) return 0;
  manager->teamPtr = team;
  team->manager = manager;
  team->managerID = manager->id;
  return 1;
}

void manager_addPlayerToTeam(uint16_t id) {
  FManager *manager = (FManager *)USER_CURRENT.userObj;
  FPlayer *player = player_retrieve(id);
  FTeam *team = NULL;

  if (manager == NULL || player == NULL || !player->isActive) return;
  for (uint_fast8_t i = 0; i < session_teamCount; ++i) {
    if (session_teamDynamicArray[i]->isActive &&
        session_teamDynamicArray[i]->managerID == manager->id) {
      team = session_teamDynamicArray[i];
      break;
    }
  }
  if (team == NULL || team->playerCount >= MAX_TEAM_PLAYERS || player->teamPtr != NULL)
    return;

  team->playerIDs[team->playerCount] = (uint8_t)id;
  team->playerPtrs[team->playerCount] = player;
  team->playerCount += 1;
  player->teamPtr = team;
}

uint_fast8_t manager_disable(uint16_t id) {
  FManager *disableCandidate = manager_retrieve(id);
  if (disableCandidate == NULL || !(disableCandidate->isActive)) {
    return 0;
  }
  disableCandidate->isActive = FALSE;
  session_enabledManagerCount -= 1;
  return 1;
}
