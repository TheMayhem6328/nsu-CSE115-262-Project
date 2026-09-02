// menu_common.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Shared menu input and display utilities
//
// Also, death to Code::Blocks

#include "menu_common.h"
#include "admin.h"
#include "manager.h"
#include "player.h"
#include "session.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// Static utility functions

static void menu_printSection(const char *title) {
  printf("\n%s:\n", title);
  puts("==================================================");
}

//// Formatted utility prints

void menu_printHeader(const char *title) {
  printf("\n%s+----------------------------------------+%s\n",
         MENU_ANSI_BOLD_CYAN, MENU_ANSI_RESET);
  printf("%s| %-38s |%s\n", MENU_ANSI_BOLD_CYAN, title, MENU_ANSI_RESET);
  printf("%s+----------------------------------------+%s\n",
         MENU_ANSI_BOLD_CYAN, MENU_ANSI_RESET);
}

void menu_printOption(const char *number, const char *label) {
  printf("  %s%s%s: %s\n", MENU_ANSI_BOLD_YELLOW, number, MENU_ANSI_RESET,
         label);
}

void menu_printSuccess(const char *message) {
  printf("%s--- %s ---%s\n", MENU_ANSI_BOLD_GREEN, message, MENU_ANSI_RESET);
}

//// Read input

int_fast64_t menu_readNumber(const char *prompt) {
  char input[NAME_LENGTH];
  printf("%s%s%s", MENU_ANSI_BOLD_GREEN, prompt, MENU_ANSI_RESET);
  if (fgets(input, sizeof(input), stdin) == NULL)
    return -1;
  return (int_fast64_t)strtol(input, NULL, 10);
}

void menu_readText(const char *prompt, char *output) {
  printf("%s%s%s", MENU_ANSI_BOLD_GREEN, prompt, MENU_ANSI_RESET);
  if (fgets(output, NAME_LENGTH, stdin) == NULL) {
    output[0] = '\0';
    return;
  }
  output[strcspn(output, "\n")] = '\0';
}

//// Output entity profile

void menu_printAdmin(const FAdmin *admin) {
  if (admin == NULL)
    return;
  puts("\n+---------------- ADMIN ----------------+");
  menu_printSection("Basics");
  printf("ID: %u\nName: %s\nStatus: %s\n", admin->id, admin->name,
         admin->isActive ? "Active" : "Disabled");
}

void menu_printTeam(const FTeam *team) {
  if (team == NULL)
    return;

  puts("\n+---------------- TEAM ----------------+");

  menu_printSection("Basics");
  printf("ID: %u\nName: %s\nStatus: %s\n", team->id, team->name,
         team->isActive ? "Active" : "Disabled");

  menu_printSection("Location");
  printf("City: %s\nStadium: %s\n", team->city, team->stadium);

  menu_printSection("Season stats");
  printf("Matches played: %u\nWins: %u\nDraws: %u\nLosses: %u\nGoals for: "
         "%u\nGoals against: %u\nPoints: %u\n",
         team->matchesPlayed, team->wins, team->draws, team->losses,
         team->goalsFor, team->goalsAgainst, team->points);

  menu_printSection("Team members");
  printf("Manager: %s\nPlayers: %u\n",
         team->manager != NULL ? team->manager->name : "Unassigned",
         team->playerCount);

  for (uint_fast8_t i = 0; i < team->playerCount; ++i) {
    FPlayer *player = team->playerPtrs[i];
    if (player != NULL)
      printf("  %u: %s\n", player->id, player->name);
  }
}

void menu_printManager(const FManager *manager) {
  if (manager == NULL)
    return;

  puts("\n+--------------- MANAGER ---------------+");

  menu_printSection("Basics");
  printf("ID: %u\nName: %s\nStatus: %s\n", manager->id, manager->name,
         manager->isActive ? "Active" : "Disabled");

  menu_printSection("Team affiliation");
  if (manager->teamPtr != NULL)
    printf("Team: %u - %s\n", manager->teamPtr->id, manager->teamPtr->name);
  else
    puts("Team: Unassigned");
}

void menu_printPlayer(const FPlayer *player) {
  if (player == NULL)
    return;

  puts("\n+---------------- PLAYER ----------------+");

  menu_printSection("Basics");
  printf("ID: %u\nName: %s\nStatus: %s\n", player->id, player->name,
         player->isActive ? "Active" : "Disabled");

  menu_printSection("Field identifier");
  printf("Position: %s\nShirt Number: %u\n",
         player->position < POSITION_COUNT ? positionNames[player->position]
                                           : "Invalid",
         player->shirtNumber);

  menu_printSection("Personal metadata");
  printf("Rating: %u\nFitness: %u\nInjured: %s\n", player->rating,
         player->fitness, player->isInjured ? "Yes" : "No");

  menu_printSection("Season stats");
  printf("Appearances: %u\nGoals: %u\nAssists: %u\n", player->appearances,
         player->goals, player->assists);

  menu_printSection("Team affiliation");
  if (player->teamPtr != NULL)
    printf("Team: %u - %s\n", player->teamPtr->id, player->teamPtr->name);
  else
    puts("Team: Unassigned");
}

