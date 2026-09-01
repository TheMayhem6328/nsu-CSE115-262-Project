// main.c
// Zahiruzzman Chowdhury
//
// Main runtime code
//
// Also, death to Code::Blocks

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#endif

#include "admin.h"   // IWYU pragma: keep
#include "manager.h" // IWYU pragma: keep
#include "player.h"  // IWYU pragma: keep
#include "session.h"
#include "team.h"    // IWYU pragma: keep
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

uint_fast8_t validatedLogin(EUserType type, const char *label) {
  uint_fast8_t state = 0;
  int userID;

  // Input from user
  printf("Enter %s ID: ", label);
  scanf("%d", &userID);

  // Login
  if (user_login(type, userID)) {
    puts("Successfully logged in");
  } else {
    printf("Invalid %s ID. Please try again\n", label);
    state = 1;
  }
  return state;
}

int main(void) {
  uint_fast8_t loopFlag;
  long userChoice;
  char userInput[NAME_LENGTH];
  // Login flow
  do {
    loopFlag = 0;
    puts("Who do you want to login as?");
    puts("  1: Admin");
    puts("  2: Manager");
    puts("  3: Player");
    puts("  99: Initialize Program");
    printf("Your choice: ");
    fgets(userInput, sizeof(userInput), stdin);
    userChoice = strtol(userInput, (void*)0, 10);

    switch (userChoice) {
    case 1:
      USER_CURRENT.type = USER_ADMIN;
      loopFlag = validatedLogin(USER_CURRENT.type, "Admin");
      break;
    case 2:
      USER_CURRENT.type = USER_MANAGER;
      loopFlag = validatedLogin(USER_CURRENT.type, "Manager");
      break;
    case 3:
      USER_CURRENT.type = USER_PLAYER;
      loopFlag = validatedLogin(USER_CURRENT.type, "Player");
      break;
    case 99:
      break;
    default:
      puts("Invalid option - please try again");
      loopFlag = 1;
    }
  } while (loopFlag);

  // user_login(FUser type, uint16_t id)

  return 0;
}
