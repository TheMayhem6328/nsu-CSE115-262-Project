// menu_manager.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Manager menu implementation
//
// Also, death to Code::Blocks

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "menu_manager.h"
#include "file_common.h"
#include "manager.h"
#include "menu_common.h"
#include "player.h"
#include "session.h"
#include <stdio.h>
#include <string.h>

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

static void menu_managerEditPlayer(void) {
  int_fast64_t id = menu_readNumber("Player ID: ");
  if (id < 0 || id > UINT16_MAX) {
    puts("Invalid ID.");
    return;
  }
  FPlayer *player = player_retrieve((uint16_t)id);
  if (player == NULL || !player->isActive) {
    puts("Player not found.");
    return;
  }
  puts("  1: Field identifiers");
  puts("  2: Personal metadata");
  puts("  3: Season stats");
  int_fast64_t category = menu_readNumber("Category: ");
  switch (category) {
  case 1: {
    int_fast64_t position = menu_readNumber("Position (0-14): ");
    int_fast64_t shirt = menu_readNumber("Shirt number (0-255): ");
    if (position >= 0 && position < POSITION_COUNT && shirt >= 0 && shirt <= UINT8_MAX) {
      player->position = (EPlayerPosition)position;
      player->shirtNumber = (uint8_t)shirt;
      menu_printSuccess("Updated");
    } else puts("Invalid field data.");
    break;
  }
  case 2: {
    int_fast64_t rating = menu_readNumber("Rating (0-255): ");
    int_fast64_t fitness = menu_readNumber("Fitness (0-255): ");
    if (rating >= 0 && rating <= UINT8_MAX && fitness >= 0 && fitness <= UINT8_MAX) {
      player->rating = (uint8_t)rating;
      player->fitness = (uint8_t)fitness;
      menu_printSuccess("Updated");
    } else puts("Invalid personal data.");
    break;
  }
  case 3: {
    int_fast64_t appearances = menu_readNumber("Appearances (0-65535): ");
    int_fast64_t goals = menu_readNumber("Goals (0-65535): ");
    int_fast64_t assists = menu_readNumber("Assists (0-65535): ");
    if (appearances >= 0 && appearances <= UINT16_MAX && goals >= 0 &&
        goals <= UINT16_MAX && assists >= 0 && assists <= UINT16_MAX) {
      player->appearances = (uint16_t)appearances;
      player->goals = (uint16_t)goals;
      player->assists = (uint16_t)assists;
      menu_printSuccess("Updated");
    } else puts("Invalid season data.");
    break;
  }
  default:
    puts("Invalid category.");
  }
}

static void menu_managerUpdateName(void) {
  FManager *manager = (FManager *)USER_CURRENT.userObj;
  char name[NAME_LENGTH];
  if (manager == NULL) return;
  menu_readText("New name: ", name);
  if (name[0] == '\0') {
    puts("Invalid name.");
    return;
  }
  strncpy(manager->name, name, NAME_LENGTH);
  menu_printSuccess("Updated");
}

//// Base manager menu

uint_fast8_t menu_manager(void) {
  for (;;) {
    menu_printHeader("Manager menu");
    menu_printOption("0", "Save and Quit");
    menu_printOption("1", "View team");
    menu_printOption("2", "List team players");
    menu_printOption("3", "Add existing player to team");
    menu_printOption("4", "Update player data");
    menu_printOption("5", "Change my name");
    menu_printOption("6", "My information");
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
    case 4:
      menu_managerEditPlayer();
      break;
    case 5:
      menu_managerUpdateName();
      break;
    case 6:
      menu_printManager((FManager *)USER_CURRENT.userObj);
      break;
    default:
      puts("Invalid option.");
    }
  }
}

//// Team Management

uint_fast8_t menu_managerTeam(void) {
  FTeam *team = menu_currentManagerTeam();
  if (team == NULL) {
    puts("You are not assigned to a team.");
    return 0;
  }
  menu_printTeam(team);
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
      printf("%u: %s\n", player->id, player->name);
  }
  return 0;
}
