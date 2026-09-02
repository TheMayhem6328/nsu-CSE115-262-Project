#ifndef M6328_FILE_TEAM
#define M6328_FILE_TEAM

#include "types.h"
#include <stdio.h>

void file_writeTeam(FILE *fp, const FTeam *team);
void file_readTeam(FILE *fp, FTeam *team);

#endif
