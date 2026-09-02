#ifndef M6328_FILE_COMMON
#define M6328_FILE_COMMON

#define DATAFILE "DATA.CS115FB"

#include <stdint.h>
#include <stdio.h>

void file_writeBeUint64(FILE *fp, uint64_t val);
void file_writeBeUint16(FILE *fp, uint16_t val);
void file_writeBeUint8(FILE *fp, uint8_t val);

uint64_t file_readBeUint64(FILE *fp);
uint16_t file_readBeUint16(FILE *fp);
uint8_t file_readBeUint8(FILE *fp);

uint_fast8_t file_dataFileExists(void);
uint_fast8_t file_createDataFile(void);
uint_fast8_t file_saveDataFile(void);
uint_fast8_t file_loadDataFile(void);

#endif
