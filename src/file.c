// file.c
// Zahiruzzman Chowdhury
//
// Utility functions for managing data file
//
// Also, death to Code::Blocks

// TODO: Refactor to split file into separate domains

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "admin.h"
#endif

#include "file.h"
#include "session.h"
#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compiler macros for data record size

#define UINT8_BYTES 1u
#define UINT16_BYTES 2u

#define FILE_RECORD_SIZE_ADMIN                                                 \
  (              /* Basics */                                                  \
   UINT16_BYTES  /* id */                                                      \
   + NAME_LENGTH /* name */                                                    \
   + UINT8_BYTES /* isActive */                                                \
  )

#define FILE_RECORD_SIZE_TEAM                                                  \
  (              /* Basics */                                                  \
   UINT16_BYTES  /* id */                                                      \
   + NAME_LENGTH /* name */                                                    \
   + UINT8_BYTES /* isActive */                                                \
                                                                               \
   /* Location metadata */                                                     \
   + 2u * NAME_LENGTH /* city + stadium */                                     \
                                                                               \
   /* Season stats */                                                          \
   + 7u * UINT16_BYTES /* all season stats */                                  \
                                                                               \
   /* Team information */                                                      \
   + UINT16_BYTES                    /* managerID */                           \
   + UINT8_BYTES                     /* playerCount */                         \
   + MAX_TEAM_PLAYERS * UINT16_BYTES /* playerIDs */                           \
  )

#define FILE_RECORD_SIZE_MANAGER                                               \
  (              /* Basics */                                                  \
   UINT16_BYTES  /* id */                                                      \
   + NAME_LENGTH /* name */                                                    \
   + UINT8_BYTES /* isActive */                                                \
  )

#define FILE_RECORD_SIZE_PLAYER                                                \
  (              /* Basics */                                                  \
   UINT16_BYTES  /* id */                                                      \
   + NAME_LENGTH /* name */                                                    \
   + UINT8_BYTES /* isActive */                                                \
                                                                               \
   /* Field identifier */                                                      \
   + 2u * UINT8_BYTES /* position + shirtNumber */                             \
                                                                               \
   /* Personal metadata */                                                     \
   + 3u * UINT8_BYTES /* rating + fitness + isInjured */                       \
                                                                               \
   /* Season stats */                                                          \
   + 3u * UINT16_BYTES /* appearances + goals + assists */                     \
  )

//// Static utility functions

// Big endian write

