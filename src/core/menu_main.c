// menu_main.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Main menu implementation
//
// Also, death to Code::Blocks

#include "menu_main.h"
#include "file_common.h"
#include "menu_admin.h"
#include "menu_common.h"
#include "menu_manager.h"
#include "menu_player.h"
#include "session.h"
#include <stdio.h>
#include <stdlib.h>

//// Utility static functions

static int validatedLogin(EUserType userType, const char *label) {
  unsigned int userID;
  char userInput[NAME_LENGTH];

  // Take ID
  printf("Enter %s ID: ", label);
  if (fgets(userInput, sizeof(userInput), stdin) == NULL)
    return 1;
  userID = (unsigned int)strtol(userInput, NULL, 10);

  // Validity check
  if (!session_login(userType, (uint16_t)userID)) {
    printf("Invalid %s ID. Please try again\n", label);
    return 1;
  }

  // If valid, goto appropriate menu based on user type
  printf("Successfully logged in as (%s) %s\n", label,
         session_getCurrentUserName());
  switch (userType) {
  case USER_ADMIN:
    menu_admin();
    return 0;
  case USER_MANAGER:
    menu_manager();
    return 0;
  case USER_PLAYER:
    menu_player();
    return 0;
  default:
    return 1;
  }
}

//// Functions

uint_fast8_t menu_main(void) {
  long userChoice;
  char userInput[NAME_LENGTH];

  puts("Who do you want to login as?");
  puts("  0: Save and Exit");
  puts("  1: Admin");
  puts("  2: Manager");
  puts("  3: Player");
  printf("Your choice: ");
  if (fgets(userInput, sizeof(userInput), stdin) == NULL)
    return 0;
  userChoice = strtol(userInput, NULL, 10);

  switch (userChoice) {
  case 0:
    file_saveDataFile();
    session_exit();
    return 0;
  case 1:
    return (uint_fast8_t)validatedLogin(USER_ADMIN, "Admin");
  case 2:
    return (uint_fast8_t)validatedLogin(USER_MANAGER, "Manager");
  case 3:
    return (uint_fast8_t)validatedLogin(USER_PLAYER, "Player");
  default:
    puts("Invalid option - please try again");
    return 1;
  }
}
