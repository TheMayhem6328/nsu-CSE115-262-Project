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

//// Read input

int_fast64_t menu_readNumber(const char *prompt) {
  char input[NAME_LENGTH];
  printf("%s", prompt);
  if (fgets(input, sizeof(input), stdin) == NULL)
    return -1;
  return (uint_fast32_t)strtol(input, NULL, 10);
}

void menu_readText(const char *prompt, char *output) {
  printf("%s", prompt);
  if (fgets(output, NAME_LENGTH, stdin) == NULL) {
    output[0] = '\0';
    return;
  }
  output[strcspn(output, "\n")] = '\0';
}

//// List entities

void menu_listAdmins(void) {
  for (uint_fast8_t i = 0; i < session_adminCount; ++i)
    printf("%u: %s (%s)\n", session_adminDynamicArray[i]->id,
           session_adminDynamicArray[i]->name,
           session_adminDynamicArray[i]->isActive ? "active" : "disabled");
}

void menu_listManagers(void) {
  for (uint_fast8_t i = 0; i < session_managerCount; ++i)
    printf("%u: %s (%s)\n", session_managerDynamicArray[i]->id,
           session_managerDynamicArray[i]->name,
           session_managerDynamicArray[i]->isActive ? "active" : "disabled");
}

void menu_listPlayers(void) {
  for (uint_fast8_t i = 0; i < session_playerCount; ++i)
    printf("%u: %s, position %u, shirt %u, rating %u\n",
           session_playerDynamicArray[i]->id,
           session_playerDynamicArray[i]->name,
           (unsigned int)session_playerDynamicArray[i]->position,
           session_playerDynamicArray[i]->shirtNumber,
           session_playerDynamicArray[i]->rating);
}

void menu_listTeams(void) {
  for (uint_fast8_t i = 0; i < session_teamCount; ++i)
    printf("%u: %s, manager %u, %u players\n", session_teamDynamicArray[i]->id,
           session_teamDynamicArray[i]->name,
           session_teamDynamicArray[i]->managerID,
           session_teamDynamicArray[i]->playerCount);
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
  puts("Created.");
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
