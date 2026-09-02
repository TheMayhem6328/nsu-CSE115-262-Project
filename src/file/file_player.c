#include "file_player.h"
#include "file_common.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>

void file_writePlayer(FILE *fp, const FPlayer *player) {
  if (!player->isActive) {
    return;
  }

  file_writeBeUint16(fp, player->id);
  fwrite(player->name, 1, NAME_LENGTH, fp);
  file_writeBeUint8(fp, (uint8_t)player->isActive);
  file_writeBeUint8(fp, (uint8_t)player->position);
  file_writeBeUint8(fp, player->shirtNumber);
  file_writeBeUint8(fp, player->rating);
  file_writeBeUint8(fp, player->fitness);
  file_writeBeUint8(fp, (uint8_t)player->isInjured);
  file_writeBeUint16(fp, player->appearances);
  file_writeBeUint16(fp, player->goals);
  file_writeBeUint16(fp, player->assists);
}

void file_readPlayer(FILE *fp, FPlayer *player) {
  player->id = file_readBeUint16(fp);
  fread(player->name, 1, NAME_LENGTH, fp);
  player->isActive = (EBoolean)file_readBeUint8(fp);
  player->position = (EPlayerPosition)file_readBeUint8(fp);
  player->shirtNumber = file_readBeUint8(fp);
  player->rating = file_readBeUint8(fp);
  player->fitness = file_readBeUint8(fp);
  player->isInjured = (EBoolean)file_readBeUint8(fp);
  player->appearances = file_readBeUint16(fp);
  player->goals = file_readBeUint16(fp);
  player->assists = file_readBeUint16(fp);
  player->teamPtr = NULL;
}
