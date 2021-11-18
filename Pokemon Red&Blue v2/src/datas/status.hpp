//Program for int Status
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cassert>

typedef enum StatusID
{
   S_SLEEP,
   S_POISON,
   S_BURN,
   S_FREEZE,
   S_PARALYSIS,
   S_BADLY_POISONED,
   S_BOUND,
   S_CANT_ESCAPE,
   S_CONFUSION,
   S_CURSE,
   S_FLINCH,
   S_LEECH,
   S_TYPE_CHANGE,
   S_CHARGING,
   S_MINIMIZE,
   S_RECHARCHING,
   S_SEMI_INVULNERABLE,
   S_SUBSTITUT,
   S_THRASHING,
   S_TRANSFORMED
} StatusID;

typedef struct Status
{
   StatusID id;
   int TurnTODO;
   int TurnDID;
}Status;
