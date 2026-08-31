// types.h
// Zahiruzzman Chowdhury
//
// Definition for data types like structs and all
//
// Also, death to Code::Blocks

#ifndef M6328_TYPES
#define M6328_TYPES

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define NAME_LENGTH 75
#define MAX_TEAM_PLAYERS 26

#include <stdint.h>

// Forward definitions of struct types
typedef struct admin FAdmin;
typedef struct team FTeam;
typedef struct manager FManager;
typedef struct player FPlayer;

// Enumerates
typedef enum bool { FALSE, TRUE } EBool;
typedef enum playerPosition {
  POSITION_GK,

  POSITION_RB,
  POSITION_LB,
  POSITION_CB,
  POSITION_RWB,
  POSITION_LWB,

  POSITION_CDM,
  POSITION_CM,
  POSITION_CAM,
  POSITION_RM,
  POSITION_LM,

  POSITION_RW,
  POSITION_LW,
  POSITION_ST,
  POSITION_CF,

  POSITION_COUNT,
  POSITION_INVALID = -1
} EPlayerPosition;

// String arrays
extern const char *positionNames[POSITION_COUNT];

// Data types
struct admin {
  // Basics
  uint16_t id;
  char name[NAME_LENGTH];
  EBool isActive;
};

struct team {
  // Basics
  uint16_t id;
  char name[NAME_LENGTH];
  EBool isActive;

  // Location metadata
  char city[NAME_LENGTH];
  char stadium[NAME_LENGTH];

  // Season stats
  uint16_t matchesPlayed;
  uint16_t wins;
  uint16_t draws;
  uint16_t losses;
  uint16_t goalsFor;
  uint16_t goalsAgainst;
  uint16_t points;

  // Team Information
  uint8_t playerCount;
  uint8_t playerIDs[MAX_TEAM_PLAYERS];

  // Runtime only
  FManager *manager;
  FPlayer *playerPtrs[MAX_TEAM_PLAYERS];
};

// Maintaining a circular reference to FTeam
// for faster runtime lookup
struct manager {
  // Basics
  uint16_t id;
  char name[NAME_LENGTH];
  EBool isActive;

  // Team Information
  uint16_t team_id;

  // Runtime only
  FTeam *teamPtr;
};

// Maintaining a circular reference to FTeam
// for faster runtime lookup
struct player {
  // Basics
  uint16_t id;
  char name[NAME_LENGTH];
  EBool isActive;

  // Field identifier
  EPlayerPosition position;
  int shirtNumber;

  // Personal metadata
  int rating;
  int fitness;
  EBool isInjured;

  // Season stats
  int appearances;
  int goals;
  int assists;

  // Runtime only
  FTeam *teamPtr;
};

#endif