static void writeBeUint64(FILE *fp, uint64_t val) {
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

static void writeBeUint16(FILE *fp, uint16_t val) {
  // Use bitwise operations to split
  // uint16_t to big endian bytes
  uint8_t buf[2];
  buf[0] = (uint8_t)((val >> 8) & 0xFF);
  buf[1] = (uint8_t)(val & 0xFF);

  // Write bytes to file
  fwrite(buf, 1, 2, fp);
}

static void writeBeUint8(FILE *fp, uint8_t val) {
  // Write bytes to file
  fwrite(&val, 1, 1, fp);
}

// Big endian read

static uint64_t readBeUint64(FILE *fp) {
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

static uint16_t readBeUint16(FILE *fp) {
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

static uint8_t readBeUint8(FILE *fp) {
  // Read bytes
  uint8_t buf[1];
  if (fread(buf, 1, 1, fp) != 1) {
    // Fallback
    return 0;
  }

  // Return value
  return buf[0];
}

// Write data to file

static void writeAdmin(FILE *fp, const FAdmin *admin) {
  if ((admin->isActive)) {
    // Basics
    writeBeUint16(fp, admin->id);
    fwrite(admin->name, 1, NAME_LENGTH, fp);
    writeBeUint8(fp, (uint8_t)admin->isActive);
  }
}

static void writeTeam(FILE *fp, const FTeam *team) {
  if ((team->isActive)) {
    // Basics
    writeBeUint16(fp, team->id);
    fwrite(team->name, 1, NAME_LENGTH, fp);
    writeBeUint8(fp, (uint8_t)team->isActive);

    // Location metadata
    fwrite(team->city, 1, NAME_LENGTH, fp);
    fwrite(team->stadium, 1, NAME_LENGTH, fp);

    // Season stats
    writeBeUint16(fp, team->matchesPlayed);
    writeBeUint16(fp, team->wins);
    writeBeUint16(fp, team->draws);
    writeBeUint16(fp, team->losses);
    writeBeUint16(fp, team->goalsFor);
    writeBeUint16(fp, team->goalsAgainst);
    writeBeUint16(fp, team->points);

    // Team information
    writeBeUint16(fp, team->managerID);
    writeBeUint8(fp, team->playerCount);
    // Player IDs
    for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
      writeBeUint8(fp, team->playerIDs[i]);
    }
  }
}

static void writeManager(FILE *fp, const FManager *manager) {
  if ((manager->isActive)) {
    // Basics
    writeBeUint16(fp, manager->id);
    fwrite(manager->name, 1, NAME_LENGTH, fp);
    writeBeUint8(fp, (uint8_t)manager->isActive);
  }
}

static void writePlayer(FILE *fp, const FPlayer *player) {
  if ((player->isActive)) {
    // Basics
    writeBeUint16(fp, player->id);
    fwrite(player->name, 1, NAME_LENGTH, fp);
    writeBeUint8(fp, (uint8_t)player->isActive);

    // Field identifier
    writeBeUint8(fp, (uint8_t)player->position);
    writeBeUint8(fp, player->shirtNumber);

    // Personal metadata
    writeBeUint8(fp, player->rating);
    writeBeUint8(fp, player->fitness);
    writeBeUint8(fp, (uint8_t)player->isInjured);

    // Season stats
    writeBeUint16(fp, player->appearances);
    writeBeUint16(fp, player->goals);
    writeBeUint16(fp, player->assists);
  }
}

// Read data to file
static void readAdmin(FILE *fp, FAdmin *user) {
  // Basics
  user->id = readBeUint16(fp);
  fread(user->name, 1, NAME_LENGTH, fp);
  user->isActive = (EBoolean)readBeUint8(fp);
}

static void readTeam(FILE *fp, FTeam *team) {
  // Basics
  team->id = readBeUint16(fp);
  fread(team->name, 1, NAME_LENGTH, fp);
  team->isActive = (EBoolean)readBeUint8(fp);

  // Location metadata
  fread(team->city, 1, NAME_LENGTH, fp);
  fread(team->stadium, 1, NAME_LENGTH, fp);

  // Season stats
  team->matchesPlayed = readBeUint16(fp);
  team->wins = readBeUint16(fp);
  team->draws = readBeUint16(fp);
  team->losses = readBeUint16(fp);
  team->goalsFor = readBeUint16(fp);
  team->goalsAgainst = readBeUint16(fp);
  team->points = readBeUint16(fp);

  // Team information
  team->managerID = readBeUint16(fp);
  team->playerCount = readBeUint8(fp);
  // Player IDs
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team->playerIDs[i] = readBeUint8(fp);
  }

  // TODO: Fix pointer handling
  team->manager = NULL;
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team->playerPtrs[i] = NULL;
  }
}

static void readManager(FILE *fp, FManager *manager) {
  // Basics
  manager->id = readBeUint16(fp);
  fread(manager->name, 1, NAME_LENGTH, fp);
  manager->isActive = (EBoolean)readBeUint8(fp);

  // TODO: Fix pointer handling
  manager->teamPtr = NULL;
}

static void readPlayer(FILE *fp, FPlayer *player) {
  // Basics
  player->id = readBeUint16(fp);
  fread(player->name, 1, NAME_LENGTH, fp);
  player->isActive = (EBoolean)readBeUint8(fp);

  // Field identifier
  player->position = (EPlayerPosition)readBeUint8(fp);
  player->shirtNumber = readBeUint8(fp);

  // Personal metadata
  player->rating = readBeUint8(fp);
  player->fitness = readBeUint8(fp);
  player->isInjured = (EBoolean)readBeUint8(fp);

  // Season stats
  player->appearances = readBeUint16(fp);
  player->goals = readBeUint16(fp);
  player->assists = readBeUint16(fp);

  // TODO: Fix pointer handling
  player->teamPtr = NULL;
}

