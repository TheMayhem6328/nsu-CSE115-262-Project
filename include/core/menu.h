// menu.h
// Zahiruzzman Chowdhury
//
// Functions to define user-facing menus
//
// Also, death to Code::Blocks

#ifndef M6328_MENU
#define M6328_MENU

#include <stdint.h>

//// User actions
uint_fast8_t menu_main(void);
uint_fast8_t menu_admin(void);
uint_fast8_t menu_manager(void);
uint_fast8_t menu_player(void);

#endif
