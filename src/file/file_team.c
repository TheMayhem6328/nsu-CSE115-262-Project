#include "file_team.h"
#include "file_common.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>

void file_writeTeam(FILE *fp, const FTeam *team) {
  if (!team->isActive) {
    return;
  }

  file_writeBeUint16(fp, team->id);
  fwrite(team->name, 1, NAME_LENGTH, fp);
  file_writeBeUint8(fp, (uint8_t)team->isActive);
  fwrite(team->city, 1, NAME_LENGTH, fp);
  fwrite(team->stadium, 1, NAME_LENGTH, fp);

  file_writeBeUint16(fp, team->matchesPlayed);
  file_writeBeUint16(fp, team->wins);
  file_writeBeUint16(fp, team->draws);
  file_writeBeUint16(fp, team->losses);
  file_writeBeUint16(fp, team->goalsFor);
  file_writeBeUint16(fp, team->goalsAgainst);
  file_writeBeUint16(fp, team->points);

  file_writeBeUint16(fp, team->managerID);
  file_writeBeUint8(fp, team->playerCount);
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    file_writeBeUint8(fp, team->playerIDs[i]);
  }
}

void file_readTeam(FILE *fp, FTeam *team) {
  team->id = file_readBeUint16(fp);
  fread(team->name, 1, NAME_LENGTH, fp);
  team->isActive = (EBoolean)file_readBeUint8(fp);
  fread(team->city, 1, NAME_LENGTH, fp);
  fread(team->stadium, 1, NAME_LENGTH, fp);

  team->matchesPlayed = file_readBeUint16(fp);
  team->wins = file_readBeUint16(fp);
  team->draws = file_readBeUint16(fp);
  team->losses = file_readBeUint16(fp);
  team->goalsFor = file_readBeUint16(fp);
  team->goalsAgainst = file_readBeUint16(fp);
  team->points = file_readBeUint16(fp);

  team->managerID = file_readBeUint16(fp);
  team->playerCount = file_readBeUint8(fp);
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team->playerIDs[i] = file_readBeUint8(fp);
  }

  team->manager = NULL;
  for (uint8_t i = 0; i < MAX_TEAM_PLAYERS; ++i) {
    team->playerPtrs[i] = NULL;
  }
}
