// file_player.h
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Player file serialization functions
//
// Also, death to Code::Blocks

#ifndef M6328_FILE_PLAYER
#define M6328_FILE_PLAYER

#include "types.h"
#include <stdio.h>

void file_writePlayer(FILE *fp, const FPlayer *player);
void file_readPlayer(FILE *fp, FPlayer *player);

#endif
