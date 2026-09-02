// main.c
// Zahiruzzman Chowdhury
//
// 2513048043
// CSE115.17
//
// Main runtime code
//
// Also, death to Code::Blocks

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "file_common.h"
#include "menu_main.h"
#include <stdint.h>
#include <stdio.h>

int main(void) {
  uint_fast8_t loopFlag = 0;
  if (!file_dataFileExists()) {
    puts("Data file doesn't exist. Running `file_createDataFile`");
    file_createDataFile();
    puts("Created data file. Executing regular program now");
  } else {
    file_loadDataFile();
  }

  do {
    loopFlag = menu_main();
  } while (loopFlag);

  return 0;
}
