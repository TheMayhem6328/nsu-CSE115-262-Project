// file_manager.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Manager file serialization
//
// Also, death to Code::Blocks

#include "file_manager.h"
#include "file_common.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>

void file_writeManager(FILE *fp, const FManager *manager) {
  if (!manager->isActive) {
    return;
  }

  file_writeBeUint16(fp, manager->id);
  fwrite(manager->name, 1, NAME_LENGTH, fp);
  file_writeBeUint8(fp, (uint8_t)manager->isActive);
}

void file_readManager(FILE *fp, FManager *manager) {
  manager->id = file_readBeUint16(fp);
  fread(manager->name, 1, NAME_LENGTH, fp);
  manager->isActive = (EBoolean)file_readBeUint8(fp);
  manager->teamPtr = NULL;
}
