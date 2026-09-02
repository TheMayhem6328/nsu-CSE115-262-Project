// menu.c
// Zahiruzzman Chowdhury
//
// Functions to define user-facing menus
//
// Also, death to Code::Blocks

#include "menu.h"
#include "session.h"
#include "file_common.h"
#include <stdio.h>
#include <stdlib.h>

static int validatedLogin(EUserType usertype, const char *label) {
  unsigned int userID;
  char userInput[NAME_LENGTH];

  // Input from user
  printf("Enter %s ID: ", label);
  fgets(userInput, sizeof(userInput), stdin);
  userID = (unsigned int)strtol(userInput, (void *)0, 10);

  // Login
  if (session_login(usertype, (uint16_t)userID)) {
    printf("Successfully logged in as (%s) %s\n", label, session_getCurrentUserName());
    return 0;
  } else {
    printf("Invalid %s ID. Please try again\n", label);
    return 1;
  }
}

uint_fast8_t menu_main(void) {
  long userChoice;
  char userInput[NAME_LENGTH];

  // Login flow
  puts("Who do you want to login as?");
  puts("  0: Save and Exit");
  puts("  1: Admin");
  puts("  2: Manager");
  puts("  3: Player");
  printf("Your choice: ");
  fgets(userInput, sizeof(userInput), stdin);
  userChoice = strtol(userInput, (void *)0, 10);

  // Load user type specific menu
  switch (userChoice) {
  case 0:
    file_saveDataFile();
    session_exit();
    return 0;
  case 1:
    return (uint_fast8_t)validatedLogin(USER_ADMIN, "Admin");
    break;
  case 2:
    return (uint_fast8_t)validatedLogin(USER_MANAGER, "Manager");
    break;
  case 3:
    return (uint_fast8_t)validatedLogin(USER_PLAYER, "Player");
    break;
  default:
    puts("Invalid option - please try again");
    return 1;
  }
}