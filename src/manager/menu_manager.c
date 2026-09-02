// menu_manager.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Manager menu implementation
//
// Also, death to Code::Blocks

#include "menu_manager.h"
#include "file_common.h"
#include "manager.h"
#include "menu_common.h"
#include "player.h"
#include "session.h"
#include <stdio.h>

//// Utility static functions

static FTeam *menu_currentManagerTeam(void) {
  FManager *manager = (FManager *)USER_CURRENT.userObj;
  if (manager == NULL)
    return NULL;
  for (uint_fast8_t i = 0; i < session_teamCount; ++i)
    if (session_teamDynamicArray[i]->isActive &&
        session_teamDynamicArray[i]->managerID == manager->id)
      return session_teamDynamicArray[i];
  return NULL;
}

//// Team Management

uint_fast8_t menu_managerTeam(void) {
  FTeam *team = menu_currentManagerTeam();
  if (team == NULL) {
    puts("You are not assigned to a team.");
    return 0;
  }
  printf("Team %u: %s, manager %u, %u players\n", team->id, team->name,
         team->managerID, team->playerCount);
  return 0;
}

uint_fast8_t menu_managerPlayers(void) {
  FTeam *team = menu_currentManagerTeam();
  if (team == NULL) {
    puts("You are not assigned to a team.");
    return 0;
  }
  for (uint_fast8_t i = 0; i < team->playerCount; ++i) {
    FPlayer *player = player_retrieve(team->playerIDs[i]);
    if (player != NULL)
      printf("%u: %s, position %u, shirt %u, rating %u\n", player->id,
             player->name, (unsigned int)player->position, player->shirtNumber,
             player->rating);
  }
  return 0;
}

//// Base manager menu

uint_fast8_t menu_manager(void) {
  for (;;) {
    puts("\nManager menu");
    puts("  0: Save and Quit");
    puts("  1: View team");
    puts("  2: List team players");
    puts("  3: Add existing player to team");
    int_fast64_t choice = menu_readNumber("Your choice: ");

    switch (choice) {
    case 0:
      file_saveDataFile();
      session_exit();
      return 0;
    case 1:
      menu_managerTeam();
      break;
    case 2:
      menu_managerPlayers();
      break;
    case 3:
      if (menu_currentManagerTeam() == NULL)
        puts("You are not assigned to a team.");
      else {
        int_fast64_t id = menu_readNumber("Player ID: ");
        if (id >= 0 && id <= UINT16_MAX)
          manager_addPlayerToTeam((uint16_t)id);
      }
      break;
    default:
      puts("Invalid option.");
    }
  }
}