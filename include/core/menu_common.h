// menu_common.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Shared menu utility functions
//
// Also, death to Code::Blocks

#ifndef M6328_MENU_COMMON
#define M6328_MENU_COMMON

#include "session.h"
#include <stdint.h>

// Read input
int_fast64_t menu_readNumber(const char *prompt);
void menu_readText(const char *prompt, char *output);

// List entities
void menu_listAdmins(void);
void menu_listManagers(void);
void menu_listPlayers(void);
void menu_listTeams(void);

// Generic user management
void menu_createUser(EUserType type);
void menu_disableUser(EUserType type);

#endif
