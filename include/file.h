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

#include <stdint.h>
#include <stdio.h>

//// Functions

// Big Endian Write
void file_writeBeUint64(FILE *fp, uint64_t val);
void file_writeBeUint16(FILE *fp, uint16_t val);
void file_writeBeUint8(FILE *fp, uint8_t val);

// Big Endian Read
uint64_t file_readBeUint64(FILE *fp);
uint16_t file_readBeUint16(FILE *fp);
uint8_t file_readBeUint8(FILE *fp);

// File Management
uint_fast8_t file_dataFileExists(void);
uint_fast8_t file_createDataFile(void);
uint_fast8_t file_saveDataFile(void);

#endif
