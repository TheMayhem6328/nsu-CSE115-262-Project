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

// Big Endian

void write_uint64_be(FILE *f, uint64_t val);
uint64_t read_uint64_be(FILE *f);

// Serialization
// TODO

#endif