//// Output entity list

void menu_listAdmins(void) {
  puts("\n+-------+----------------------+----------+");
  puts("| ID    | Name                 | Status   |");
  puts("+-------+----------------------+----------+");

  for (uint_fast8_t i = 0; i < session_adminCount; ++i)
    printf("| %-5u | %-20.20s | %-8s |\n", session_adminDynamicArray[i]->id,
           session_adminDynamicArray[i]->name,
           session_adminDynamicArray[i]->isActive ? "active" : "disabled");

  puts("+-------+----------------------+----------+\n");
}

void menu_listTeams(void) {
  puts("\n+-------+----------------------+---------+--------+");
  puts("| ID    | Name                 | Manager | Players|");
  puts("+-------+----------------------+---------+--------+");
  for (uint_fast8_t i = 0; i < session_teamCount; ++i)
    printf("| %-5u | %-20.20s | %-7u | %-6u |\n",
           session_teamDynamicArray[i]->id, session_teamDynamicArray[i]->name,
           session_teamDynamicArray[i]->managerID,
           session_teamDynamicArray[i]->playerCount);
  puts("+-------+----------------------+---------+--------+\n");
}

void menu_listManagers(void) {
  puts("\n+-------+----------------------+----------+");
  puts("| ID    | Name                 | Status   |");
  puts("+-------+----------------------+----------+");

  for (uint_fast8_t i = 0; i < session_managerCount; ++i)
    printf("| %-5u | %-20.20s | %-8s |\n", session_managerDynamicArray[i]->id,
           session_managerDynamicArray[i]->name,
           session_managerDynamicArray[i]->isActive ? "active" : "disabled");

  puts("+-------+----------------------+----------+\n");
}

void menu_listPlayers(void) {
  puts("\n+-------+----------------------+----------+--------+--------+");
  puts("| ID    | Name                 | Position | Shirt  | Rating |");
  puts("+-------+----------------------+----------+--------+--------+");
  
  for (uint_fast8_t i = 0; i < session_playerCount; ++i)
    printf("| %-5u | %-20.20s | %-8u | %-6u | %-6u |\n",
           session_playerDynamicArray[i]->id,
           session_playerDynamicArray[i]->name,
           (unsigned int)session_playerDynamicArray[i]->position,
           session_playerDynamicArray[i]->shirtNumber,
           session_playerDynamicArray[i]->rating);
  puts("+-------+----------------------+----------+--------+--------+\n");
}

//// Generic user management

void menu_createUser(EUserType type) {
  char name[NAME_LENGTH];
  int_fast64_t id = menu_readNumber("ID: ");
  menu_readText("Name: ", name);

  if (id < 0 || id > UINT16_MAX || name[0] == '\0') {
    puts("Invalid data.");
    return;
  }

  switch (type) {
  case USER_ADMIN:
    admin_create((uint16_t)id, name);
    break;
  case USER_MANAGER:
    manager_create((uint16_t)id, name);
    break;
  case USER_PLAYER:
    player_create((uint16_t)id, name);
    break;
  default:
    puts("Invalid user type.");
    return;
  }
  menu_printSuccess("Created");
}

void menu_updateUser(EUserType type) {
  int_fast64_t id = menu_readNumber("ID to update: ");
  char name[NAME_LENGTH];
  if (id < 0 || id > UINT16_MAX) {
    puts("Invalid ID.");
    return;
  }
  menu_readText("New name: ", name);
  if (name[0] == '\0') {
    puts("Invalid name.");
    return;
  }
  switch (type) {
  case USER_ADMIN: {
    FAdmin *user = admin_retrieve((uint16_t)id);
    if (user == NULL) {
      puts("Not found.");
      return;
    }
    strncpy(user->name, name, NAME_LENGTH);
    break;
  }
  case USER_MANAGER: {
    FManager *user = manager_retrieve((uint16_t)id);
    if (user == NULL) {
      puts("Not found.");
      return;
    }
    strncpy(user->name, name, NAME_LENGTH);
    break;
  }
  case USER_PLAYER: {
    FPlayer *user = player_retrieve((uint16_t)id);
    if (user == NULL) {
      puts("Not found.");
      return;
    }
    strncpy(user->name, name, NAME_LENGTH);
    break;
  }
  default:
    puts("Invalid user type.");
    return;
  }
  menu_printSuccess("Updated");
}

void menu_disableUser(EUserType type) {
  int_fast64_t id = menu_readNumber("ID to disable: ");
  uint_fast8_t result = 0;

  if (id < 0 || id > UINT16_MAX) {
    puts("Invalid ID.");
    return;
  }

  switch (type) {
  case USER_ADMIN:
    result = admin_disable((uint16_t)id);
    break;
  case USER_MANAGER:
    result = manager_disable((uint16_t)id);
    break;
  case USER_PLAYER:
    result = player_disable((uint16_t)id);
    break;
  default:
    puts("Invalid user type.");
    return;
  }
  puts(result ? "Disabled." : "Not found or cannot be disabled.");
}
