// file.h
// Zahiruzzman Chowdhury
//
// Utility functions for managing data file
// Ensuring big endianness for consistency
//
// Also, death to Code::Blocks

#ifndef M6328_FILES
#define M6328_FILES

#define DATAFILE "DATA.CS115FB"

#include "types.h"
#include <stdint.h>
#include <stdio.h> // IWYU pragma: keep

// Structs

// Functions

// Big Endian Write

void file_writeBeUint64(FILE *f, uint64_t val);
void file_writeBeUint16(FILE *f, uint16_t val);
void file_writeBeUint8(FILE *f, uint8_t val);

// Big Endian Read

uint64_t file_readBeUint64(FILE *f);
uint16_t file_readBeUint16(FILE *f);
uint8_t file_readBeUint8(FILE *f);

// Serialization

// File

EBoolean file_dataFileExists(void);
uint8_t file_saveDataFile(void);

#endif
