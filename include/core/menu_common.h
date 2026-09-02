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

#define MENU_ANSI_RESET "\033[0m"
#define MENU_ANSI_BOLD_CYAN "\033[1;36m"
#define MENU_ANSI_BOLD_YELLOW "\033[1;33m"
#define MENU_ANSI_BOLD_GREEN "\033[1;32m"

// Formatted utility prints
void menu_printHeader(const char *title);
void menu_printOption(const char *number, const char *label);
void menu_printSuccess(const char *message);

// Read input
int_fast64_t menu_readNumber(const char *prompt);
void menu_readText(const char *prompt, char *output);

// Output entity profile
void menu_printAdmin(const FAdmin *admin);
void menu_printTeam(const FTeam *team);
void menu_printManager(const FManager *manager);
void menu_printPlayer(const FPlayer *player);

// Output entity list
void menu_listAdmins(void);
void menu_listTeams(void);
void menu_listManagers(void);
void menu_listPlayers(void);

// Generic user management
void menu_createUser(EUserType type);
void menu_updateUser(EUserType type);
void menu_disableUser(EUserType type);

#endif
