// types.c
// Zahiruzzman Chowdhury
// 2513048043
// CSE115.17
//
// Definition for data types like structs and all
//
// Also, death to Code::Blocks

#include "types.h"

// String arrays
const char *const positionNames[POSITION_COUNT] = {
    [POSITION_GK] = "Goalkeeper",
    [POSITION_RB] = "Right-back",
    [POSITION_LB] = "Left-back",
    [POSITION_CB] = "Centre-back",
    [POSITION_RWB] = "Right wing-back",
    [POSITION_LWB] = "Left wing-back",
    [POSITION_CDM] = "Defensive midfielder",
    [POSITION_CM] = "Central midfielder",
    [POSITION_CAM] = "Attacking midfielder",
    [POSITION_RM] = "Right midfielder",
    [POSITION_LM] = "Left midfielder",
    [POSITION_RW] = "Right winger",
    [POSITION_LW] = "Left winger",
    [POSITION_ST] = "Striker",
    [POSITION_CF] = "Centre-forward"};