//// Functions

// File Management

uint_fast8_t file_dataFileExists(void) {
  // If file cannot be read, BAD
  FILE *file = fopen(DATAFILE, "r");
  if (file != NULL) {
    fclose(file);
    return 1;
  }

  // Or else, GOOD
  return 0;
}

uint_fast8_t file_createDataFile(void) {
  // Init variables
  char value[NAME_LENGTH] = {0};
  uint16_t id;

  // Get admin ID
  printf("Enter initial admin id: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';
  id = (uint16_t)strtol(value, NULL, 10);

  // Get admin name
  printf("Enter initial admin name: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';

  // Create initial admin struct
  admin_create(id, value);

  // Save contents to file and return success
  return file_saveDataFile();
}

uint_fast8_t file_saveDataFile(void) {
  // If file can't be opened, HALT HALT HALT
  FILE *file = fopen(DATAFILE, "wb");
  if (file == NULL)
    return 0;

  //// Write fixed-bounds content

  // Header
  fwrite("CS115_FB", 1, 8, file);
  writeBeUint8(file, 0);

  // Offsets
  uint64_t adminOffset = 0x21;
  uint64_t teamOffset = adminOffset + (uint64_t)session_enabledAdminCount *
                                          FILE_RECORD_SIZE_ADMIN;
  uint64_t managerOffset =
      teamOffset + (uint64_t)session_enabledTeamCount * FILE_RECORD_SIZE_TEAM;
  uint64_t playerOffset =
      managerOffset +
      (uint64_t)session_enabledManagerCount * FILE_RECORD_SIZE_MANAGER;

  // Write offsets
  writeBeUint64(file, teamOffset);
  writeBeUint64(file, managerOffset);
  writeBeUint64(file, playerOffset);

  //// Write content

  // Admin
  fseek(file, (long)adminOffset, SEEK_SET);
  for (int i = 0; i < session_enabledAdminCount; ++i) {
    writeAdmin(file, session_adminDynamicArray[i]);
  }

  // Team
  fseek(file, (long)teamOffset, SEEK_SET);
  for (int i = 0; i < session_enabledTeamCount; ++i) {
    writeTeam(file, session_teamDynamicArray[i]);
  }

  // Manager
  fseek(file, (long)managerOffset, SEEK_SET);
  for (int i = 0; i < session_enabledManagerCount; ++i) {
    writeManager(file, session_managerDynamicArray[i]);
  }

  // Player
  fseek(file, (long)playerOffset, SEEK_SET);
  for (int i = 0; i < session_enabledPlayerCount; ++i) {
    writePlayer(file, session_playerDynamicArray[i]);
  }

  //// Close

  fclose(file);
  return 1;
}

uint_fast8_t file_loadDataFile(void) {
  // If file can't be opened, HALT HALT HALT
  FILE *fp = fopen(DATAFILE, "rb");
  if (fp == NULL) {
    return 0;
  }

  // Verify file type using magic bytes
  char magic[9];
  if (fread(magic, 1, 8, fp) != 8) {
    fclose(fp);
    return 0;
  }
  magic[8] = '\0';
  if (strcmp(magic, "CS115_FB") != 0) {
    fclose(fp);
    return 0;
  }

  // Read data file revision for the sake of sequential seeking
  uint8_t revision = readBeUint8(fp);
  (void)revision;

  // Read offsets
  uint64_t teamOffset = readBeUint64(fp);
  uint64_t managerOffset = readBeUint64(fp);
  uint64_t playerOffset = readBeUint64(fp);
  const uint64_t adminOffset = 0x21;

  // Get filesize
  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return 0;
  }
  long fileSize = ftell(fp);
  if (fileSize < 0) {
    fclose(fp);
    return 0;
  }

  // If offsets are weirdly arranged, stop
  if (teamOffset < adminOffset || teamOffset > (uint64_t)fileSize) {
    fclose(fp);
    return 0;
  }

  // Calculate counts
  session_adminCount =
      (uint_fast8_t)((teamOffset - adminOffset) / FILE_RECORD_SIZE_ADMIN);
  session_teamCount =
      (uint_fast8_t)((managerOffset - teamOffset) / FILE_RECORD_SIZE_TEAM);
  session_managerCount =
      (uint_fast8_t)((playerOffset - managerOffset) / FILE_RECORD_SIZE_MANAGER);
  session_playerCount =
      (uint_fast8_t)((fileSize >= (long)playerOffset)
                         ? ((uint64_t)fileSize - playerOffset) /
                               FILE_RECORD_SIZE_PLAYER
                         : 0);

  // Calculate counts
  session_enabledAdminCount = session_adminCount;
  session_enabledTeamCount = session_teamCount;
  session_enabledManagerCount = session_managerCount;
  session_enabledPlayerCount = session_playerCount;

  // Initialize session arrays
  session_adminDynamicArray = NULL;
  session_teamDynamicArray = NULL;
  session_managerDynamicArray = NULL;
  session_playerDynamicArray = NULL;

  //// Populate session arrays
  // TODO: Refactor to make generics and reduce clutter

  // Admin
  if (session_adminCount > 0) {
    session_adminDynamicArray =
        malloc((size_t)session_adminCount * sizeof(FAdmin *));
    if (session_adminDynamicArray == NULL) {
      fclose(fp);
      return 0;
    }
    fseek(fp, (long)adminOffset, SEEK_SET);
    for (uint_fast8_t i = 0; i < session_adminCount; ++i) {
      session_adminDynamicArray[i] = malloc(sizeof(FAdmin));
      if (session_adminDynamicArray[i] == NULL) {
        fclose(fp);
        return 0;
      }
      readAdmin(fp, session_adminDynamicArray[i]);
    }
  }

  // Team
  if (session_teamCount > 0) {
    session_teamDynamicArray =
        malloc((size_t)session_teamCount * sizeof(FTeam *));
    if (session_teamDynamicArray == NULL) {
      fclose(fp);
      return 0;
    }
    fseek(fp, (long)teamOffset, SEEK_SET);
    for (uint_fast8_t i = 0; i < session_teamCount; ++i) {
      session_teamDynamicArray[i] = malloc(sizeof(FTeam));
      if (session_teamDynamicArray[i] == NULL) {
        fclose(fp);
        return 0;
      }
      readTeam(fp, session_teamDynamicArray[i]);
    }
  }

  // Manager
  if (session_managerCount > 0) {
    session_managerDynamicArray =
        malloc((size_t)session_managerCount * sizeof(FManager *));
    if (session_managerDynamicArray == NULL) {
      fclose(fp);
      return 0;
    }
    fseek(fp, (long)managerOffset, SEEK_SET);
    for (uint_fast8_t i = 0; i < session_managerCount; ++i) {
      session_managerDynamicArray[i] = malloc(sizeof(FManager));
      if (session_managerDynamicArray[i] == NULL) {
        fclose(fp);
        return 0;
      }
      readManager(fp, session_managerDynamicArray[i]);
    }
  }

  // Player
  if (session_playerCount > 0) {
    session_playerDynamicArray =
        malloc((size_t)session_playerCount * sizeof(FPlayer *));
    if (session_playerDynamicArray == NULL) {
      fclose(fp);
      return 0;
    }
    fseek(fp, (long)playerOffset, SEEK_SET);
    for (uint_fast8_t i = 0; i < session_playerCount; ++i) {
      session_playerDynamicArray[i] = malloc(sizeof(FPlayer));
      if (session_playerDynamicArray[i] == NULL) {
        fclose(fp);
        return 0;
      }
      readPlayer(fp, session_playerDynamicArray[i]);
    }
  }

  //// Close

  fclose(fp);
  return 1;
}
