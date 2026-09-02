#include "file_admin.h"
#include "file_common.h"
#include "types.h"

#include <stdint.h>
#include <stdio.h>

void file_writeAdmin(FILE *fp, const FAdmin *admin) {
  if (admin->isActive) {
    file_writeBeUint16(fp, admin->id);
    fwrite(admin->name, 1, NAME_LENGTH, fp);
    file_writeBeUint8(fp, (uint8_t)admin->isActive);
  }
}

void file_readAdmin(FILE *fp, FAdmin *user) {
  user->id = file_readBeUint16(fp);

  if (fread(user->name, 1, NAME_LENGTH, fp) != NAME_LENGTH) {
    user->name[0] = '\0';
  }

  user->isActive = (EBoolean)file_readBeUint8(fp);
}
