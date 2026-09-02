#include "menu_player.h"
#include "file_common.h"
#include "menu_common.h"
#include "session.h"
#include <stdio.h>

uint_fast8_t menu_playerProfile(void) {
  FPlayer *player = (FPlayer *)USER_CURRENT.userObj;
  if (player != NULL)
    printf("%u: %s, position %u, shirt %u, rating %u, fitness %u\n", player->id,
           player->name, (unsigned int)player->position, player->shirtNumber,
           player->rating, player->fitness);
  return 0;
}

//// Base player menu

uint_fast8_t menu_player(void) {
  for (;;) {
    puts("\nPlayer menu");
    puts("  0: Save and Quit");
    puts("  1: View my profile");
    int_fast64_t choice = menu_readNumber("Your choice: ");
    switch (choice) {
    case 0:
      file_saveDataFile();
      session_exit();
      return 0;
    case 1:
      menu_playerProfile();
      break;
    default:
      puts("Invalid option.");
    }
  }
}
