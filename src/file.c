// file.c
// Zahiruzzman Chowdhury
//
// Utility functions for managing data file
//
// Also, death to Code::Blocks

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "admin.h"
#endif

#include "file.h"
#include "session.h"
#include "types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Write data
static void file_writeAdmin(FILE *fp, const FAdmin *user) {
  file_writeBeUint16(fp, user->id);
  fwrite(user->name, 1, NAME_LENGTH, fp);
  file_writeBeUint8(fp, (uint8_t)user->isActive);
}
static void file_writeTeam(FILE *fp, const FTeam *user);
static void file_writeManager(FILE *fp, const FManager *user);
static void file_writePlayer(FILE *fp, const FPlayer *user);

// Read data
static void file_readAdmin(FILE *fp, FAdmin *user) {
  user->id = file_readBeUint16(fp);
  fread(user->name, 1, NAME_LENGTH, fp);
  user->isActive = (EBoolean)file_readBeUint8(fp);
}
static void file_readTeam(FILE *fp, FTeam *user);
static void file_readManager(FILE *fp, FManager *user);
static void file_readPlayer(FILE *fp, FPlayer *user);

// Big Endian Write

void file_writeBeUint64(FILE *fp, uint64_t val) {
  // Use bitwise operations to split
  // uint64_t to big endian bytes
  uint8_t buf[8];
  buf[0] = (uint8_t)((val >> 56) & 0xFF);
  buf[1] = (uint8_t)((val >> 48) & 0xFF);
  buf[2] = (uint8_t)((val >> 40) & 0xFF);
  buf[3] = (uint8_t)((val >> 32) & 0xFF);
  buf[4] = (uint8_t)((val >> 24) & 0xFF);
  buf[5] = (uint8_t)((val >> 16) & 0xFF);
  buf[6] = (uint8_t)((val >> 8) & 0xFF);
  buf[7] = (uint8_t)(val & 0xFF);

  // Write bytes to file
  fwrite(buf, 1, 8, fp);
}

void file_writeBeUint16(FILE *fp, uint16_t val) {
  // Use bitwise operations to split
  // uint16_t to big endian bytes
  uint8_t buf[2];
  buf[0] = (uint8_t)((val >> 8) & 0xFF);
  buf[1] = (uint8_t)(val & 0xFF);

  // Write bytes to file
  fwrite(buf, 1, 2, fp);
}

void file_writeBeUint8(FILE *fp, uint8_t val) {
  // Write bytes to file
  fwrite(&val, 1, 1, fp);
}

// Big Endian Read

uint64_t file_readBeUint64(FILE *fp) {
  // Read bytes
  uint8_t buf[8];
  if (fread(buf, 1, 8, fp) != 8) {
    // Fallback
    return 0;
  }

  // Use bitwise operations to join bytes
  // into one uint64_t
  return ((uint64_t)buf[0] << 56) | ((uint64_t)buf[1] << 48) |
         ((uint64_t)buf[2] << 40) | ((uint64_t)buf[3] << 32) |
         ((uint64_t)buf[4] << 24) | ((uint64_t)buf[5] << 16) |
         ((uint64_t)buf[6] << 8) | ((uint64_t)buf[7]);
}

uint16_t file_readBeUint16(FILE *fp) {
  // Read bytes
  uint8_t buf[2];
  if (fread(buf, 1, 2, fp) != 2) {
    // Fallback
    return 0;
  }

  // Use bitwise operations to join bytes
  // into one uint16_t
  return (uint16_t)((uint16_t)buf[0] << 8) | ((uint16_t)buf[1]);
}

uint8_t file_readBeUint8(FILE *fp) {
  // Read bytes
  uint8_t buf[1];
  if (fread(buf, 1, 1, fp) != 1) {
    // Fallback
    return 0;
  }

  // Return value
  return buf[0];
}

// File Management

uint_fast8_t file_dataFileExists(void) {
  FILE *file = fopen(DATAFILE, "r");
  if (file != NULL) {
    fclose(file);
    return 1;
  }
  return 0;
}

uint_fast8_t file_createDataFile(void) {
  FAdmin initialAdmin;
  char value[NAME_LENGTH] = {0};
  uint16_t id;

  printf("Enter initial admin id: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';
  id = (uint16_t)strtol(value, NULL, 10);

  printf("Enter initial admin name: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';

  initialAdmin = admin_create(id, value);

  session_adminCount += 1;
  session_adminDynamicArray = malloc(sizeof(FAdmin *) * session_adminCount);
  session_adminDynamicArray[0] = malloc(sizeof(FAdmin));
  *session_adminDynamicArray[0] = initialAdmin;

  return file_saveDataFile();
}

uint_fast8_t file_saveDataFile(void) {
  FILE *file = fopen(DATAFILE, "wb");
  if (file == NULL)
    return 0;

  // Header
  fwrite("CS115_FB", 1, 8, file);
  file_writeBeUint8(file, 0);

  // Offsets
  uint64_t adminOffset = 0x21;
  uint64_t adminSize = session_adminCount * sizeof(FAdmin);
  uint64_t teamOffset = adminOffset + adminSize;
  uint64_t managerOffset = teamOffset + (session_teamCount * sizeof(FTeam));
  uint64_t playerOffset =
      managerOffset + (session_managerCount * sizeof(FManager));

  // Write offsets
  file_writeBeUint64(file, teamOffset);
  file_writeBeUint64(file, managerOffset);
  file_writeBeUint64(file, playerOffset);

  // Write content
  fseek(file, (long)adminOffset, SEEK_SET);
  for (int i = 0; i < session_adminCount; i++) {
    file_writeAdmin(file, session_adminDynamicArray[i]);
  }

  fclose(file);
  return 1;
}