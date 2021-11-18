//Program for each PKMN
#pragma once
#include <cstdio>
#include <cstdlib>
#include "moves.hpp"
#include "status.hpp"

typedef struct MoveSlot
{
    MoveId id;
    char name[32];
    Type type;
    int pp;
    int power;
    Category category;
    int accuracy;
    int PPBase;
} MoveSlot;

typedef struct Stage
{
    int attack;
    int defense;
    int special;
    int speed;
    int accuracy;
    int evasion;
}Stage;

typedef enum Owner
{
    WILD,
    PLAYER
} Owner;

typedef struct Pokemon
{
    int speciesId;
    char name[32];
    float currentHP;
    int level;
    Status status;
    Type type1;
    Type type2;
    int catchRate;
    int moveCount;
    MoveSlot moveSlots[4];
    int OriginalTrainerID;
    int ExpPoints;
    Owner owner;
    Stage stage;

    int healthEV;
    int attackEV;
    int defenseEV;
    int speedEV;
    int specialEV;

    int hpIV;
    int attackIV;
    int defenseIV;
    int specialIV;
    int speedIV;

    float MaxHP;
    int healthStat;
    int defenseStat;
    int attackStat;
    int speedStat;
    int specialStat;
    
} Pokemon;