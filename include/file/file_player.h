#ifndef M6328_FILE_PLAYER
#define M6328_FILE_PLAYER

#include "types.h"
#include <stdio.h>

void file_writePlayer(FILE *fp, const FPlayer *player);
void file_readPlayer(FILE *fp, FPlayer *player);

#endif
