// menu_admin.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Admin menu functions
//
// Also, death to Code::Blocks

#ifndef M6328_MENU_ADMIN
#define M6328_MENU_ADMIN

#include <stdint.h>

// Base admin menu
uint_fast8_t menu_admin(void);

// Wrappers to `menu_users` for admin
uint_fast8_t menu_adminAdmins(void);
uint_fast8_t menu_adminManagers(void);
uint_fast8_t menu_adminPlayers(void);

// Admin view for team management
uint_fast8_t menu_adminTeams(void);

#endif
