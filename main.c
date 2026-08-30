/*
main.c
Zahiruzzman Chowdhury

Keeping it compatible with C89
Since I do not trust any environment
outside mine

Also, death to Code::Blocks
*/

#ifndef CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "types.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    FManager s;
    s.id = 2;
    strncpy(s.name, "Hello There!", NAME_LENGTH);
    s.name[sizeof(s.name) - 1] = '\0';
    printf("%d %s\n", s.id, s.name);
    return 0;
}