//Program for Player data base
#pragma once
#include <cstdlib>
#include <cstdio>
#include "species.hpp" 
#include "pokemon.hpp"
#include "type.hpp"
#include <ctime>
#define PokemonMax 6

typedef enum PokeballType
{
    P_POKEBALL,
    P_GREATBALL,
    P_ULTRABALL,
    P_MASTERBALL,
    P_SAFARIBALL
}PokeballType;

typedef struct Pokeball
{
    PokeballType type;
}Pokeball;

typedef struct Player
{
    char name[32];
    int pokeballCount;
    Pokemon pokemon[PokemonMax];
    Pokeball pokeball[32];
    int pokemonCount;
    int Poke_Dollar;


}Player;

/*
typedef struct Item
{
    Pokeball pokeball;
}Item;
*/


