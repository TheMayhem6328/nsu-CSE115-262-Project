/*
types.h 
Zahiruzzman Chowdhury

Keeping it compatible with C89
Since I do not trust any environment
outside mine

Also, death to Code::Blocks
*/

#ifndef CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef TYPES
#define TYPES

#define NAME_LENGTH 75
#define MAX_TEAM_PLAYERS 26

/* Forward definitions */
typedef struct admin FAdmin;
typedef struct team FTeam;
typedef struct manager FManager;
typedef struct player FPlayer;

/* Enumerates */
typedef enum active {
  INACTIVE,
  ACTIVE
} EActive;

/* Data types */
struct admin {
  int id;
  char name[NAME_LENGTH];
  EActive activeStatus;
};

struct team {
  int id;
  char name[NAME_LENGTH];
  EActive activeStatus;
  FManager *manager;
  FPlayer *players[MAX_TEAM_PLAYERS];
};

/*
Maintaining a circular reference to FTeam
for faster info lookup
*/
struct manager {
  int id;
  char name[NAME_LENGTH];
  EActive activeStatus;
  FTeam *team;
};

/*
Maintaining a circular reference to FTeam
for faster info lookup
*/
struct player {
  int id;
  char name[NAME_LENGTH];
  EActive activeStatus;
  FTeam *team;
};

#endif