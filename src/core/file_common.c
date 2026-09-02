#include "file_common.h"
#include "file_admin.h"
#include "file_manager.h"
#include "file_player.h"
#include "file_team.h"
#include "admin.h"
#include "session.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT8_BYTES 1u
#define UINT16_BYTES 2u

#define FILE_RECORD_SIZE_ADMIN                                                 \
  (                                                                           \
    UINT16_BYTES + NAME_LENGTH + UINT8_BYTES                                  \
  )

#define FILE_RECORD_SIZE_TEAM                                                  \
  (                                                                           \
    UINT16_BYTES + NAME_LENGTH + UINT8_BYTES + 2u * NAME_LENGTH +             \
    7u * UINT16_BYTES + UINT16_BYTES + UINT8_BYTES +                           \
    MAX_TEAM_PLAYERS * UINT8_BYTES                                            \
  )

#define FILE_RECORD_SIZE_MANAGER                                               \
  (                                                                           \
    UINT16_BYTES + NAME_LENGTH + UINT8_BYTES                                  \
  )

#define FILE_RECORD_SIZE_PLAYER                                                \
  (                                                                           \
    UINT16_BYTES + NAME_LENGTH + UINT8_BYTES + 2u * UINT8_BYTES +             \
    3u * UINT8_BYTES + 3u * UINT16_BYTES                                     \
  )

void file_writeBeUint64(FILE *fp, uint64_t val) {
  uint8_t buf[8];
  buf[0] = (uint8_t)((val >> 56) & 0xFFu);
  buf[1] = (uint8_t)((val >> 48) & 0xFFu);
  buf[2] = (uint8_t)((val >> 40) & 0xFFu);
  buf[3] = (uint8_t)((val >> 32) & 0xFFu);
  buf[4] = (uint8_t)((val >> 24) & 0xFFu);
  buf[5] = (uint8_t)((val >> 16) & 0xFFu);
  buf[6] = (uint8_t)((val >> 8) & 0xFFu);
  buf[7] = (uint8_t)(val & 0xFFu);
  fwrite(buf, 1, 8, fp);
}

void file_writeBeUint16(FILE *fp, uint16_t val) {
  uint8_t buf[2];
  buf[0] = (uint8_t)((val >> 8) & 0xFFu);
  buf[1] = (uint8_t)(val & 0xFFu);
  fwrite(buf, 1, 2, fp);
}

void file_writeBeUint8(FILE *fp, uint8_t val) {
  fwrite(&val, 1, 1, fp);
}

uint64_t file_readBeUint64(FILE *fp) {
  uint8_t buf[8];
  if (fread(buf, 1, 8, fp) != 8) {
    return 0;
  }

  return ((uint64_t)buf[0] << 56) | ((uint64_t)buf[1] << 48) |
         ((uint64_t)buf[2] << 40) | ((uint64_t)buf[3] << 32) |
         ((uint64_t)buf[4] << 24) | ((uint64_t)buf[5] << 16) |
         ((uint64_t)buf[6] << 8) | ((uint64_t)buf[7]);
}

uint16_t file_readBeUint16(FILE *fp) {
  uint8_t buf[2];
  if (fread(buf, 1, 2, fp) != 2) {
    return 0;
  }

  return (uint16_t)(((uint16_t)buf[0] << 8) | ((uint16_t)buf[1]));
}

uint8_t file_readBeUint8(FILE *fp) {
  uint8_t buf[1];
  if (fread(buf, 1, 1, fp) != 1) {
    return 0;
  }

  return buf[0];
}

uint_fast8_t file_dataFileExists(void) {
  FILE *file = fopen(DATAFILE, "r");
  if (file != NULL) {
    fclose(file);
    return 1;
  }
  return 0;
}

