// file.h
// Zahiruzzman Chowdhury
//
// Utility functions for managing data file
//
// Also, death to Code::Blocks

#include "file.h"

// Big Endian Write

void write_uint64_be(FILE *f, uint64_t val) {
  // Use bitwise operations to split
  // uint64_t to big endian bytes
  uint8_t buf[8];
  buf[0] = (uint8_t)((val >> 56) & 0xFF);
  buf[1] = (uint8_t)((val >> 48) & 0xFF);
  buf[2] = (uint8_t)((val >> 40) & 0xFF);
  buf[3] = (uint8_t)((val >> 32) & 0xFF);
  buf[4] = (uint8_t)((val >> 24) & 0xFF);
  buf[5] = (uint8_t)((val >> 16) & 0xFF);
  buf[6] = (uint8_t)((val >> 8) & 0xFF);
  buf[7] = (uint8_t)(val & 0xFF);

  // Write bytes to file
  fwrite(buf, 1, 8, f);
}

void write_uint16_be(FILE *f, uint16_t val) {
  // Use bitwise operations to split
  // uint64_t to big endian bytes
  uint8_t buf[2];
  buf[0] = (uint8_t)((val >> 8) & 0xFF);
  buf[1] = (uint8_t)(val & 0xFF);

  // Write bytes to file
  fwrite(buf, 1, 2, f);
}

void write_uint8_be(FILE *f, uint8_t val) {
  // Write bytes to file
  fwrite(&val, 1, 1, f);
}

// Big Endian Read

uint64_t read_uint64_be(FILE *f) {
  // Read bytes
  uint8_t buf[8];
  if (fread(buf, 1, 8, f) != 8) {
    // Fallback
    return 0;
  }

  // Use bitwise operations to join bytes
  // into one uint64_t
  return ((uint64_t)buf[0] << 56) | ((uint64_t)buf[1] << 48) |
         ((uint64_t)buf[2] << 40) | ((uint64_t)buf[3] << 32) |
         ((uint64_t)buf[4] << 24) | ((uint64_t)buf[5] << 16) |
         ((uint64_t)buf[6] << 8) | ((uint64_t)buf[7] << 0);
}

uint16_t read_uint16_be(FILE *f) {
  // Read bytes
  uint8_t buf[2];
  if (fread(buf, 1, 2, f) != 2) {
    // Fallback
    return 0;
  }

  // Use bitwise operations to join bytes
  // into one uint64_t
  return ((uint16_t)buf[0] << 8) | ((uint16_t)buf[1] << 0);
}

uint8_t read_uint8_be(FILE *f) {
  // Read bytes
  uint8_t buf[1];
  if (fread(buf, 1, 1, f) != 1) {
    // Fallback
    return 0;
  }

  // Use bitwise operations to join bytes
  // into one uint64_t
  return buf[0];
}
