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

//// Functions

// File Management
uint_fast8_t file_dataFileExists(void);
uint_fast8_t file_createDataFile(void);
uint_fast8_t file_saveDataFile(void);
uint_fast8_t file_loadDataFile(void);

#endif
