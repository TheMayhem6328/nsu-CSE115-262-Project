#include "file_admin.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>

void file_writeAdmin(FILE *fp, const FAdmin *admin) {
  if (admin->isActive) {
    fwrite(&admin->id, sizeof(admin->id), 1, fp);
    fwrite(admin->name, 1, NAME_LENGTH, fp);
    fwrite(&admin->isActive, sizeof(admin->isActive), 1, fp);
  }
}

void file_readAdmin(FILE *fp, FAdmin *user) {
  uint16_t id = 0;
  uint8_t isActive = 0;

  if (fread(&id, sizeof(id), 1, fp) != 1) {
    id = 0;
  }
  user->id = id;

  if (fread(user->name, 1, NAME_LENGTH, fp) != NAME_LENGTH) {
    user->name[0] = '\0';
  }

  if (fread(&isActive, sizeof(isActive), 1, fp) != 1) {
    isActive = 0;
  }
  user->isActive = (EBoolean)isActive;
}
