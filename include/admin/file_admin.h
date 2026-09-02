#ifndef M6328_FILE_ADMIN
#define M6328_FILE_ADMIN

#include "types.h"
#include <stdio.h>

void file_writeAdmin(FILE *fp, const FAdmin *admin);
void file_readAdmin(FILE *fp, FAdmin *user);

#endif