uint_fast8_t file_createDataFile(void) {
  char value[NAME_LENGTH] = {0};
  uint16_t id;

  printf("Enter initial admin id: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';
  id = (uint16_t)strtol(value, NULL, 10);

  printf("Enter initial admin name: ");
  fgets(value, NAME_LENGTH, stdin);
  value[strcspn(value, "\n")] = '\0';

  admin_create(id, value);
  return file_saveDataFile();
}

uint_fast8_t file_saveDataFile(void) {
  FILE *file = fopen(DATAFILE, "wb");
  if (file == NULL) {
    return 0;
  }

  fwrite("CS115_FB", 1, 8, file);
  file_writeBeUint8(file, 0);

  uint64_t adminOffset = 0x21u;
  uint64_t teamOffset = adminOffset + (uint64_t)session_enabledAdminCount *
                                          FILE_RECORD_SIZE_ADMIN;
  uint64_t managerOffset =
      teamOffset + (uint64_t)session_enabledTeamCount * FILE_RECORD_SIZE_TEAM;
  uint64_t playerOffset = managerOffset +
                          (uint64_t)session_enabledManagerCount *
                              FILE_RECORD_SIZE_MANAGER;

  file_writeBeUint64(file, teamOffset);
  file_writeBeUint64(file, managerOffset);
  file_writeBeUint64(file, playerOffset);

  fseek(file, (long)adminOffset, SEEK_SET);
  for (int i = 0; i < session_adminCount; ++i) {
    if (session_adminDynamicArray[i]->isActive) {
      file_writeAdmin(file, session_adminDynamicArray[i]);
    }
  }

  fseek(file, (long)teamOffset, SEEK_SET);
  for (int i = 0; i < session_teamCount; ++i) {
    if (session_teamDynamicArray[i]->isActive) {
      file_writeTeam(file, session_teamDynamicArray[i]);
    }
  }

  fseek(file, (long)managerOffset, SEEK_SET);
  for (int i = 0; i < session_managerCount; ++i) {
    if (session_managerDynamicArray[i]->isActive) {
      file_writeManager(file, session_managerDynamicArray[i]);
    }
  }

  fseek(file, (long)playerOffset, SEEK_SET);
  for (int i = 0; i < session_playerCount; ++i) {
    if (session_playerDynamicArray[i]->isActive) {
      file_writePlayer(file, session_playerDynamicArray[i]);
    }
  }

  fclose(file);
  return 1;
}

uint_fast8_t file_loadDataFile(void) {
  FILE *fp = fopen(DATAFILE, "rb");
  if (fp == NULL) {
    return 0;
  }

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

  uint8_t revision = file_readBeUint8(fp);
  (void)revision;

  uint64_t teamOffset = file_readBeUint64(fp);
  uint64_t managerOffset = file_readBeUint64(fp);
  uint64_t playerOffset = file_readBeUint64(fp);
  const uint64_t adminOffset = 0x21u;

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return 0;
  }

  long fileSize = ftell(fp);
  if (fileSize < 0) {
    fclose(fp);
    return 0;
  }

  if (teamOffset < adminOffset || teamOffset > (uint64_t)fileSize) {
    fclose(fp);
    return 0;
  }

  session_adminCount = (uint_fast8_t)((teamOffset - adminOffset) / FILE_RECORD_SIZE_ADMIN);
  session_teamCount = (uint_fast8_t)((managerOffset - teamOffset) / FILE_RECORD_SIZE_TEAM);
  session_managerCount =
      (uint_fast8_t)((playerOffset - managerOffset) / FILE_RECORD_SIZE_MANAGER);
  session_playerCount =
      (uint_fast8_t)((fileSize >= (long)playerOffset)
                         ? ((uint64_t)fileSize - playerOffset) /
                               FILE_RECORD_SIZE_PLAYER
                         : 0);

  session_enabledAdminCount = session_adminCount;
  session_enabledTeamCount = session_teamCount;
  session_enabledManagerCount = session_managerCount;
  session_enabledPlayerCount = session_playerCount;

  session_adminDynamicArray = NULL;
  session_teamDynamicArray = NULL;
  session_managerDynamicArray = NULL;
  session_playerDynamicArray = NULL;

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
      file_readAdmin(fp, session_adminDynamicArray[i]);
    }
  }

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
      file_readTeam(fp, session_teamDynamicArray[i]);
    }
  }

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
      file_readManager(fp, session_managerDynamicArray[i]);
    }
  }

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
      file_readPlayer(fp, session_playerDynamicArray[i]);
    }
  }

  fclose(fp);
  return 1;
}
