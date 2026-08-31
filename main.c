// main.c
// Zahiruzzman Chowdhury
//
// Main runtime code
//
// Also, death to Code::Blocks

#ifndef _CRT_SECURE_NO_WARNINGS
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
