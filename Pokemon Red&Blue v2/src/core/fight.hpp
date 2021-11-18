//Program for Fights
#pragma once
#include <cstdio>
#include <cstdlib>
#include "../rules/rules.hpp"
#include "../datas/species.hpp"
#include <ctime>
void* handleAttack(Pokemon *attacker, MoveSlot moveSlot, Pokemon *defender);
void WildFight(Player* player, Pokemon wild);