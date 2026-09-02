// menu_admin.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Admin menu implementation
//
// Also, death to Code::Blocks

#include "menu_admin.h"
#include "file_common.h"
#include "menu_common.h"
#include "team.h"
#include <stdio.h>

//// Utility static functions

// Generic CRUD menu
static uint_fast8_t menu_users(EUserType type, const char *title) {
  for (;;) {
    printf("\n%s\n", title);
    puts("  0: Back");
    puts("  1: List");
    puts("  2: Create");
    puts("  3: Disable");
    int_fast64_t choice = menu_readNumber("Your choice: ");
    switch (choice) {
    case 0:
      return 0;
    case 1:
      switch (type) {
      case USER_ADMIN:
          menu_listAdmins();
          break;
      case USER_MANAGER:
          menu_listManagers();
          break;
      case USER_PLAYER:
          menu_listPlayers();
          break;
      default:
        return 1;
      }
      break;
    case 2:
      menu_createUser(type);
      break;
    case 3:
      menu_disableUser(type);
      break;
    default:
      puts("Invalid option.");
    }
  }
}

//// Wrappers to `menu_users` for admin

uint_fast8_t menu_adminAdmins(void) {
  return menu_users(USER_ADMIN, "Admin accounts");
}
uint_fast8_t menu_adminManagers(void) {
  return menu_users(USER_MANAGER, "Manager accounts");
}
uint_fast8_t menu_adminPlayers(void) {
  return menu_users(USER_PLAYER, "Player accounts");
}

//// Admin view for team management

uint_fast8_t menu_adminTeams(void) {
  for (;;) {
    puts("\nTeams");
    puts("  0: Back");
    puts("  1: List");
    puts("  2: Create");
    puts("  3: Disable");
    int_fast64_t choice = menu_readNumber("Your choice: ");
    switch (choice) {
    case 0:
      return 0;
    case 1:
      menu_listTeams();
      break;
    case 2: {
      char name[NAME_LENGTH];
      int_fast64_t id = menu_readNumber("ID: ");
      menu_readText("Name: ", name);
      if (id >= 0 && id <= UINT16_MAX && name[0] != '\0') {
        team_create((uint16_t)id, name);
        puts("Created.");
      } else
        puts("Invalid data.");
      break;
    }
    case 3: {
      int_fast64_t id = menu_readNumber("ID to disable: ");
      if (id >= 0 && id <= UINT16_MAX)
        puts(team_disable((uint16_t)id) ? "Disabled." : "Not found.");
      else
        puts("Invalid ID.");
      break;
    }
    default:
      puts("Invalid option.");
    }
  }
}

//// Base admin menu

uint_fast8_t menu_admin(void) {
  for (;;) {
    puts("\nAdmin menu");
    puts("  0: Save and Quit");
    puts("  1: Admin accounts");
    puts("  2: Manager accounts");
    puts("  3: Teams");
    puts("  4: Player accounts");
    int_fast64_t choice = menu_readNumber("Your choice: ");
    switch (choice) {
    case 0:
      file_saveDataFile();
      session_exit();
      return 0;
    case 1:
      menu_adminAdmins();
      break;
    case 2:
      menu_adminManagers();
      break;
    case 3:
      menu_adminTeams();
      break;
    case 4:
      menu_adminPlayers();
      break;
    default:
      puts("Invalid option.");
    }
  }
}
