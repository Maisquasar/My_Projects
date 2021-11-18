//Program for Rules of game
#pragma once
#include <cstdlib>
#include <cstdio>
#include "../datas/species.hpp" //Experience Growth
#include "../datas/pokemon.hpp"
#include "../datas/type.hpp"
#include <ctime>
#include "../datas/player.hpp"
//Calcul
int ConvertToBin(int nbr);
int ConvertToDeci(int tab[]);

//Pokemon
void HealPokemons(Player *player);
int getExperienceYield(Pokemon pk);
int getAttackIV(Pokemon pk);
int getDefenseIV(Pokemon pk);
int getSpecialIV(Pokemon pk);
int getSpeedIV(Pokemon pk);
int getHpIV(Pokemon pk);
float getMaxHP(Pokemon pk);
Pokemon createPokemon(int speciesId, int level, Owner);
int getxpRequiredForLevel(Pokemon pk);
void evolve(Pokemon pk);
void checkLvlUp(Pokemon pk);
Player createPlayer();
float Accuracy(Move *move, Pokemon user, Pokemon target);
float getStageEvasion(Pokemon pk);
float getStageAccuracy(Pokemon pk);
float CriticalHit(Move *move, Pokemon pk, int criticalChanceBonus);
static float getEffectiveness(char c);
float getTypeEffectiveness(Type moveType, Type targetPrimaryType, Type targetSecondaryType);
float getSTAB(Type moveType, Type userPrimaryType, Type userSecondaryType);
int getMoveIdByDisponible(int DisponibleMoves[], Pokemon pk);
MoveSlot createMoveSlot(Move* move, Pokemon pk);
Move *getMoveByPk(Pokemon pk);
Pokemon defineMoves(Pokemon pk);
Pokemon createWildPkByRoad(int road);
int pokemonCatch(Pokeball pb, Pokemon wild);
void* catchPokemon(Player* player, Pokemon wild);