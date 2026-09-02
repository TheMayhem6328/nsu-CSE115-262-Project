// file_manager.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Manager file serialization functions
//
// Also, death to Code::Blocks

#ifndef M6328_FILE_MANAGER
#define M6328_FILE_MANAGER

#include "types.h"
#include <stdio.h>

void file_writeManager(FILE *fp, const FManager *manager);
void file_readManager(FILE *fp, FManager *manager);

#endif
