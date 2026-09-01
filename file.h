// file.h
// Zahiruzzman Chowdhury
//
// Utility functions for managing data file
// Ensuring big endianness for consistency
//
// Also, death to Code::Blocks

#ifndef M6328_FILES
#define M6328_FILES

#include "types.h" // IWYU pragma: keep
#include <stdint.h>
#include <stdio.h> // IWYU pragma: keep

// Structs

// Functions

// Big Endian Write

void write_uint64_be(FILE *f, uint64_t val);
void write_uint16_be(FILE *f, uint16_t val);
void write_uint8_be(FILE *f, uint8_t val);

// Big Endian Read

uint64_t read_uint64_be(FILE *f);
uint16_t read_uint16_be(FILE *f);
uint8_t read_uint8_be(FILE *f);

// Serialization


#endif
