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
#include "manager.h"
#include "menu_common.h"
#include "player.h"
#include "team.h"
#include <stdio.h>

//// Utility static functions

// Generic CRUD menu
static uint_fast8_t menu_users(EUserType type, const char *title) {
  for (;;) {
    menu_printHeader(title);
    menu_printOption("0", "Back");
    menu_printOption("1", "List");
    menu_printOption("2", "Create");
    menu_printOption("3", "Disable");
    menu_printOption("4", "Update name");
    menu_printOption("5", "List without team");
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
    case 4:
      menu_updateUser(type);
      break;
    case 5:
      if (type == USER_MANAGER)
        manager_listManagersWithoutTeam();
      else if (type == USER_PLAYER)
        player_listPlayersWithoutTeam();
      else
        puts("Admins do not belong to teams.");
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
    menu_printHeader("Team management");
    menu_printOption("0", "Back");
    menu_printOption("1", "List");
    menu_printOption("2", "Create");
    menu_printOption("3", "Disable");
    menu_printOption("4", "Team wizard");
    menu_printOption("5", "List teams without manager");
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
        menu_printSuccess("Created");
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
    case 4: {
      int_fast64_t teamID = menu_readNumber("Team ID: ");
      char teamName[NAME_LENGTH];
      menu_readText("Team name: ", teamName);
      if (teamID < 0 || teamID > UINT16_MAX || teamName[0] == '\0') {
        puts("Invalid team data.");
        break;
      }
      FTeam *team = team_create((uint16_t)teamID, teamName);

      menu_printOption("1", "Assign existing manager");
      menu_printOption("2", "Create manager");
      int_fast64_t managerChoice = menu_readNumber("Manager option: ");

      FManager *manager = NULL;

      switch (managerChoice) {
      case 1: {
        int_fast64_t managerID = menu_readNumber("Manager ID: ");
        if (managerID >= 0 && managerID <= UINT16_MAX)
          manager = manager_retrieve((uint16_t)managerID);
        break;
      }

      case 2: {
        int_fast64_t managerID = menu_readNumber("New manager ID: ");
        char managerName[NAME_LENGTH];
        menu_readText("New manager name: ", managerName);
        if (managerID >= 0 && managerID <= UINT16_MAX && managerName[0] != '\0')
          manager = manager_create((uint16_t)managerID, managerName);
        break;
      }
      }

      if (manager != NULL && team_assignManager(team, manager))
        menu_printSuccess("Team and manager created");
      else
        menu_printSuccess("Team created without a manager");
      break;
    }

    case 5:
      team_listTeamsWithoutManager();
      break;
    default:
      puts("Invalid option.");
    }
  }
}

//// Base admin menu

uint_fast8_t menu_admin(void) {
  for (;;) {
    menu_printHeader("Admin menu");
    menu_printOption("0", "Save and Quit");
    menu_printOption("1", "Admin accounts");
    menu_printOption("2", "Manager accounts");
    menu_printOption("3", "Teams");
    menu_printOption("4", "Player accounts");
    menu_printOption("5", "My information");
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
    case 5:
      menu_printAdmin((FAdmin *)USER_CURRENT.userObj);
      break;
    default:
      puts("Invalid option.");
    }
  }
}
