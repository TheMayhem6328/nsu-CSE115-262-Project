// menu_player.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Player menu implementation
//
// Also, death to Code::Blocks

#include "menu_player.h"
#include "file_common.h"
#include "menu_common.h"
#include "player.h"
#include "session.h"
#include <stdio.h>
#include <string.h>

//// Utility static functions

static void menu_playerTeam(void) {
  FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
  if (player == NULL || player->teamPtr == NULL) {
    puts("You are not assigned to a team.");
    return;
  }
  menu_printTeam(player->teamPtr);
}

static void menu_playerMates(void) {
  FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
  if (player == NULL || player->teamPtr == NULL) {
    puts("You are not assigned to a team.");
    return;
  }
  puts("\nTeam mates:");
  for (uint_fast8_t i = 0; i < player->teamPtr->playerCount; ++i) {
    FPlayer *mate = player->teamPtr->playerPtrs[i];
    if (mate != NULL && mate != player)
      printf("%u: %s\n", mate->id, mate->name);
  }
}

//// Base player menu

uint_fast8_t menu_player(void) {
  for (;;) {
    menu_printHeader("Player menu");
    menu_printOption("0", "Save and Quit");
    menu_printOption("1", "View my profile");
    menu_printOption("2", "View my team");
    menu_printOption("3", "View my team mates");
    menu_printOption("4", "Change name");
    menu_printOption("5", "Set injury status");
    menu_printOption("6", "Leave team");
    int_fast64_t choice = menu_readNumber("Your choice: ");
    switch (choice) {
    case 0:
      file_saveDataFile();
      session_exit();
      return 0;
    case 1:
      menu_playerProfile();
      break;
    case 2:
      menu_playerTeam();
      break;
    case 3:
      menu_playerMates();
      break;
    case 4: {
      FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
      char name[NAME_LENGTH];
      menu_readText("New name: ", name);
      if (player != NULL && name[0] != '\0') {
        strncpy(player->name, name, NAME_LENGTH);
        menu_printSuccess("Updated");
      } else
        puts("Invalid name.");
      break;
    }
    case 5: {
      FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
      int_fast64_t injured = menu_readNumber("Injured? (0/1): ");
      if (player != NULL && (injured == 0 || injured == 1)) {
        player->isInjured = (EBoolean)injured;
        menu_printSuccess("Updated");
      } else
        puts("Invalid injury status.");
      break;
    }
    case 6:
      puts(player_leaveTeam((FPlayer *)USER_CURRENT.userObj)
               ? "Left team."
               : "You are not in a team.");
      break;
    default:
      puts("Invalid option.");
    }
  }
}

//// Player information
uint_fast8_t menu_playerProfile(void) {
  FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
  menu_printPlayer(player);
  return 0;
}
