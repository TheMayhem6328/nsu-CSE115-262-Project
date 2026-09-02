// file_admin.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Admin file serialization functions
//
// Also, death to Code::Blocks

#ifndef M6328_FILE_ADMIN
#define M6328_FILE_ADMIN

#include "types.h"
#include <stdio.h>

void file_writeAdmin(FILE *fp, const FAdmin *admin);
void file_readAdmin(FILE *fp, FAdmin *user);

#endif
