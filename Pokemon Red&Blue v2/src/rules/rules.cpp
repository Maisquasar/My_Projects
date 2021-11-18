//Program for Rules of game
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <cassert>
#include "rules.hpp"
#include <raylib.h>
//Calcul
static int DisponibleMoves[10];

int ConvertToBin(int nbr)
{
    int tab[10], i;
    for (i = 0; nbr > 0; i++)
    {
        tab[i] = nbr % 2;
        nbr = nbr / 2;
    }
    if (tab[0] == 1)
        return 1;
    else
        return 0;
}

int ConvertToDeci(int tab[])
{
    int x = 0;
    if (tab[0] == 1)
        x += 1;
    if (tab[1] == 1)
        x += 2;
    if (tab[2] == 1)
        x += 4;
    if (tab[3] == 1)
        x += 8;
    return x;
}

//Pokemon Stats
void HealPokemon(Pokemon* pk)
{
    Species *sp = getSpeciesByIndex(pk->speciesId);
    pk->attackStat = sp->attackStat;
    pk->healthStat = sp->healthStat;
    pk->defenseStat = sp->defenseStat;
    pk->speedStat = sp->speedStat;
    pk->specialStat = sp->specialStat;
    pk->currentHP = getMaxHP(*pk);
}

void HealPokemons(Player *player)
{
    for (int i = 0; i <= player->pokemonCount; ++i)
    {
        HealPokemon(&player->pokemon[i]);
    }
    fgetc(stdin);
}

int getExperienceYield(Pokemon pk)
{
    Species *sp = getSpeciesByIndex(pk.speciesId);
    int s = 1;          //Nombre de pokemon intervenue dans le combat
    int a;              //Si pokemon sauvage a = 1 sinon a = 1.5
    int CombatType = 0; //Sauvage
    if (CombatType = 0)
        a = 1;
    else
        a = 1.5;
    int experienceYield = ((a * sp->ExperienceYield * pk.level) / (7 * s));
    return experienceYield;
}

int getAttackIV(Pokemon pk)
{
    return rand() % 16;
}
int getDefenseIV(Pokemon pk)
{
    return rand() % 16;
}
int getSpecialIV(Pokemon pk)
{
    return rand() % 16;
}
int getSpeedIV(Pokemon pk)
{
    return rand() % 16;
}

int getHpIV(Pokemon pk)
{
    int tab[15];
    tab[3] = ConvertToBin(pk.attackIV);
    tab[2] = ConvertToBin(pk.defenseIV);
    tab[1] = ConvertToBin(pk.speedIV);
    tab[0] = ConvertToBin(pk.specialIV);
    int hpIV = ConvertToDeci(tab);
    return hpIV;
}
float getMaxHP(Pokemon pk)
{
    Species *sp = getSpeciesByIndex(pk.speciesId);
    float hp = ((((sp->healthStat + (pk.hpIV)) * 2 + ((sqrt(pk.healthEV)) / 4)) * pk.level) / 100) + pk.level + 10;
    return hp;
}

Pokemon createPokemon(int speciesId, int level, Owner owner)
{
     Species *species = getSpeciesByIndex(speciesId);
    Pokemon result = {0};
    for (int i = 0; i < 32; ++i)
    {
        result.name[i] = species->name[i];
    }
    result.type1 = species->primaryType;
    result.type2 = species->secondaryType;
    result.speciesId = speciesId;
    result.level = level;
    result.owner = owner;
    srand(time(NULL));
    result.attackIV = getAttackIV(result);
    result.defenseIV = getDefenseIV(result);
    result.specialIV = getSpecialIV(result);
    result.speedIV = getSpecialIV(result);
    result.moveCount = 4;
    result.hpIV = getHpIV(result);
    result.currentHP = getMaxHP(result);
    result.MaxHP = getMaxHP(result);
    //Stats change
    result.attackStat = species->attackStat;
    result.healthStat = species->healthStat;
    result.defenseStat = species->defenseStat;
    result.speedStat = species->speedStat;
    result.specialStat = species->specialStat;

    result.stage.evasion = 0;
    result.stage.accuracy = 0;
    result.stage.special = 0;
    result.stage.speed = 0;
    result.stage.defense = 0;
    result.stage.attack = 0;

    result = defineMoves(result);
    return result;
}

int getxpRequiredForLevel(Pokemon pk) //work
{
    Species *sp = getSpeciesByIndex(pk.speciesId);
    int xp;
    if (sp->experienceGrowth == EG_FAST)
    {
        xp = (4 * pow(pk.level, 3)) / 5;
    }
    if (sp->experienceGrowth == EG_MEDIUM_SLOW)
    {
        xp = pow(pk.level, 3);
    }
    if (sp->experienceGrowth == EG_MEDIUM_FAST)
    {
        xp = ((6 * (pow(pk.level, 3))) / 5) - (15 * pow(pk.level, 2)) + (100 * pk.level) - 140;
    }
    if (sp->experienceGrowth == EG_SLOW)
    {
        xp = (5 * (pow(pk.level, 3))) / 4;
    }
    return xp;
}

//Checks
void evolve(Pokemon pk) //à verifier
{
    Species *sp = getSpeciesByIndex(pk.speciesId + 1); //Evolution
    Species *prev = getSpeciesByIndex(pk.speciesId);
    printf("What ? %s is evolving !\n", prev->name);
    fgetc(stdin);
    printf("%s evolved into %s\n", prev->name, sp->name);
    fgetc(stdin);
    pk.speciesId = pk.speciesId + 1;
}

void checkLvlUp(Pokemon pk) //Work
{
    int xpRequired = getxpRequiredForLevel(pk);
    Species *sp = getSpeciesByIndex(pk.speciesId);
    while (xpRequired <= pk.ExpPoints)
    {
        xpRequired = getxpRequiredForLevel(pk);
        pk.level = pk.level + 1;
        pk.ExpPoints = pk.ExpPoints - xpRequired;
        xpRequired = getxpRequiredForLevel(pk);
        printf("%s grew to lvl %d [%d/%d]!\n", sp->name, pk.level, pk.ExpPoints, xpRequired);
        //=========Evolution=================
        switch (pk.speciesId)
        {
        //Level 7
        case 9:  //Caterpie -> Metapod
        case 12: //Weedle -> Kakuna
            if (pk.level == 7)
                evolve(pk);
            break;
        //Level 10
        case 10: //Metapod -> Butterfree
        case 13: //Kakuna -> Beedrill
            if (pk.level == 10)
                evolve(pk);
            break;
        //Level 16
        case 0:  //Bulbasaur -> Ivysaure
        case 3:  //Charmander -> Charmeleon
        case 6:  //Squirtle -> Wartortle
        case 28: //Nidoran (f) -> Nidorina
        case 31: //Nidoran (m) -> Nidorino
        case 62: //Abra -> Kadabra
            if (pk.level == 16)
                evolve(pk);
            break;
        //Level 18
        case 15: //Pidgey -> Pidgeotto
            if (pk.level == 18)
                evolve(pk);
            break;
        //Level 20
        case 18:  //Rattata -> Raticate
        case 20:  //Spearow -> Fearow
        case 128: //Magikarp -> Gyarados
            if (pk.level == 20)
                evolve(pk);
            break;
        //Level 21
        case 42: //Oddish -> Gloom
        case 68: //Bellsprout -> Weepinbell
            if (pk.level == 21)
                evolve(pk);
            break;
        //Level 22
        case 22: //Ekans -> Arbok
        case 26: //Sandshrew -> Sandslash
        case 40: //Zubat -> Golbat
            if (pk.level == 22)
                evolve(pk);
            break;
        //Level 24
        case 45: //Paras -> Parasect
            if (pk.level == 24)
                evolve(pk);
            break;
        //Level 25
        case 59: //Poliwag -> Poliwhirl
        case 73: //Geodude -> Graveler
        case 91: //Gastly -> Haunter
            if (pk.level == 25)
                evolve(pk);
            break;
        //Level 26
        case 49: //Diglett -> Dugtrio
        case 95: //Drowzee -> Hypno
            if (pk.level == 26)
                evolve(pk);
            break;
        //Level 28
        case 51:  //Meowth -> Persian
        case 55:  //Mankey -> Primeape
        case 65:  //Machop -> Machoke
        case 97:  //Krabby -> Kingler
        case 103: //Cubone -> Marowak
            if (pk.level == 28)
                evolve(pk);
            break;
        //Level 30
        case 71:  //Tentacool -> Tentacruel
        case 80:  //Magnemite -> Magneton
        case 99:  //Voltorb -> Electrode
        case 146: //Dratini -> Dragonair
            if (pk.level == 30)
                evolve(pk);
            break;
        //Level 31
        case 47: //Venonat -> Venomoth
        case 83: //Doduo -> Dodrio
            if (pk.level == 31)
                evolve(pk);
            break;
        //Level 32
        case 1:   //Ivysaure -> Venusaur
        case 115: //Horsea -> Seadra
            if (pk.level == 32)
                evolve(pk);
            break;
        //Level 33
        case 117:
            if (pk.level == 33)
                evolve(pk);
            break;
        //Level 35
        case 108: //Koffing -> Weezing
            if (pk.level == 35)
                evolve(pk);
            break;
        //Level 36
        case 4:  //Charmeleon -> Charizard
        case 7:  //Wartortle -> Blastoise
        case 16: //Pidgeotto -> Pidgeot
            if (pk.level == 36)
                evolve(pk);
            break;
        //Level 37
        case 78: //Slowpoke -> Slowbro
            if (pk.level == 37)
                evolve(pk);
        //Level 40
        case 76:  //Ponyta -> Rapidash
        case 137: //Omanyte -> Omastar
        case 139: //Kabuto -> Kabutops
            if (pk.level == 40)
                evolve(pk);
            break;
        //Level 42
        case 110:
            if (pk.level == 42)
                evolve(pk);
            break;
        case 147: //Dragonair -> Dragonite
            if (pk.level == 55)
                evolve(pk);
            break;
        default:
            break;
        }
    }
}

Player createPlayer()
{
    char name[32] = "Red";
    Player player = {0};
    for (int i = 0; i < 32; ++i)
    {
        player.name[i] = name[i];
    }

    for (int i = 0; i != 10; ++i)
    {
        player.pokeball[i].type = P_POKEBALL;
        player.pokeballCount += 1;
    }
    //printf("Choose your starter :\n 1. Bulbasaure\n 2. Charmander\n 3. Squirtle\n");
    int choice = 1;
    player.pokemonCount = 1;
    //scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        player.pokemon[0] = createPokemon(0, 5, PLAYER);
        break;
    case 2:
        player.pokemon[0] = createPokemon(3, 5, PLAYER);
        break;
    case 3:
        player.pokemon[0] = createPokemon(6, 5, PLAYER);
        break;
    default:
        printf("Invalid number\n");
        break;
    }
    return player;
}

float CriticalHit(Move *move, Pokemon pk, int criticalChanceBonus)
{
    int T = (pk.speedStat / 2);
    T = T * criticalChanceBonus;
    float criticalhit;
    int criticalChance = GetRandomValue(1,256);
    if (criticalChance <= T)
    {
        criticalhit = (2 * pk.level + 5);
        criticalhit = criticalhit / (pk.level + 5);
        return criticalhit;
    }
    else
    {
        return criticalhit = 1;
    }
}

float Accuracy(Move *move, Pokemon user, Pokemon target)
{
    float Accuracy = move->accuracy * getStageAccuracy(user) * getStageEvasion(target);
    return Accuracy;
}

float getStageEvasion(Pokemon pk)
{
    float evasion;
    switch (pk.stage.evasion)
    {
    case -6:
        evasion = 25 / 100;
        break;
    case -5:
        evasion = 28 / 100;
        break;
    case -4:
        evasion = 33 / 100;
        break;
    case -3:
        evasion = 40 / 100;
        break;
    case -2:
        evasion = 50 / 100;
        break;
    case -1:
        evasion = 66 / 100;
        break;
    case 0:
        evasion = 100 / 100;
        break;
    case 1:
        evasion = 150 / 100;
        break;
    case 2:
        evasion = 200 / 100;
        break;
    case 3:
        evasion = 250 / 100;
        break;
    case 4:
        evasion = 300 / 100;
        break;
    case 5:
        evasion = 350 / 100;
        break;
    case 6:
        evasion = 400 / 100;
        break;
    default:
        break;
    }
    return evasion;
}

float getStageAccuracy(Pokemon pk)
{
    float accuracy;
    switch (pk.stage.accuracy)
    {
    case 6:
        accuracy = 25 / 100;
        break;
    case 5:
        accuracy = 28 / 100;
        break;
    case 4:
        accuracy = 33 / 100;
        break;
    case 3:
        accuracy = 40 / 100;
        break;
    case 2:
        accuracy = 50 / 100;
        break;
    case 1:
        accuracy = 66 / 100;
        break;
    case 0:
        accuracy = 100 / 100;
        break;
    case -1:
        accuracy = 150 / 100;
        break;
    case -2:
        accuracy = 200 / 100;
        break;
    case -3:
        accuracy = 250 / 100;
        break;
    case -4:
        accuracy = 300 / 100;
        break;
    case -5:
        accuracy = 350 / 100;
        break;
    case -6:
        accuracy = 400 / 100;
        break;
    default:
        break;
    }
    return accuracy;
}

static float getEffectiveness(char c)
{
    switch (c)
    {
    case 'n':

        return 0.0f; // 'n' = No effect (0%)
    case 'b':

        return 0.5f; // 'b' = Not very effective (50%)
    case 's':

        return 2.0f; // 's' = Super-effective (200%)
    default:
        return 1.f;
    }
}

float getTypeEffectiveness(Type moveType, Type targetPrimaryType, Type targetSecondaryType)
{
    char efficacity1, efficacity2;
    float effectivness;
    assert(moveType > T_NOT_SET && moveType <= T_DRAGON);
    assert(targetPrimaryType >= T_NOT_SET && targetPrimaryType <= T_DRAGON);
    assert(targetSecondaryType >= T_NOT_SET && targetSecondaryType <= T_DRAGON);
    const char effectivenessMatrix[][16] = {
        "            bn ",
        " bb ss     sb b",
        " sb b   s   s b",
        "  sbb   ns    b",
        " bs b  bsb bs b",
        "  b sb  ss    s",
        "s    s b bbbsn ",
        "    s  bb  sbb ",
        " s sb  s n bs  ",
        "   bs s    sb  ",
        "      ss  b    ",
        " b  s bs bs  b ",
        " s   sb bs s   ",
        "n         n  s ",
        "              s"};
    if (targetSecondaryType == T_NOT_SET)
    {
        efficacity1 = effectivenessMatrix[moveType - 1][targetPrimaryType - 1];
        effectivness = getEffectiveness(efficacity1);
    }
    else
    {
        efficacity1 = effectivenessMatrix[moveType - 1][targetPrimaryType - 1];
        efficacity2 = effectivenessMatrix[moveType - 1][targetSecondaryType - 1];
        effectivness = getEffectiveness(efficacity1) * getEffectiveness(efficacity2);
    }
    int x = effectivness * 10;
    system("clear");
    switch (x)
    {
    case 0:
        // printf(BLK "It's not effective\n" reset);
        // fgetc(stdin);
        break;
    case 5:
        // printf(BBLK "It's not very effective\n" reset);
        // fgetc(stdin);
        break;
    case 20:
        // printf(BRED "It's super effective\n" reset);
        // fgetc(stdin);
        break;
    default:
        break;
    }
    return effectivness;
}
float getSTAB(Type moveType, Type userPrimaryType, Type userSecondaryType)
{
    if ((moveType == userPrimaryType) || (moveType == userSecondaryType))
    {
        return 1.5f; // STAB (150%)
    }
    else
    {
        return 1.0f;
    }
}

int getMoveIdByDisponible(Pokemon pk)
{
    /*
    for (int i = 0; i < 10; ++i) //Print all moves id
    {
        printf(BRED"DisponibleMoves[%d] = %d\n"reset, i, DisponibleMoves[i]);
    }
    */
    int Length = (sizeof(DisponibleMoves) / sizeof(int) + 1);
    //printf("Length : %d\n", Length);
    int moveId = (rand() % Length);
    for (int i = 0; i < 50; i++)
    {
        if (DisponibleMoves[moveId] != MT_UNDEFINE)
            break;
        moveId = (rand() % Length);
    }
    //printf("Moveid : %d\n", moveId);
    moveId = DisponibleMoves[moveId];
    //printf(BBLU "moveId : %d \n" reset, moveId);
    return moveId;
}

MoveSlot createMoveSlot(Move *move, Pokemon pk)
{
    MoveSlot result;
    result.id = move->id;
    for (int i = 0; i != 50; i++)
    {
        result.name[i] = move->name[i];
    }
    result.type = move->type;
    result.pp = move->pp;
    result.power = move->power;
    result.category = move->category;
    result.accuracy = move->accuracy;
    result.PPBase = move->pp;
    return result;
}

//gcc -g tests/test_Pokemon_stats.c src/rules.c src/species.c src/moves.c src/fight.c -lm && ./a.out

Move *getMoveByPk(Pokemon pk)
{
    Move *move = {0};
    //printf("speciesID: %d\n", pk.speciesId);
    for (int i = 0; i < 10; i++)
        DisponibleMoves[i] = MT_UNDEFINE;
    switch (pk.speciesId)
    {
    case 0: //Bulbasaur
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 7)
            DisponibleMoves[2] = MT_LEECH_SEED;
        if (pk.level >= 13)
            DisponibleMoves[3] = MT_VINE_WHIP;
        if (pk.level >= 20)
            DisponibleMoves[4] = MT_POISON_POWDER;
        if (pk.level >= 27)
            DisponibleMoves[5] = MT_RAZOR_LEAF;
        if (pk.level >= 34)
            DisponibleMoves[6] = MT_GROWTH;
        if (pk.level >= 41)
            DisponibleMoves[8] = MT_SLEEP_POWDER;
        if (pk.level >= 48)
            DisponibleMoves[9] = MT_SOLAR_BEAM;
        break;
    case 1: //Ivysaur
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_LEECH_SEED;
        if (pk.level >= 13)
            DisponibleMoves[3] = MT_VINE_WHIP;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_POISON_POWDER;
        if (pk.level >= 30)
            DisponibleMoves[5] = MT_RAZOR_LEAF;
        if (pk.level >= 38)
            DisponibleMoves[6] = MT_GROWTH;
        if (pk.level >= 46)
            DisponibleMoves[8] = MT_SLEEP_POWDER;
        if (pk.level >= 54)
            DisponibleMoves[9] = MT_SOLAR_BEAM;
        break;
    case 2: //Venusaur
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_LEECH_SEED;
        DisponibleMoves[3] = MT_VINE_WHIP;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_POISON_POWDER;
        if (pk.level >= 30)
            DisponibleMoves[5] = MT_RAZOR_LEAF;
        if (pk.level >= 43)
            DisponibleMoves[6] = MT_GROWTH;
        if (pk.level >= 55)
            DisponibleMoves[8] = MT_SLEEP_POWDER;
        if (pk.level >= 65)
            DisponibleMoves[9] = MT_SOLAR_BEAM;
        break;
    case 3: //Charmander
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 9)
            DisponibleMoves[2] = MT_EMBER;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level >= 30)
            DisponibleMoves[5] = MT_SLASH;
        if (pk.level >= 38)
            DisponibleMoves[6] = MT_FLAMETHROWER;
        if (pk.level >= 46)
            DisponibleMoves[8] = MT_FIRE_SPIN;
        break;
    case 4: //Charmeleon
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_EMBER;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level >= 33)
            DisponibleMoves[5] = MT_SLASH;
        if (pk.level >= 42)
            DisponibleMoves[6] = MT_FLAMETHROWER;
        if (pk.level >= 56)
            DisponibleMoves[8] = MT_FIRE_SPIN;
        break;
    case 5: //Charizard
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_EMBER;
        DisponibleMoves[3] = MT_LEER;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level >= 36)
            DisponibleMoves[5] = MT_SLASH;
        if (pk.level >= 46)
            DisponibleMoves[6] = MT_FLAMETHROWER;
        if (pk.level >= 55)
            DisponibleMoves[8] = MT_FIRE_SPIN;
        break;
    case 6: //Squirle
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level >= 8)
            DisponibleMoves[2] = MT_BUBBLE;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_BITE;
        if (pk.level >= 28)
            DisponibleMoves[5] = MT_WITHDRAW;
        if (pk.level >= 35)
            DisponibleMoves[6] = MT_SKULL_BASH;
        if (pk.level >= 42)
            DisponibleMoves[8] = MT_HYDRO_PUMP;
        break;
    case 7: //Wartotle
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_BUBBLE;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_BITE;
        if (pk.level >= 31)
            DisponibleMoves[5] = MT_WITHDRAW;
        if (pk.level >= 39)
            DisponibleMoves[6] = MT_SKULL_BASH;
        if (pk.level >= 47)
            DisponibleMoves[8] = MT_HYDRO_PUMP;
        break;
    case 8: //Blastoise
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_BUBBLE;
        DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_BITE;
        if (pk.level >= 31)
            DisponibleMoves[5] = MT_WITHDRAW;
        if (pk.level >= 42)
            DisponibleMoves[6] = MT_SKULL_BASH;
        if (pk.level >= 52)
            DisponibleMoves[7] = MT_HYDRO_PUMP;
        break;
    case 9: //Caterpie
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_STRING_SHOT;
        break;
    case 10: //Metapod
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_STRING_SHOT;
        DisponibleMoves[2] = MT_HARDEN;
        break;
    case 11: //Butterfree
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_HARDEN;
        DisponibleMoves[3] = MT_CONFUSION;
        if (pk.level >= 15)
            DisponibleMoves[4] = MT_POISON_POWDER;
        if (pk.level >= 16)
            DisponibleMoves[5] = MT_STUN_SPORE;
        if (pk.level >= 17)
            DisponibleMoves[6] = MT_SLEEP_POWDER;
        if (pk.level >= 24)
            DisponibleMoves[7] = MT_SUPERSONIC;
        if (pk.level >= 26)
            DisponibleMoves[8] = MT_WHIRLWIND;
        if (pk.level >= 32)
            DisponibleMoves[9] = MT_PSYBEAM;
        break;
    case 12: //Weedle
        DisponibleMoves[0] = MT_POISON_STING;
        DisponibleMoves[1] = MT_STRING_SHOT;
        break;
    case 13: //Kakuna
        DisponibleMoves[0] = MT_POISON_STING;
        DisponibleMoves[1] = MT_STRING_SHOT;
        DisponibleMoves[2] = MT_HARDEN;
        break;
    case 14: //Beedrill
        DisponibleMoves[0] = MT_POISON_STING;
        DisponibleMoves[1] = MT_STRING_SHOT;
        DisponibleMoves[2] = MT_HARDEN;
        DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level >= 16)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level >= 20)
            DisponibleMoves[5] = MT_TWINEEDLE;
        if (pk.level >= 25)
            DisponibleMoves[6] = MT_RAGE;
        if (pk.level >= 30)
            DisponibleMoves[7] = MT_PIN_MISSILE;
        if (pk.level >= 35)
            DisponibleMoves[8] = MT_AGILITY;
        break;
    case 15: //Pidgey
        DisponibleMoves[0] = MT_GUST;
        if (pk.level >= 5)
            DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level >= 9)
            DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_WHIRLWIND;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_WING_ATTACK;
        if (pk.level >= 30)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level >= 38)
            DisponibleMoves[6] = MT_MIRROR_MOVE;
        break;
    case 16: //Pidgeotto
        DisponibleMoves[0] = MT_GUST;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level >= 12)
            DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_WHIRLWIND;
        if (pk.level >= 31)
            DisponibleMoves[4] = MT_WING_ATTACK;
        if (pk.level >= 40)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level >= 49)
            DisponibleMoves[6] = MT_MIRROR_MOVE;
        break;
    case 17: //Pidgeot
        DisponibleMoves[0] = MT_GUST;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_WHIRLWIND;
        if (pk.level >= 31)
            DisponibleMoves[4] = MT_WING_ATTACK;
        if (pk.level >= 44)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level >= 54)
            DisponibleMoves[6] = MT_MIRROR_MOVE;
        break;
    case 18: //Rattata
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level >= 7)
            DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 14)
            DisponibleMoves[3] = MT_HYPER_FANG;
        if (pk.level >= 23)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level >= 34)
            DisponibleMoves[5] = MT_SUPER_FANG;
        break;
    case 19: //Raticate
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 14)
            DisponibleMoves[3] = MT_HYPER_FANG;
        if (pk.level >= 27)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level >= 41)
            DisponibleMoves[5] = MT_SUPER_FANG;
        break;
    case 20: //Spearow
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 9)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level >= 22)
            DisponibleMoves[4] = MT_MIRROR_MOVE;
        if (pk.level >= 29)
            DisponibleMoves[5] = MT_DRILL_PECK;
        if (pk.level >= 36)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 21: //Fearow
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_LEER;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level >= 25)
            DisponibleMoves[4] = MT_MIRROR_MOVE;
        if (pk.level >= 34)
            DisponibleMoves[5] = MT_DRILL_PECK;
        if (pk.level >= 43)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 22: //Ekans
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_LEER;
        if (pk.level >= 10)
            DisponibleMoves[2] = MT_POISON_STING;
        if (pk.level >= 17)
            DisponibleMoves[3] = MT_BITE;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_GLARE;
        if (pk.level >= 31)
            DisponibleMoves[5] = MT_SCREECH;
        if (pk.level >= 38)
            DisponibleMoves[6] = MT_ACID;
        break;
    case 23: //Arbok
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_POISON_STING;
        if (pk.level >= 17)
            DisponibleMoves[3] = MT_BITE;
        if (pk.level >= 27)
            DisponibleMoves[4] = MT_GLARE;
        if (pk.level >= 36)
            DisponibleMoves[5] = MT_SCREECH;
        if (pk.level >= 47)
            DisponibleMoves[6] = MT_ACID;
        break;
    case 24: //Pikachu
        DisponibleMoves[0] = MT_THUNDER_SHOCK;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 9)
            DisponibleMoves[2] = MT_THUNDER_WAVE;
        if (pk.level >= 16)
            DisponibleMoves[3] = MT_QUICK_ATTACK;
        if (pk.level >= 33)
            DisponibleMoves[4] = MT_AGILITY;
        if (pk.level >= 43)
            DisponibleMoves[5] = MT_THUNDER;
        if (pk.level >= 26)
            DisponibleMoves[6] = MT_SWIFT;
        break;
    case 25: //Raichu
        DisponibleMoves[0] = MT_THUNDER_SHOCK;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_THUNDER_WAVE;
        DisponibleMoves[3] = MT_QUICK_ATTACK;
        DisponibleMoves[4] = MT_AGILITY;
        DisponibleMoves[5] = MT_THUNDER;
        DisponibleMoves[6] = MT_SWIFT;
        DisponibleMoves[7] = MT_SURF;
        break;
    case 26: //Sandshrew
        DisponibleMoves[0] = MT_SCRATCH;
        if (pk.level >= 10)
            DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level >= 17)
            DisponibleMoves[2] = MT_SLASH;
        if (pk.level >= 24)
            DisponibleMoves[3] = MT_POISON_STING;
        if (pk.level >= 31)
            DisponibleMoves[4] = MT_SWIFT;
        if (pk.level >= 38)
            DisponibleMoves[5] = MT_FURY_SWIPES;
        break;
    case 27: //Sandslash
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level >= 17)
            DisponibleMoves[2] = MT_SLASH;
        if (pk.level >= 27)
            DisponibleMoves[3] = MT_POISON_STING;
        if (pk.level >= 36)
            DisponibleMoves[4] = MT_SWIFT;
        if (pk.level >= 47)
            DisponibleMoves[5] = MT_FURY_SWIPES;
        break;
    case 28: //Nidoran (f)
        DisponibleMoves[0] = MT_GROWL;
        DisponibleMoves[1] = MT_TACKLE;
        if (pk.level >= 8)
            DisponibleMoves[2] = MT_SCRATCH;
        if (pk.level >= 43)
            DisponibleMoves[3] = MT_DOUBLE_KICK;
        if (pk.level >= 14)
            DisponibleMoves[4] = MT_POISON_STING;
        if (pk.level >= 21)
            DisponibleMoves[5] = MT_TAIL_WHIP;
        if (pk.level >= 29)
            DisponibleMoves[6] = MT_BITE;
        if (pk.level >= 36)
            DisponibleMoves[7] = MT_FURY_SWIPES;
        break;
    case 29: //Nidorina
        DisponibleMoves[0] = MT_GROWL;
        DisponibleMoves[1] = MT_TACKLE;
        DisponibleMoves[2] = MT_SCRATCH;
        if (pk.level >= 50)
            DisponibleMoves[3] = MT_DOUBLE_KICK;
        if (pk.level >= 14)
            DisponibleMoves[4] = MT_POISON_STING;
        if (pk.level >= 23)
            DisponibleMoves[5] = MT_TAIL_WHIP;
        if (pk.level >= 32)
            DisponibleMoves[6] = MT_BITE;
        if (pk.level >= 41)
            DisponibleMoves[7] = MT_FURY_SWIPES;
        break;
    case 30: //Nidoqueen
        DisponibleMoves[0] = MT_TAIL_WHIP;
        DisponibleMoves[1] = MT_TACKLE;
        DisponibleMoves[2] = MT_SCRATCH;
        DisponibleMoves[3] = MT_BODY_SLAM;
        DisponibleMoves[4] = MT_POISON_STING;
        DisponibleMoves[5] = MT_BITE;
        DisponibleMoves[6] = MT_DOUBLE_KICK;
        DisponibleMoves[7] = MT_FURY_SWIPES;
        DisponibleMoves[8] = MT_GROWL;
        DisponibleMoves[9] = MT_POISON_STING;
        break;
    case 31: //Nidoran (m)
        DisponibleMoves[0] = MT_LEER;
        DisponibleMoves[1] = MT_TACKLE;
        if (pk.level >= 8)
            DisponibleMoves[2] = MT_HORN_ATTACK;
        if (pk.level >= 43)
            DisponibleMoves[3] = MT_DOUBLE_KICK;
        if (pk.level >= 14)
            DisponibleMoves[4] = MT_POISON_STING;
        if (pk.level >= 21)
            DisponibleMoves[5] = MT_FOCUS_ENERGY;
        if (pk.level >= 29)
            DisponibleMoves[6] = MT_FURY_ATTACK;
        if (pk.level >= 36)
            DisponibleMoves[7] = MT_HORN_DRILL;
        break;
    case 32: //Nidorino
        DisponibleMoves[0] = MT_GROWL;
        DisponibleMoves[1] = MT_TACKLE;
        DisponibleMoves[2] = MT_HORN_ATTACK;
        if (pk.level >= 50)
            DisponibleMoves[3] = MT_DOUBLE_KICK;
        if (pk.level >= 14)
            DisponibleMoves[4] = MT_POISON_STING;
        if (pk.level >= 23)
            DisponibleMoves[5] = MT_FOCUS_ENERGY;
        if (pk.level >= 32)
            DisponibleMoves[6] = MT_FURY_ATTACK;
        if (pk.level >= 41)
            DisponibleMoves[7] = MT_HORN_DRILL;
        break;
    case 33: //Nidoking
        DisponibleMoves[0] = MT_HORN_ATTACK;
        DisponibleMoves[1] = MT_TACKLE;
        DisponibleMoves[2] = MT_POISON_STING;
        DisponibleMoves[3] = MT_THRASH;
        DisponibleMoves[4] = MT_DOUBLE_KICK;
        DisponibleMoves[5] = MT_FOCUS_ENERGY;
        DisponibleMoves[6] = MT_FURY_ATTACK;
        DisponibleMoves[7] = MT_LEER;
        break;
    case 34: //Clefairy
        DisponibleMoves[0] = MT_POUND;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 13)
            DisponibleMoves[2] = MT_SING;
        if (pk.level >= 18)
            DisponibleMoves[3] = MT_DOUBLE_SLAP;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_MINIMIZE;
        if (pk.level >= 31)
            DisponibleMoves[5] = MT_METRONOME;
        if (pk.level >= 39)
            DisponibleMoves[6] = MT_DEFENSE_CURL;
        if (pk.level >= 48)
            DisponibleMoves[7] = MT_LIGHT_SCREEN;
        break;
    case 35: //Clefable
        DisponibleMoves[0] = MT_SING;
        DisponibleMoves[1] = MT_DOUBLE_SLAP;
        DisponibleMoves[2] = MT_MINIMIZE;
        DisponibleMoves[3] = MT_METRONOME;
        DisponibleMoves[4] = MT_GROWL;
        DisponibleMoves[5] = MT_DEFENSE_CURL;
        DisponibleMoves[6] = MT_LIGHT_SCREEN;
        DisponibleMoves[7] = MT_POUND;
        break;
    case 36: //Vulpix
        DisponibleMoves[0] = MT_EMBER;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level >= 16)
            DisponibleMoves[2] = MT_QUICK_ATTACK;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_ROAR;
        if (pk.level >= 28)
            DisponibleMoves[4] = MT_CONFUSE_RAY;
        if (pk.level >= 35)
            DisponibleMoves[5] = MT_FLAMETHROWER;
        if (pk.level >= 42)
            DisponibleMoves[6] = MT_FIRE_SPIN;
        break;
    case 37: //Ninetales
        DisponibleMoves[0] = MT_EMBER;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        DisponibleMoves[3] = MT_ROAR;
        DisponibleMoves[4] = MT_CONFUSE_RAY;
        DisponibleMoves[5] = MT_FLAMETHROWER;
        DisponibleMoves[6] = MT_FIRE_SPIN;
        break;
    case 38: //Jigglypuff
        DisponibleMoves[0] = MT_SING;
        if (pk.level >= 9)
            DisponibleMoves[1] = MT_POUND;
        if (pk.level >= 14)
            DisponibleMoves[2] = MT_DISABLE;
        if (pk.level >= 19)
            DisponibleMoves[3] = MT_DEFENSE_CURL;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_DOUBLE_SLAP;
        if (pk.level >= 29)
            DisponibleMoves[5] = MT_REST;
        if (pk.level >= 34)
            DisponibleMoves[6] = MT_BODY_SLAM;
        if (pk.level >= 39)
            DisponibleMoves[7] = MT_DOUBLE_EDGE;
        break;
    case 39: //Wigglytuff
        DisponibleMoves[0] = MT_SING;
        DisponibleMoves[1] = MT_DISABLE;
        DisponibleMoves[2] = MT_DEFENSE_CURL;
        DisponibleMoves[3] = MT_DOUBLE_SLAP;
        DisponibleMoves[4] = MT_POUND;
        break;
    case 40: //Zubat
        DisponibleMoves[0] = MT_LEECH_LIFE;
        if (pk.level >= 10)
            DisponibleMoves[1] = MT_SUPERSONIC;
        if (pk.level >= 15)
            DisponibleMoves[2] = MT_BITE;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_CONFUSE_RAY;
        if (pk.level >= 28)
            DisponibleMoves[4] = MT_WING_ATTACK;
        if (pk.level >= 36)
            DisponibleMoves[5] = MT_HAZE;
        break;
    case 41: //Golbat
        DisponibleMoves[0] = MT_LEECH_LIFE;
        DisponibleMoves[1] = MT_BITE;
        if (pk.level >= 10)
            DisponibleMoves[2] = MT_SUPERSONIC;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_CONFUSE_RAY;
        if (pk.level >= 32)
            DisponibleMoves[4] = MT_WING_ATTACK;
        if (pk.level >= 43)
            DisponibleMoves[5] = MT_HAZE;
        break;
    case 42: //Oddish
        DisponibleMoves[0] = MT_ABSORB;
        if (pk.level >= 15)
            DisponibleMoves[1] = MT_POISON_POWDER;
        if (pk.level >= 17)
            DisponibleMoves[2] = MT_STUN_SPORE;
        if (pk.level >= 19)
            DisponibleMoves[3] = MT_SLEEP_POWDER;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_ACID;
        if (pk.level >= 33)
            DisponibleMoves[5] = MT_PETAL_DANCE;
        if (pk.level >= 46)
            DisponibleMoves[6] = MT_SOLAR_BEAM;
        break;
    case 43: //Gloom
        DisponibleMoves[0] = MT_ABSORB;
        DisponibleMoves[1] = MT_POISON_POWDER;
        DisponibleMoves[2] = MT_STUN_SPORE;
        if (pk.level >= 19)
            DisponibleMoves[3] = MT_SLEEP_POWDER;
        if (pk.level >= 28)
            DisponibleMoves[4] = MT_ACID;
        if (pk.level >= 38)
            DisponibleMoves[5] = MT_PETAL_DANCE;
        if (pk.level >= 52)
            DisponibleMoves[6] = MT_SOLAR_BEAM;
        break;
    case 44: //Vileplume
        DisponibleMoves[0] = MT_ABSORB;
        DisponibleMoves[1] = MT_PETAL_DANCE;
        DisponibleMoves[2] = MT_STUN_SPORE;
        if (pk.level >= 15)
            DisponibleMoves[3] = MT_POISON_POWDER;
        break;
    case 45: //Paras
        DisponibleMoves[0] = MT_SCRATCH;
        if (pk.level >= 13)
            DisponibleMoves[1] = MT_STUN_SPORE;
        if (pk.level >= 20)
            DisponibleMoves[2] = MT_LEECH_LIFE;
        if (pk.level >= 27)
            DisponibleMoves[3] = MT_SPORE;
        if (pk.level >= 34)
            DisponibleMoves[4] = MT_SLASH;
        if (pk.level >= 41)
            DisponibleMoves[5] = MT_GROWTH;
        break;
    case 46: //Parasect
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_STUN_SPORE;
        DisponibleMoves[2] = MT_LEECH_LIFE;
        if (pk.level >= 27)
            DisponibleMoves[3] = MT_SPORE;
        if (pk.level >= 34)
            DisponibleMoves[4] = MT_SLASH;
        if (pk.level >= 41)
            DisponibleMoves[5] = MT_GROWTH;
        break;
    case 47: //Venonat
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_DISABLE;
        if (pk.level >= 24)
            DisponibleMoves[2] = MT_POISON_POWDER;
        if (pk.level >= 27)
            DisponibleMoves[3] = MT_LEECH_LIFE;
        if (pk.level >= 30)
            DisponibleMoves[4] = MT_STUN_SPORE;
        if (pk.level >= 35)
            DisponibleMoves[5] = MT_PSYBEAM;
        if (pk.level >= 38)
            DisponibleMoves[6] = MT_SLEEP_POWDER;
        if (pk.level >= 43)
            DisponibleMoves[7] = MT_PSYCHIC;
        break;
    case 48: //Venomoth
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_DISABLE;
        DisponibleMoves[2] = MT_POISON_POWDER;
        DisponibleMoves[3] = MT_LEECH_LIFE;
        if (pk.level >= 30)
            DisponibleMoves[4] = MT_STUN_SPORE;
        if (pk.level >= 38)
            DisponibleMoves[5] = MT_PSYBEAM;
        if (pk.level >= 43)
            DisponibleMoves[6] = MT_SLEEP_POWDER;
        if (pk.level >= 50)
            DisponibleMoves[7] = MT_PSYCHIC;
        break;
    case 49: //Diglett
        DisponibleMoves[0] = MT_SCRATCH;
        if (pk.level >= 15)
            DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 19)
            DisponibleMoves[2] = MT_DIG;
        if (pk.level >= 24)
            DisponibleMoves[3] = MT_SAND_ATTACK;
        if (pk.level >= 31)
            DisponibleMoves[4] = MT_SLASH;
        if (pk.level >= 40)
            DisponibleMoves[5] = MT_EARTHQUAKE;
        break;
    case 50: //Dugtrio
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_DIG;
        if (pk.level >= 24)
            DisponibleMoves[3] = MT_SAND_ATTACK;
        if (pk.level >= 35)
            DisponibleMoves[4] = MT_SLASH;
        if (pk.level >= 47)
            DisponibleMoves[5] = MT_EARTHQUAKE;
        break;
    case 51: //Meowth
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level >= 12)
            DisponibleMoves[2] = MT_BITE;
        if (pk.level >= 17)
            DisponibleMoves[3] = MT_PAY_DAY;
        if (pk.level >= 24)
            DisponibleMoves[4] = MT_SCREECH;
        if (pk.level >= 33)
            DisponibleMoves[5] = MT_FURY_SWIPES;
        if (pk.level >= 44)
            DisponibleMoves[6] = MT_SLASH;
        break;
    case 52: //Persian
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_BITE;
        DisponibleMoves[3] = MT_SCREECH;
        if (pk.level >= 17)
            DisponibleMoves[4] = MT_PAY_DAY;
        if (pk.level >= 37)
            DisponibleMoves[5] = MT_FURY_SWIPES;
        if (pk.level >= 51)
            DisponibleMoves[6] = MT_SLASH;
        break;
    case 53: //Psyduck
        DisponibleMoves[0] = MT_SCRATCH;
        if (pk.level >= 28)
            DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level >= 31)
            DisponibleMoves[2] = MT_DISABLE;
        if (pk.level >= 36)
            DisponibleMoves[3] = MT_CONFUSION;
        if (pk.level >= 43)
            DisponibleMoves[4] = MT_FURY_SWIPES;
        if (pk.level >= 52)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 54: //Golduck
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_DISABLE;
        DisponibleMoves[6] = MT_AMNESIA;
        if (pk.level >= 39)
            DisponibleMoves[3] = MT_CONFUSION;
        if (pk.level >= 48)
            DisponibleMoves[4] = MT_FURY_SWIPES;
        if (pk.level >= 59)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 55: //Mankey
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_LEER;
        if (pk.level >= 15)
            DisponibleMoves[2] = MT_KARATE_CHOP;
        if (pk.level >= 21)
            DisponibleMoves[3] = MT_FURY_SWIPES;
        if (pk.level >= 27)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level >= 33)
            DisponibleMoves[5] = MT_SEISMIC_TOSS;
        if (pk.level >= 39)
            DisponibleMoves[6] = MT_THRASH;
        break;
    case 56: //Primeape
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_KARATE_CHOP;
        DisponibleMoves[3] = MT_FURY_SWIPES;
        if (pk.level >= 27)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level >= 37)
            DisponibleMoves[5] = MT_SEISMIC_TOSS;
        if (pk.level >= 46)
            DisponibleMoves[6] = MT_THRASH;
        break;
    case 57: //Growlithe
        DisponibleMoves[0] = MT_BITE;
        DisponibleMoves[1] = MT_ROAR;
        if (pk.level <= 18)
            DisponibleMoves[2] = MT_EMBER;
        if (pk.level <= 23)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level <= 30)
            DisponibleMoves[4] = MT_TAKE_DOWN;
        if (pk.level <= 39)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level <= 50)
            DisponibleMoves[6] = MT_FLAMETHROWER;
        break;
    case 58: //Arcanine
        DisponibleMoves[0] = MT_BITE;
        DisponibleMoves[1] = MT_ROAR;
        DisponibleMoves[2] = MT_EMBER;
        DisponibleMoves[3] = MT_LEER;
        DisponibleMoves[4] = MT_TAKE_DOWN;
        DisponibleMoves[5] = MT_AGILITY;
        DisponibleMoves[6] = MT_FLAMETHROWER;
        break;
    case 59: //Poliwag
        DisponibleMoves[0] = MT_BUBBLE;
        if (pk.level <= 16)
            DisponibleMoves[1] = MT_HYPNOSIS;
        if (pk.level <= 19)
            DisponibleMoves[2] = MT_WATER_GUN;
        if (pk.level <= 25)
            DisponibleMoves[3] = MT_DOUBLE_SLAP;
        if (pk.level <= 31)
            DisponibleMoves[4] = MT_BODY_SLAM;
        if (pk.level <= 38)
            DisponibleMoves[5] = MT_AMNESIA;
        if (pk.level <= 45)
            DisponibleMoves[6] = MT_HYDRO_PUMP;
        break;
    case 60: //Poliwhirl
        DisponibleMoves[0] = MT_BUBBLE;
        DisponibleMoves[1] = MT_HYPNOSIS;
        DisponibleMoves[2] = MT_WATER_GUN;
        if (pk.level <= 26)
            DisponibleMoves[3] = MT_DOUBLE_SLAP;
        if (pk.level <= 33)
            DisponibleMoves[4] = MT_BODY_SLAM;
        if (pk.level <= 41)
            DisponibleMoves[5] = MT_AMNESIA;
        if (pk.level <= 49)
            DisponibleMoves[6] = MT_HYDRO_PUMP;
        break;
    case 61: //Poliwrath
        DisponibleMoves[0] = MT_BUBBLE;
        DisponibleMoves[1] = MT_HYPNOSIS;
        DisponibleMoves[2] = MT_WATER_GUN;
        DisponibleMoves[3] = MT_DOUBLE_SLAP;
        DisponibleMoves[4] = MT_BODY_SLAM;
        DisponibleMoves[5] = MT_AMNESIA;
        DisponibleMoves[6] = MT_HYDRO_PUMP;
        break;
    case 62: //Abra
        DisponibleMoves[0] = MT_TELEPORT;
        break;
    case 63: //Kadabra
    case 64: //Alakazam
        DisponibleMoves[0] = MT_TELEPORT;
        DisponibleMoves[1] = MT_CONFUSION;
        DisponibleMoves[2] = MT_DISABLE;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_PSYBEAM;
        if (pk.level <= 31)
            DisponibleMoves[4] = MT_RECOVER;
        if (pk.level <= 38)
            DisponibleMoves[5] = MT_PSYCHIC;
        if (pk.level <= 42)
            DisponibleMoves[6] = MT_REFLECT;
        break;
    case 65: //Machop
        DisponibleMoves[0] = MT_KARATE_CHOP;
        if (pk.level <= 20)
            DisponibleMoves[1] = MT_LOW_KICK;
        if (pk.level <= 25)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 32)
            DisponibleMoves[3] = MT_FOCUS_ENERGY;
        if (pk.level <= 39)
            DisponibleMoves[4] = MT_SEISMIC_TOSS;
        if (pk.level <= 46)
            DisponibleMoves[5] = MT_SUBMISSION;
        break;
    case 66: //Machoke
    case 67: //Machamp
        DisponibleMoves[0] = MT_KARATE_CHOP;
        DisponibleMoves[1] = MT_LOW_KICK;
        DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 36)
            DisponibleMoves[3] = MT_FOCUS_ENERGY;
        if (pk.level <= 44)
            DisponibleMoves[4] = MT_SEISMIC_TOSS;
        if (pk.level <= 52)
            DisponibleMoves[5] = MT_SUBMISSION;
        break;
    case 68: //Bellsprout
        DisponibleMoves[0] = MT_VINE_WHIP;
        DisponibleMoves[1] = MT_GROWTH;
        if (pk.level <= 13)
            DisponibleMoves[2] = MT_WRAP;
        if (pk.level <= 15)
            DisponibleMoves[3] = MT_POISON_POWDER;
        if (pk.level <= 18)
            DisponibleMoves[4] = MT_SLEEP_POWDER;
        if (pk.level <= 21)
            DisponibleMoves[5] = MT_STUN_SPORE;
        if (pk.level <= 26)
            DisponibleMoves[6] = MT_ACID;
        if (pk.level <= 33)
            DisponibleMoves[7] = MT_RAZOR_LEAF;
        if (pk.level <= 42)
            DisponibleMoves[8] = MT_SLEEP_POWDER;
        break;
    case 69: //Weepinbell
        DisponibleMoves[0] = MT_VINE_WHIP;
        DisponibleMoves[1] = MT_GROWTH;
        DisponibleMoves[2] = MT_WRAP;
        if (pk.level <= 15)
            DisponibleMoves[3] = MT_POISON_POWDER;
        if (pk.level <= 18)
            DisponibleMoves[4] = MT_SLEEP_POWDER;
        if (pk.level <= 23)
            DisponibleMoves[5] = MT_STUN_SPORE;
        if (pk.level <= 29)
            DisponibleMoves[6] = MT_ACID;
        if (pk.level <= 38)
            DisponibleMoves[7] = MT_RAZOR_LEAF;
        if (pk.level <= 49)
            DisponibleMoves[8] = MT_SLAM;
        break;
    case 70: //Victreebel
        DisponibleMoves[0] = MT_VINE_WHIP;
        DisponibleMoves[1] = MT_GROWTH;
        DisponibleMoves[2] = MT_WRAP;
        DisponibleMoves[9] = MT_SLAM;
        DisponibleMoves[6] = MT_ACID;
        DisponibleMoves[7] = MT_RAZOR_LEAF;
        DisponibleMoves[5] = MT_STUN_SPORE;
        if (pk.level <= 15)
            DisponibleMoves[3] = MT_POISON_POWDER;
        if (pk.level <= 18)
            DisponibleMoves[4] = MT_SLEEP_POWDER;
        break;
    case 71: //Tentacool
        DisponibleMoves[0] = MT_ACID;
        if (pk.level <= 7)
            DisponibleMoves[1] = MT_SUPERSONIC;
        if (pk.level <= 13)
            DisponibleMoves[2] = MT_WRAP;
        if (pk.level <= 18)
            DisponibleMoves[3] = MT_POISON_STING;
        if (pk.level <= 22)
            DisponibleMoves[4] = MT_WATER_GUN;
        if (pk.level <= 27)
            DisponibleMoves[5] = MT_CONSTRICT;
        if (pk.level <= 33)
            DisponibleMoves[6] = MT_BARRIER;
        if (pk.level <= 40)
            DisponibleMoves[7] = MT_SCREECH;
        if (pk.level <= 48)
            DisponibleMoves[8] = MT_HYDRO_PUMP;
        break;
    case 72: //Tentacruel
        DisponibleMoves[0] = MT_ACID;
        DisponibleMoves[1] = MT_SUPERSONIC;
        DisponibleMoves[2] = MT_WRAP;
        if (pk.level <= 18)
            DisponibleMoves[3] = MT_POISON_STING;
        if (pk.level <= 22)
            DisponibleMoves[4] = MT_WATER_GUN;
        if (pk.level <= 27)
            DisponibleMoves[5] = MT_CONSTRICT;
        if (pk.level <= 35)
            DisponibleMoves[6] = MT_BARRIER;
        if (pk.level <= 43)
            DisponibleMoves[7] = MT_SCREECH;
        if (pk.level <= 50)
            DisponibleMoves[8] = MT_HYDRO_PUMP;
        break;
    case 73: //Geodude
        DisponibleMoves[0] = MT_TACKLE;
        if (pk.level <= 11)
            DisponibleMoves[1] = MT_DEFENSE_CURL;
        if (pk.level <= 16)
            DisponibleMoves[2] = MT_ROCK_THROW;
        if (pk.level <= 21)
            DisponibleMoves[3] = MT_SELF_DESTRUCT;
        if (pk.level <= 26)
            DisponibleMoves[4] = MT_HARDEN;
        if (pk.level <= 31)
            DisponibleMoves[5] = MT_EARTHQUAKE;
        if (pk.level <= 36)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 74: //Graveler
    case 75: //Golem
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_DEFENSE_CURL;
        if (pk.level <= 16)
            DisponibleMoves[2] = MT_ROCK_THROW;
        if (pk.level <= 21)
            DisponibleMoves[3] = MT_SELF_DESTRUCT;
        if (pk.level <= 29)
            DisponibleMoves[4] = MT_HARDEN;
        if (pk.level <= 36)
            DisponibleMoves[5] = MT_EARTHQUAKE;
        if (pk.level <= 43)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 76: //Ponyta
        DisponibleMoves[0] = MT_EMBER;
        if (pk.level <= 30)
            DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level <= 32)
            DisponibleMoves[2] = MT_STOMP;
        if (pk.level <= 35)
            DisponibleMoves[3] = MT_GROWL;
        if (pk.level <= 39)
            DisponibleMoves[4] = MT_FIRE_SPIN;
        if (pk.level <= 43)
            DisponibleMoves[5] = MT_TAKE_DOWN;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 77: //Rapidash
        DisponibleMoves[0] = MT_EMBER;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_STOMP;
        DisponibleMoves[3] = MT_GROWL;
        if (pk.level <= 39)
            DisponibleMoves[4] = MT_FIRE_SPIN;
        if (pk.level <= 47)
            DisponibleMoves[5] = MT_TAKE_DOWN;
        if (pk.level <= 55)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 78: //Slowpoke
        DisponibleMoves[0] = MT_CONFUSION;
        if (pk.level <= 18)
            DisponibleMoves[1] = MT_DISABLE;
        if (pk.level <= 22)
            DisponibleMoves[2] = MT_HEADBUTT;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_GROWL;
        if (pk.level <= 33)
            DisponibleMoves[4] = MT_WATER_GUN;
        if (pk.level <= 40)
            DisponibleMoves[5] = MT_AMNESIA;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_PSYCHIC;
        break;
    case 79: //Slowbro
        DisponibleMoves[0] = MT_CONFUSION;
        DisponibleMoves[1] = MT_DISABLE;
        DisponibleMoves[2] = MT_HEADBUTT;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_GROWL;
        if (pk.level <= 33)
            DisponibleMoves[4] = MT_WATER_GUN;
        if (pk.level <= 44)
            DisponibleMoves[5] = MT_AMNESIA;
        if (pk.level <= 55)
            DisponibleMoves[6] = MT_PSYCHIC;
        if (pk.level <= 37)
            DisponibleMoves[7] = MT_WITHDRAW;
        break;
    case 80: //Magnemite
        DisponibleMoves[0] = MT_TACKLE;
        if (pk.level <= 21)
            DisponibleMoves[1] = MT_SONIC_BOOM;
        if (pk.level <= 25)
            DisponibleMoves[2] = MT_THUNDER_SHOCK;
        if (pk.level <= 29)
            DisponibleMoves[3] = MT_SUPERSONIC;
        if (pk.level <= 35)
            DisponibleMoves[4] = MT_THUNDER_WAVE;
        if (pk.level <= 41)
            DisponibleMoves[5] = MT_SWIFT;
        if (pk.level <= 47)
            DisponibleMoves[6] = MT_SCREECH;
        break;
    case 81: //Magneton
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SONIC_BOOM;
        DisponibleMoves[2] = MT_THUNDER_SHOCK;
        if (pk.level <= 29)
            DisponibleMoves[3] = MT_SUPERSONIC;
        if (pk.level <= 38)
            DisponibleMoves[4] = MT_THUNDER_WAVE;
        if (pk.level <= 46)
            DisponibleMoves[5] = MT_SWIFT;
        if (pk.level <= 54)
            DisponibleMoves[6] = MT_SCREECH;
        break;
    case 82: //Farfetch'd
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level <= 7)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 15)
            DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level <= 23)
            DisponibleMoves[4] = MT_SWORDS_DANCE;
        if (pk.level <= 31)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level <= 39)
            DisponibleMoves[6] = MT_SLASH;
        break;
    case 83: //Doduo
        DisponibleMoves[0] = MT_PECK;
        if (pk.level <= 20)
            DisponibleMoves[1] = MT_GROWL;
        if (pk.level <= 24)
            DisponibleMoves[2] = MT_FURY_ATTACK;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_DRILL_PECK;
        if (pk.level <= 36)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level <= 40)
            DisponibleMoves[5] = MT_TRI_ATTACK;
        if (pk.level <= 44)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 84: //Dodrio
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_FURY_ATTACK;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_DRILL_PECK;
        if (pk.level <= 39)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level <= 45)
            DisponibleMoves[5] = MT_TRI_ATTACK;
        if (pk.level <= 51)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 85: //Seel
        DisponibleMoves[0] = MT_HEADBUTT;
        if (pk.level <= 30)
            DisponibleMoves[1] = MT_GROWL;
        if (pk.level <= 35)
            DisponibleMoves[2] = MT_AURORA_BEAM;
        if (pk.level <= 40)
            DisponibleMoves[3] = MT_REST;
        if (pk.level <= 45)
            DisponibleMoves[4] = MT_TAKE_DOWN;
        if (pk.level <= 50)
            DisponibleMoves[5] = MT_ICE_BEAM;
        break;
    case 86: //Dewgong
        DisponibleMoves[0] = MT_HEADBUTT;
        DisponibleMoves[1] = MT_GROWL;
        DisponibleMoves[2] = MT_AURORA_BEAM;
        if (pk.level <= 44)
            DisponibleMoves[3] = MT_REST;
        if (pk.level <= 50)
            DisponibleMoves[4] = MT_TAKE_DOWN;
        if (pk.level <= 56)
            DisponibleMoves[5] = MT_ICE_BEAM;
        break;
    case 87: //Grimer
        DisponibleMoves[0] = MT_DISABLE;
        DisponibleMoves[1] = MT_POUND;
        if (pk.level <= 30)
            DisponibleMoves[2] = MT_POISON_GAS;
        if (pk.level <= 33)
            DisponibleMoves[3] = MT_MINIMIZE;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_SLUDGE;
        if (pk.level <= 42)
            DisponibleMoves[5] = MT_HARDEN;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_SCREECH;
        if (pk.level <= 55)
            DisponibleMoves[7] = MT_ACID_ARMOR;
        break;
    case 88: //Muk
        DisponibleMoves[0] = MT_DISABLE;
        DisponibleMoves[1] = MT_POUND;
        DisponibleMoves[2] = MT_POISON_GAS;
        if (pk.level <= 33)
            DisponibleMoves[3] = MT_MINIMIZE;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_SLUDGE;
        if (pk.level <= 45)
            DisponibleMoves[5] = MT_HARDEN;
        if (pk.level <= 53)
            DisponibleMoves[6] = MT_SCREECH;
        if (pk.level <= 60)
            DisponibleMoves[7] = MT_ACID_ARMOR;
        break;
    case 89: //Shellder
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_WITHDRAW;
        if (pk.level <= 18)
            DisponibleMoves[2] = MT_SUPERSONIC;
        if (pk.level <= 23)
            DisponibleMoves[3] = MT_CLAMP;
        if (pk.level <= 30)
            DisponibleMoves[4] = MT_AURORA_BEAM;
        if (pk.level <= 39)
            DisponibleMoves[5] = MT_LEER;
        if (pk.level <= 50)
            DisponibleMoves[6] = MT_ICE_BEAM;
        break;
    case 90: //Cloyster
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_WITHDRAW;
        DisponibleMoves[5] = MT_LEER;
        DisponibleMoves[2] = MT_SUPERSONIC;
        DisponibleMoves[3] = MT_CLAMP;
        DisponibleMoves[4] = MT_AURORA_BEAM;
        if (pk.level <= 50)
            DisponibleMoves[6] = MT_SPIKE_CANNON;
        break;
    case 91: //Gastly
        DisponibleMoves[0] = MT_LICK;
        DisponibleMoves[1] = MT_CONFUSE_RAY;
        DisponibleMoves[2] = MT_NIGHT_SHADE;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_HYPNOSIS;
        if (pk.level <= 35)
            DisponibleMoves[4] = MT_DREAM_EATER;
        break;
    case 92: //Haunter
        DisponibleMoves[0] = MT_LICK;
        DisponibleMoves[1] = MT_CONFUSE_RAY;
        DisponibleMoves[2] = MT_NIGHT_SHADE;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_HYPNOSIS;
        if (pk.level <= 35)
            DisponibleMoves[4] = MT_DREAM_EATER;
        break;
    case 93: //Genagr
        DisponibleMoves[0] = MT_LICK;
        DisponibleMoves[1] = MT_CONFUSE_RAY;
        DisponibleMoves[2] = MT_NIGHT_SHADE;
        if (pk.level <= 29)
            DisponibleMoves[3] = MT_HYPNOSIS;
        if (pk.level <= 38)
            DisponibleMoves[4] = MT_DREAM_EATER;
        break;
    case 94: //Onix
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SCREECH;
        if (pk.level <= 15)
            DisponibleMoves[2] = MT_BIND;
        if (pk.level <= 19)
            DisponibleMoves[3] = MT_ROCK_THROW;
        if (pk.level <= 25)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level <= 33)
            DisponibleMoves[5] = MT_SLAM;
        if (pk.level <= 43)
            DisponibleMoves[6] = MT_HARDEN;
        break;
    case 95: //Drowzee
        DisponibleMoves[0] = MT_POUND;
        DisponibleMoves[1] = MT_HYPNOSIS;
        if (pk.level <= 12)
            DisponibleMoves[2] = MT_DISABLE;
        if (pk.level <= 17)
            DisponibleMoves[3] = MT_CONFUSION;
        if (pk.level <= 24)
            DisponibleMoves[4] = MT_HEADBUTT;
        if (pk.level <= 29)
            DisponibleMoves[5] = MT_POISON_GAS;
        if (pk.level <= 32)
            DisponibleMoves[6] = MT_PSYCHIC;
        if (pk.level <= 37)
            DisponibleMoves[7] = MT_MEDITATE;
        break;
    case 96: //Hypno
        DisponibleMoves[0] = MT_POUND;
        DisponibleMoves[1] = MT_HYPNOSIS;
        DisponibleMoves[2] = MT_DISABLE;
        DisponibleMoves[3] = MT_CONFUSION;
        if (pk.level <= 24)
            DisponibleMoves[4] = MT_HEADBUTT;
        if (pk.level <= 33)
            DisponibleMoves[5] = MT_POISON_GAS;
        if (pk.level <= 37)
            DisponibleMoves[6] = MT_PSYCHIC;
        if (pk.level <= 43)
            DisponibleMoves[7] = MT_MEDITATE;
        break;
    case 97: //Krabby
        DisponibleMoves[0] = MT_BUBBLE;
        DisponibleMoves[1] = MT_LEER;
        if (pk.level <= 20)
            DisponibleMoves[2] = MT_VISE_GRIP;
        if (pk.level <= 25)
            DisponibleMoves[3] = MT_GUILLOTINE;
        if (pk.level <= 30)
            DisponibleMoves[4] = MT_STOMP;
        if (pk.level <= 35)
            DisponibleMoves[5] = MT_CRABHAMMER;
        if (pk.level <= 40)
            DisponibleMoves[6] = MT_HARDEN;
        break;
    case 98: //Kingler
        DisponibleMoves[0] = MT_BUBBLE;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_VISE_GRIP;
        if (pk.level <= 25)
            DisponibleMoves[3] = MT_GUILLOTINE;
        if (pk.level <= 34)
            DisponibleMoves[4] = MT_STOMP;
        if (pk.level <= 42)
            DisponibleMoves[5] = MT_CRABHAMMER;
        if (pk.level <= 49)
            DisponibleMoves[6] = MT_HARDEN;
        break;
    case 99: //Voltorb
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SCREECH;
        if (pk.level <= 17)
            DisponibleMoves[2] = MT_SONIC_BOOM;
        if (pk.level <= 22)
            DisponibleMoves[3] = MT_SELF_DESTRUCT;
        if (pk.level <= 29)
            DisponibleMoves[4] = MT_LIGHT_SCREEN;
        if (pk.level <= 36)
            DisponibleMoves[5] = MT_SWIFT;
        if (pk.level <= 43)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 100: //Electrode
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SCREECH;
        DisponibleMoves[2] = MT_SONIC_BOOM;
        if (pk.level <= 22)
            DisponibleMoves[3] = MT_SELF_DESTRUCT;
        if (pk.level <= 29)
            DisponibleMoves[4] = MT_LIGHT_SCREEN;
        if (pk.level <= 40)
            DisponibleMoves[5] = MT_SWIFT;
        if (pk.level <= 50)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 101: //Exeggcute
        DisponibleMoves[0] = MT_BARRAGE;
        DisponibleMoves[1] = MT_HYPNOSIS;
        if (pk.level <= 25)
            DisponibleMoves[2] = MT_REFLECT;
        if (pk.level <= 28)
            DisponibleMoves[3] = MT_LEECH_SEED;
        if (pk.level <= 32)
            DisponibleMoves[4] = MT_STUN_SPORE;
        if (pk.level <= 37)
            DisponibleMoves[5] = MT_POISON_POWDER;
        if (pk.level <= 42)
            DisponibleMoves[6] = MT_SOLAR_BEAM;
        if (pk.level <= 48)
            DisponibleMoves[7] = MT_SLEEP_POWDER;
        break;
    case 102: //Exeggutor
        DisponibleMoves[0] = MT_BARRAGE;
        DisponibleMoves[1] = MT_HYPNOSIS;
        DisponibleMoves[2] = MT_LEECH_SEED;
        DisponibleMoves[3] = MT_STUN_SPORE;
        DisponibleMoves[4] = MT_POISON_POWDER;
        DisponibleMoves[5] = MT_SLEEP_POWDER;
        if (pk.level <= 28)
            DisponibleMoves[6] = MT_STOMP;

        break;
    case 103: //Cubone
        DisponibleMoves[0] = MT_GROWL;
        DisponibleMoves[1] = MT_BONE_CLUB;
        if (pk.level <= 25)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 31)
            DisponibleMoves[3] = MT_FOCUS_ENERGY;
        if (pk.level <= 38)
            DisponibleMoves[4] = MT_THRASH;
        if (pk.level <= 43)
            DisponibleMoves[5] = MT_BONEMERANG;
        if (pk.level <= 46)
            DisponibleMoves[6] = MT_RAGE;
        break;
    case 104: //Marowak
        DisponibleMoves[0] = MT_GROWL;
        DisponibleMoves[1] = MT_BONE_CLUB;
        DisponibleMoves[2] = MT_LEER;
        DisponibleMoves[3] = MT_FOCUS_ENERGY;
        if (pk.level <= 41)
            DisponibleMoves[4] = MT_THRASH;
        if (pk.level <= 48)
            DisponibleMoves[5] = MT_BONEMERANG;
        if (pk.level <= 55)
            DisponibleMoves[6] = MT_RAGE;
        break;
    case 105: //Hitmonlee
        DisponibleMoves[0] = MT_DOUBLE_KICK;
        DisponibleMoves[1] = MT_MEDITATE;
        if (pk.level <= 33)
            DisponibleMoves[2] = MT_ROLLING_KICK;
        if (pk.level <= 38)
            DisponibleMoves[3] = MT_JUMP_KICK;
        if (pk.level <= 43)
            DisponibleMoves[4] = MT_FOCUS_ENERGY;
        if (pk.level <= 48)
            DisponibleMoves[5] = MT_HIGH_JUMP_KICK;
        if (pk.level <= 53)
            DisponibleMoves[6] = MT_MEGA_KICK;
        break;
    case 106: //Hitmonchan
        DisponibleMoves[0] = MT_COMET_PUNCH;
        DisponibleMoves[1] = MT_AGILITY;
        if (pk.level <= 33)
            DisponibleMoves[2] = MT_FIRE_PUNCH;
        if (pk.level <= 38)
            DisponibleMoves[3] = MT_ICE_PUNCH;
        if (pk.level <= 43)
            DisponibleMoves[4] = MT_THUNDER_PUNCH;
        if (pk.level <= 48)
            DisponibleMoves[5] = MT_MEGA_PUNCH;
        if (pk.level <= 53)
            DisponibleMoves[6] = MT_COUNTER;
        break;
    case 107: //Lickitung
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_SUPERSONIC;
        if (pk.level <= 7)
            DisponibleMoves[2] = MT_STOMP;
        if (pk.level <= 15)
            DisponibleMoves[3] = MT_DISABLE;
        if (pk.level <= 23)
            DisponibleMoves[4] = MT_DEFENSE_CURL;
        if (pk.level <= 31)
            DisponibleMoves[5] = MT_SLAM;
        if (pk.level <= 39)
            DisponibleMoves[6] = MT_SCREECH;
        break;
    case 108: //Koffing
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SMOG;
        if (pk.level <= 32)
            DisponibleMoves[2] = MT_SLUDGE;
        if (pk.level <= 37)
            DisponibleMoves[3] = MT_SMOKESCREEN;
        if (pk.level <= 40)
            DisponibleMoves[4] = MT_SELF_DESTRUCT;
        if (pk.level <= 45)
            DisponibleMoves[5] = MT_HAZE;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 109: //Weezing
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SMOG;
        DisponibleMoves[2] = MT_SLUDGE;
        if (pk.level <= 39)
            DisponibleMoves[3] = MT_SMOKESCREEN;
        if (pk.level <= 43)
            DisponibleMoves[4] = MT_SELF_DESTRUCT;
        if (pk.level <= 49)
            DisponibleMoves[5] = MT_HAZE;
        if (pk.level <= 53)
            DisponibleMoves[6] = MT_EXPLOSION;
        break;
    case 110: //Rhyhorn
        DisponibleMoves[0] = MT_HORN_ATTACK;
        if (pk.level <= 30)
            DisponibleMoves[1] = MT_STOMP;
        if (pk.level <= 35)
            DisponibleMoves[2] = MT_TAIL_WHIP;
        if (pk.level <= 40)
            DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level <= 45)
            DisponibleMoves[4] = MT_HORN_DRILL;
        if (pk.level <= 50)
            DisponibleMoves[5] = MT_LEER;
        if (pk.level <= 55)
            DisponibleMoves[6] = MT_TAKE_DOWN;
        break;
    case 111: //Rhydon
        DisponibleMoves[0] = MT_HORN_ATTACK;
        DisponibleMoves[1] = MT_STOMP;
        DisponibleMoves[2] = MT_TAIL_WHIP;
        DisponibleMoves[3] = MT_FURY_ATTACK;
        if (pk.level <= 48)
            DisponibleMoves[4] = MT_HORN_DRILL;
        if (pk.level <= 55)
            DisponibleMoves[5] = MT_LEER;
        if (pk.level <= 64)
            DisponibleMoves[6] = MT_TAKE_DOWN;
        break;
    case 112: //Chansey
        DisponibleMoves[0] = MT_POUND;
        DisponibleMoves[1] = MT_DOUBLE_SLAP;
        if (pk.level <= 24)
            DisponibleMoves[2] = MT_SING;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_GROWL;
        if (pk.level <= 38)
            DisponibleMoves[4] = MT_MINIMIZE;
        if (pk.level <= 44)
            DisponibleMoves[5] = MT_DEFENSE_CURL;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_LIGHT_SCREEN;
        if (pk.level <= 54)
            DisponibleMoves[7] = MT_DOUBLE_EDGE;
        break;
    case 113: //Tangela
        DisponibleMoves[0] = MT_CONSTRICT;
        DisponibleMoves[1] = MT_BIND;
        if (pk.level <= 29)
            DisponibleMoves[2] = MT_ABSORB;
        if (pk.level <= 32)
            DisponibleMoves[3] = MT_POISON_POWDER;
        if (pk.level <= 36)
            DisponibleMoves[4] = MT_STUN_SPORE;
        if (pk.level <= 39)
            DisponibleMoves[5] = MT_SLEEP_POWDER;
        if (pk.level <= 45)
            DisponibleMoves[6] = MT_SLAM;
        if (pk.level <= 49)
            DisponibleMoves[7] = MT_GROWTH;
        break;
    case 114: //Kangaskhan
        DisponibleMoves[0] = MT_BUBBLE;
        if (pk.level <= 19)
            DisponibleMoves[1] = MT_SMOKESCREEN;
        if (pk.level <= 24)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_AGILITY;
        if (pk.level <= 45)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 115: //Horsea
        DisponibleMoves[0] = MT_BUBBLE;
        if (pk.level <= 19)
            DisponibleMoves[1] = MT_SMOKESCREEN;
        if (pk.level <= 24)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_AGILITY;
        if (pk.level <= 45)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 116: //Seadra
        DisponibleMoves[0] = MT_BUBBLE;
        DisponibleMoves[1] = MT_SMOKESCREEN;
        if (pk.level <= 24)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level <= 30)
            DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level <= 41)
            DisponibleMoves[4] = MT_AGILITY;
        if (pk.level <= 52)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 117: //Goldeen
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        if (pk.level <= 19)
            DisponibleMoves[2] = MT_SUPERSONIC;
        if (pk.level <= 24)
            DisponibleMoves[3] = MT_HORN_ATTACK;
        if (pk.level <= 30)
            DisponibleMoves[4] = MT_FURY_ATTACK;
        if (pk.level <= 37)
            DisponibleMoves[5] = MT_WATERFALL;
        if (pk.level <= 45)
            DisponibleMoves[6] = MT_HORN_DRILL;
        if (pk.level <= 54)
            DisponibleMoves[7] = MT_AGILITY;
        break;
    case 118: //Seaking
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_TAIL_WHIP;
        DisponibleMoves[2] = MT_SUPERSONIC;
        if (pk.level <= 24)
            DisponibleMoves[3] = MT_HORN_ATTACK;
        if (pk.level <= 30)
            DisponibleMoves[4] = MT_FURY_ATTACK;
        if (pk.level <= 39)
            DisponibleMoves[5] = MT_WATERFALL;
        if (pk.level <= 48)
            DisponibleMoves[6] = MT_HORN_DRILL;
        if (pk.level <= 54)
            DisponibleMoves[7] = MT_AGILITY;
        break;
    case 119: //Staryu
        DisponibleMoves[0] = MT_TACKLE;
        if (pk.level <= 17)
            DisponibleMoves[1] = MT_WATER_GUN;
        if (pk.level <= 22)
            DisponibleMoves[2] = MT_HARDEN;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_RECOVER;
        if (pk.level <= 32)
            DisponibleMoves[4] = MT_SWIFT;
        if (pk.level <= 37)
            DisponibleMoves[5] = MT_MINIMIZE;
        if (pk.level <= 42)
            DisponibleMoves[6] = MT_LIGHT_SCREEN;
        if (pk.level <= 47)
            DisponibleMoves[7] = MT_HYDRO_PUMP;
        break;
    case 120: //Starmie
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_WATER_GUN;
        DisponibleMoves[2] = MT_HARDEN;
        DisponibleMoves[3] = MT_RECOVER;
        DisponibleMoves[4] = MT_MINIMIZE;
        DisponibleMoves[5] = MT_LIGHT_SCREEN;
        DisponibleMoves[6] = MT_HYDRO_PUMP;
        break;
    case 121: //Mr.Mime
        DisponibleMoves[0] = MT_CONFUSION;
        DisponibleMoves[1] = MT_BARRIER;
        if (pk.level <= 23)
            DisponibleMoves[2] = MT_LIGHT_SCREEN;
        if (pk.level <= 31)
            DisponibleMoves[3] = MT_DOUBLE_SLAP;
        if (pk.level <= 39)
            DisponibleMoves[4] = MT_MEDITATE;
        if (pk.level <= 47)
            DisponibleMoves[5] = MT_SUBSTITUTE;
        break;
    case 122: //Scyther
        DisponibleMoves[0] = MT_QUICK_ATTACK;
        if (pk.level <= 17)
            DisponibleMoves[1] = MT_LEER;
        if (pk.level <= 20)
            DisponibleMoves[2] = MT_FOCUS_ENERGY;
        if (pk.level <= 24)
            DisponibleMoves[3] = MT_DOUBLE_TEAM;
        if (pk.level <= 29)
            DisponibleMoves[4] = MT_SLASH;
        if (pk.level <= 35)
            DisponibleMoves[5] = MT_SWORDS_DANCE;
        if (pk.level <= 42)
            DisponibleMoves[6] = MT_AGILITY;
        break;
    case 123: //Jynx
        DisponibleMoves[0] = MT_POUND;
        DisponibleMoves[1] = MT_LOVELY_KISS;
        if (pk.level <= 18)
            DisponibleMoves[2] = MT_LICK;
        if (pk.level <= 23)
            DisponibleMoves[3] = MT_DOUBLE_SLAP;
        if (pk.level <= 31)
            DisponibleMoves[4] = MT_ICE_PUNCH;
        if (pk.level <= 39)
            DisponibleMoves[5] = MT_BODY_SLAM;
        if (pk.level <= 47)
            DisponibleMoves[6] = MT_THRASH;
        if (pk.level <= 58)
            DisponibleMoves[7] = MT_BLIZZARD;
        break;
    case 124: //Electabuzz
        DisponibleMoves[0] = MT_QUICK_ATTACK;
        DisponibleMoves[1] = MT_LEER;
        if (pk.level <= 34)
            DisponibleMoves[2] = MT_THUNDER_SHOCK;
        if (pk.level <= 37)
            DisponibleMoves[3] = MT_SCREECH;
        if (pk.level <= 42)
            DisponibleMoves[4] = MT_THUNDER_PUNCH;
        if (pk.level <= 49)
            DisponibleMoves[5] = MT_LIGHT_SCREEN;
        if (pk.level <= 54)
            DisponibleMoves[6] = MT_THUNDER;
        break;
    case 125: //Magmar
        DisponibleMoves[0] = MT_EMBER;
        if (pk.level <= 36)
            DisponibleMoves[1] = MT_LEER;
        if (pk.level <= 39)
            DisponibleMoves[2] = MT_CONFUSE_RAY;
        if (pk.level <= 43)
            DisponibleMoves[3] = MT_FIRE_PUNCH;
        if (pk.level <= 48)
            DisponibleMoves[4] = MT_SMOKESCREEN;
        if (pk.level <= 52)
            DisponibleMoves[5] = MT_SMOG;
        if (pk.level <= 55)
            DisponibleMoves[6] = MT_FLAMETHROWER;
        break;
    case 126: //Pinsir
        DisponibleMoves[0] = MT_VISE_GRIP;
        if (pk.level <= 25)
            DisponibleMoves[1] = MT_SEISMIC_TOSS;
        if (pk.level <= 30)
            DisponibleMoves[2] = MT_GUILLOTINE;
        if (pk.level <= 36)
            DisponibleMoves[3] = MT_FOCUS_ENERGY;
        if (pk.level <= 43)
            DisponibleMoves[4] = MT_HARDEN;
        if (pk.level <= 49)
            DisponibleMoves[5] = MT_SLASH;
        if (pk.level <= 54)
            DisponibleMoves[6] = MT_SWORDS_DANCE;
        break;
    case 127: //Tauros
        DisponibleMoves[0] = MT_TACKLE;
        if (pk.level <= 21)
            DisponibleMoves[1] = MT_STOMP;
        if (pk.level <= 28)
            DisponibleMoves[2] = MT_TAIL_WHIP;
        if (pk.level <= 35)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level <= 44)
            DisponibleMoves[4] = MT_RAGE;
        if (pk.level <= 51)
            DisponibleMoves[5] = MT_TAKE_DOWN;
        break;
    case 128: //Magikarp
        DisponibleMoves[0] = MT_SPLASH;
        if (pk.level <= 15)
            DisponibleMoves[1] = MT_TACKLE;
        break;
    case 129: //Gyarados
        DisponibleMoves[0] = MT_BITE;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_DRAGON_RAGE;
        DisponibleMoves[3] = MT_HYDRO_PUMP;
        DisponibleMoves[4] = MT_SPLASH;
        DisponibleMoves[5] = MT_TACKLE;
        if (pk.level <= 52)
            DisponibleMoves[6] = MT_HYPER_BEAM;
        break;
    case 130: //Lapras
        DisponibleMoves[0] = MT_WATER_GUN;
        DisponibleMoves[1] = MT_GROWL;
        if (pk.level <= 16)
            DisponibleMoves[2] = MT_SING;
        if (pk.level <= 20)
            DisponibleMoves[3] = MT_MIST;
        if (pk.level <= 25)
            DisponibleMoves[4] = MT_BODY_SLAM;
        if (pk.level <= 31)
            DisponibleMoves[5] = MT_CONFUSE_RAY;
        if (pk.level <= 38)
            DisponibleMoves[6] = MT_ICE_BEAM;
        if (pk.level <= 46)
            DisponibleMoves[7] = MT_HYDRO_PUMP;
        break;
    case 131: //Ditto
        DisponibleMoves[0] = MT_TRANSFORM;
        break;
    case 132: //Eevee
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        if (pk.level <= 31)
            DisponibleMoves[2] = MT_TAIL_WHIP;
        if (pk.level <= 27)
            DisponibleMoves[3] = MT_QUICK_ATTACK;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_BITE;
        if (pk.level <= 42)
            DisponibleMoves[5] = MT_TAKE_DOWN;
        break;
    case 133: //Vaporeon
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        DisponibleMoves[3] = MT_WATER_GUN;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_TAIL_WHIP;
        if (pk.level <= 40)
            DisponibleMoves[5] = MT_BITE;
        if (pk.level <= 44)
            DisponibleMoves[6] = MT_HAZE;
        if (pk.level <= 42)
            DisponibleMoves[7] = MT_ACID_ARMOR;
        if (pk.level <= 54)
            DisponibleMoves[8] = MT_HYDRO_PUMP;
        if (pk.level <= 48)
            DisponibleMoves[9] = MT_MIST;
        break;
    case 134: //Jolteon
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        DisponibleMoves[3] = MT_THUNDER_SHOCK;
        if (pk.level <= 42)
            DisponibleMoves[4] = MT_DOUBLE_KICK;
        if (pk.level <= 48)
            DisponibleMoves[5] = MT_PIN_MISSILE;
        if (pk.level <= 40)
            DisponibleMoves[6] = MT_THUNDER_WAVE;
        if (pk.level <= 44)
            DisponibleMoves[7] = MT_AGILITY;
        if (pk.level <= 54)
            DisponibleMoves[8] = MT_THUNDER;
        break;
    case 135: //Flareon
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SAND_ATTACK;
        DisponibleMoves[2] = MT_QUICK_ATTACK;
        DisponibleMoves[3] = MT_EMBER;
        if (pk.level <= 37)
            DisponibleMoves[4] = MT_TAIL_WHIP;
        if (pk.level <= 40)
            DisponibleMoves[5] = MT_BITE;
        if (pk.level <= 44)
            DisponibleMoves[6] = MT_FIRE_SPIN;
        if (pk.level <= 42)
            DisponibleMoves[7] = MT_LEER;
        if (pk.level <= 54)
            DisponibleMoves[8] = MT_FLAMETHROWER;
        break;
    case 136: //Porygon
        DisponibleMoves[0] = MT_TACKLE;
        DisponibleMoves[1] = MT_SHARPEN;
        DisponibleMoves[2] = MT_CONVERSION;
        if (pk.level <= 23)
            DisponibleMoves[3] = MT_PSYBEAM;
        if (pk.level <= 28)
            DisponibleMoves[4] = MT_RECOVER;
        if (pk.level <= 35)
            DisponibleMoves[5] = MT_AGILITY;
        if (pk.level <= 42)
            DisponibleMoves[6] = MT_TRI_ATTACK;
        break;
    case 137: //Omanyte
        DisponibleMoves[0] = MT_WATER_GUN;
        DisponibleMoves[1] = MT_WITHDRAW;
        if (pk.level <= 34)
            DisponibleMoves[2] = MT_HORN_ATTACK;
        if (pk.level <= 39)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level <= 46)
            DisponibleMoves[4] = MT_SPIKE_CANNON;
        if (pk.level <= 53)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 138: //Omastar
        DisponibleMoves[0] = MT_WATER_GUN;
        DisponibleMoves[1] = MT_WITHDRAW;
        DisponibleMoves[2] = MT_HORN_ATTACK;
        if (pk.level <= 39)
            DisponibleMoves[3] = MT_LEER;
        if (pk.level <= 44)
            DisponibleMoves[4] = MT_SPIKE_CANNON;
        if (pk.level <= 49)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 139: //Kabuto
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_HARDEN;
        if (pk.level <= 34)
            DisponibleMoves[2] = MT_ABSORB;
        if (pk.level <= 39)
            DisponibleMoves[3] = MT_SLASH;
        if (pk.level <= 44)
            DisponibleMoves[4] = MT_LEER;
        if (pk.level <= 49)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 140: //Kabutops
        DisponibleMoves[0] = MT_SCRATCH;
        DisponibleMoves[1] = MT_HARDEN;
        DisponibleMoves[2] = MT_ABSORB;
        if (pk.level <= 39)
            DisponibleMoves[3] = MT_SLASH;
        if (pk.level <= 46)
            DisponibleMoves[4] = MT_LEER;
        if (pk.level <= 53)
            DisponibleMoves[5] = MT_HYDRO_PUMP;
        break;
    case 141: //Aerodactyl
        DisponibleMoves[0] = MT_WING_ATTACK;
        DisponibleMoves[1] = MT_AGILITY;
        if (pk.level <= 33)
            DisponibleMoves[2] = MT_SUPERSONIC;
        if (pk.level <= 38)
            DisponibleMoves[3] = MT_BITE;
        if (pk.level <= 45)
            DisponibleMoves[4] = MT_TAKE_DOWN;
        if (pk.level <= 54)
            DisponibleMoves[5] = MT_HYPER_BEAM;
        break;
    case 142: //Snorlax
        DisponibleMoves[0] = MT_HEADBUTT;
        DisponibleMoves[1] = MT_AMNESIA;
        DisponibleMoves[2] = MT_REST;
        if (pk.level <= 35)
            DisponibleMoves[3] = MT_BODY_SLAM;
        if (pk.level <= 41)
            DisponibleMoves[4] = MT_HARDEN;
        if (pk.level <= 48)
            DisponibleMoves[5] = MT_DOUBLE_EDGE;
        if (pk.level <= 56)
            DisponibleMoves[6] = MT_HYPER_BEAM;
        break;
    case 143: //Articuno
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[2] = MT_BLIZZARD;
        if (pk.level >= 55)
            DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 60)
            DisponibleMoves[4] = MT_MIST;
        break;
    case 144: //Zapdos
        DisponibleMoves[0] = MT_THUNDER_SHOCK;
        DisponibleMoves[1] = MT_DRILL_PECK;
        if (pk.level >= 51)
            DisponibleMoves[2] = MT_THUNDER;
        if (pk.level >= 55)
            DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 60)
            DisponibleMoves[4] = MT_LIGHT_SCREEN;
        break;
    case 145: //Moltres
        DisponibleMoves[0] = MT_PECK;
        DisponibleMoves[1] = MT_FIRE_SPIN;
        if (pk.level >= 51)
            DisponibleMoves[2] = MT_LEER;
        if (pk.level >= 55)
            DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 60)
            DisponibleMoves[4] = MT_SKY_ATTACK;
        break;
    case 146: //Dratini
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_THUNDER_WAVE;
        if (pk.level >= 20)
            DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 35)
            DisponibleMoves[4] = MT_SLAM;
        if (pk.level >= 45)
            DisponibleMoves[5] = MT_DRAGON_RAGE;
        if (pk.level >= 60)
            DisponibleMoves[6] = MT_HYPER_BEAM;
        break;
    case 147: //Dragonair
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_THUNDER_WAVE;
        if (pk.level >= 20)
            DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 35)
            DisponibleMoves[4] = MT_SLAM;
        if (pk.level >= 45)
            DisponibleMoves[5] = MT_DRAGON_RAGE;
        if (pk.level >= 60)
            DisponibleMoves[6] = MT_HYPER_BEAM;
        break;
    case 148: //Dragonite
        DisponibleMoves[0] = MT_WRAP;
        DisponibleMoves[1] = MT_LEER;
        DisponibleMoves[2] = MT_THUNDER_WAVE;
        DisponibleMoves[3] = MT_AGILITY;
        if (pk.level >= 35)
            DisponibleMoves[4] = MT_SLAM;
        if (pk.level >= 45)
            DisponibleMoves[5] = MT_DRAGON_RAGE;
        if (pk.level >= 60)
            DisponibleMoves[6] = MT_HYPER_BEAM;
        break;
    case 149: //Mewtwo
        DisponibleMoves[0] = MT_CONFUSION;
        DisponibleMoves[1] = MT_DISABLE;
        DisponibleMoves[2] = MT_SWIFT;
        DisponibleMoves[3] = MT_PSYCHIC;
        if (pk.level >= 63)
            DisponibleMoves[4] = MT_BARRIER;
        if (pk.level >= 66)
            DisponibleMoves[5] = MT_PSYCHIC;
        if (pk.level >= 70)
            DisponibleMoves[6] = MT_RECOVER;
        if (pk.level >= 75)
            DisponibleMoves[7] = MT_MIST;
        if (pk.level >= 81)
            DisponibleMoves[8] = MT_AMNESIA;
        break;
    case 150: //Mew
        DisponibleMoves[0] = MT_POUND;
        if (pk.level >= 10)
            DisponibleMoves[1] = MT_TRANSFORM;
        if (pk.level >= 20)
            DisponibleMoves[2] = MT_MEGA_PUNCH;
        if (pk.level >= 30)
            DisponibleMoves[3] = MT_METRONOME;
        if (pk.level >= 40)
            DisponibleMoves[4] = MT_PSYCHIC;
        break;
    default:
        DisponibleMoves[0] = MT_WATER_GUN;
        DisponibleMoves[1] = MT_SKY_ATTACK;
        break;
    }
    move = getMoveById((MoveId)getMoveIdByDisponible(pk));
    return move;
}

Pokemon defineMoves(Pokemon pk)
{

    Move *move1 = getMoveByPk(pk);
    for (int i = 0; i < 50; i++)
    {
        move1 = getMoveByPk(pk);
        if (move1->power != 0)
            break;
    }

    Move *move2;
    Move *move3;
    Move *move4;
    for (int i = 0; i < 50; i++)
    {
        move2 = getMoveByPk(pk);
        if (move2->id != move1->id)
            break;
    }
    for (int i = 0; i < 50; i++)
    {
        move3 = getMoveByPk(pk);
        if (move2->id != move3->id && move1->id != move3->id)
            break;
    }
    for (int i = 0; i < 50; i++)
    {
        move4 = getMoveByPk(pk);
        if (move2->id != move4->id && move1->id != move4->id && move3->id != move4->id && move4->id != MT_UNDEFINE)
            break;
    }
    while (move1->id == MT_UNDEFINE)
    {
        move1 = getMoveByPk(pk);
    }

    if (move1->id == move2->id || move2->id == MT_UNDEFINE)
    {
        move2 = 0;
        pk.moveSlots[0] = createMoveSlot(move1, pk);
        pk.moveCount = 1;
    }
    else if (move2->id == move3->id || move1->id == move3->id || move3->id == MT_UNDEFINE)
    {
        move3 = 0;
        pk.moveSlots[0] = createMoveSlot(move1, pk);
        pk.moveSlots[1] = createMoveSlot(move2, pk);
        pk.moveCount = 2;
    }
    else if (move3->id == move4->id || move2->id == move4->id || move1->id == move4->id || move4->id == MT_UNDEFINE)
    {
        move4 = 0;
        pk.moveSlots[0] = createMoveSlot(move1, pk);
        pk.moveSlots[1] = createMoveSlot(move2, pk);
        pk.moveSlots[2] = createMoveSlot(move3, pk);
        pk.moveCount = 3;
    }
    else
    {
        pk.moveSlots[0] = createMoveSlot(move1, pk);
        pk.moveSlots[1] = createMoveSlot(move2, pk);
        pk.moveSlots[2] = createMoveSlot(move3, pk);
        pk.moveSlots[3] = createMoveSlot(move4, pk);
        pk.moveCount = 4;
    }
    return pk;
}

Pokemon createWildPkByRoad(int road)
{
    srand(time(NULL));
    Pokemon pkWild;
    int random;
    random = (rand() % 100) + 1;
    switch (road)
    {
    case 1: //Kanto road 1
        if (random <= 70)
        {
            pkWild = createPokemon(PK_PIDGEY, (rand() % 5) + 3,WILD); //START +1
            return pkWild;
        } //end - start
        else
            pkWild = createPokemon(PK_RATTATA, (rand() % 2) + 3,WILD);
        return pkWild;
        break;
    case 2: //Kanto road 2
        if (random <= 15)
        {
            pkWild = createPokemon(PK_WEEDLE, (rand() % 2) + 4,WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            pkWild = createPokemon(PK_PIDGEY, (rand() % 2) + 4,WILD);
            return pkWild;
        }
        else
        {
            pkWild = createPokemon(PK_RATTATA, (rand() % 3) + 3,WILD);
            return pkWild;
        }
        break;
    case 3: //Kanto road 3
        if (random <= 45)
        {
            pkWild = createPokemon(PK_PIDGEY, (rand() % 2) + 7,WILD);
            return pkWild;
        }
        else if (random <= 90)
        {
            pkWild = createPokemon(PK_SPEAROW, (rand() % 3) + 6,WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {3, 5, 7};
            pkWild = createPokemon(PK_JIGGLYPUFF, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        break;
    case 4: //Kanto road 4
        if (random <= 40)
        {
            int levelDisponible[3] = {8, 10, 12};
            pkWild = createPokemon(PK_RATTATA, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {8, 10, 12};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[4] = {6, 8, 10, 12};
            pkWild = createPokemon(PK_EKANS, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
        break;
    case 5: //Kanto road 5
        if (random <= 40)
        {
            int levelDisponible[3] = {13, 15, 16};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {13, 15, 16};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[4] = {10, 12, 14, 16};
            pkWild = createPokemon(PK_MANKEY, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
    case 6: //Kanto road 6
        if (random <= 40)
        {
            int levelDisponible[3] = {13, 15, 16};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {13, 15, 16};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[4] = {10, 12, 14, 16};
            pkWild = createPokemon(PK_MANKEY, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
    case 7: //Kanto road 7
        if (random <= 30)
        {
            int levelDisponible[2] = {19, 22};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[2] = {19, 20};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 90)
        {
            int levelDisponible[2] = {17, 20};
            pkWild = createPokemon(PK_MANKEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[2] = {18, 20};
            pkWild = createPokemon(PK_GROWLITHE, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
    case 8:
        if (random <= 35)
        {
            int levelDisponible[2] = {18, 20};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 55)
        {
            int levelDisponible[2] = {17, 19};
            pkWild = createPokemon(PK_EKANS, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 80)
        {
            int levelDisponible[2] = {18, 20};
            pkWild = createPokemon(PK_MANKEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[2] = {15, 20};
            pkWild = createPokemon(PK_GROWLITHE, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
    case 9:
        if (random <= 40)
        {
            int levelDisponible[3] = {14, 16, 17};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {13, 16, 17};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[4] = {11, 13, 15, 17};
            pkWild = createPokemon(PK_EKANS, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
    case 10:
        if (random <= 30)
        {
            int levelDisponible[3] = {13, 16, 17};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 55)
        {
            int levelDisponible[4] = {11, 13, 15, 17};
            pkWild = createPokemon(PK_EKANS, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {14, 16, 17};
            pkWild = createPokemon(PK_VOLTORB, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 11:
        if (random <= 35)
        {
            int levelDisponible[3] = {13, 15, 17};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {12, 14, 15};
            pkWild = createPokemon(PK_EKANS, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[4] = {9, 11, 13, 15};
            pkWild = createPokemon(PK_DROWZEE, levelDisponible[rand() % 4],WILD);
            return pkWild;
        }
    case 12:
        if (random <= 35)
        {
            int levelDisponible[3] = {23, 25, 27};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {22, 24, 26};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 80)
        {
            int levelDisponible[2] = {28, 30};
            pkWild = createPokemon(PK_GLOOM, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[2] = {24, 26};
            pkWild = createPokemon(PK_VENONAT, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
    case 13:
        if (random <= 30)
        {
            int levelDisponible[2] = {25, 27};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 70)
        {
            int levelDisponible[3] = {22, 24, 26};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[2] = {28, 30};
            pkWild = createPokemon(PK_GLOOM, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 95)
        {
            int levelDisponible[2] = {24, 26};
            pkWild = createPokemon(PK_VENONAT, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            pkWild = createPokemon(PK_DITTO, 25,WILD);
            return pkWild;
        }
    case 14: //
        if (random <= 15)
        {
            pkWild = createPokemon(PK_PIDGEY, 26,WILD);
            return pkWild;
        }
        else if (random <= 20)
        {
            int levelDisponible[2] = {28, 30};
            pkWild = createPokemon(PK_PIDGEOTTO, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[3] = {22, 24, 26};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 65)
        {
            pkWild = createPokemon(PK_GLOOM, 30,WILD);
            return pkWild;
        }
        else if (random <= 85)
        {
            int levelDisponible[2] = {24, 26};
            pkWild = createPokemon(PK_VENONAT, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            pkWild = createPokemon(PK_DITTO, 23,WILD);
            return pkWild;
        }
    case 15: //
        if (random <= 15)
        {
            pkWild = createPokemon(PK_PIDGEY, 23,WILD);
            return pkWild;
        }
        else if (random <= 20)
        {
            int levelDisponible[2] = {28, 30};
            pkWild = createPokemon(PK_PIDGEOTTO, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[3] = {22, 24, 26};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 65)
        {
            pkWild = createPokemon(PK_GLOOM, 30,WILD);
            return pkWild;
        }
        else if (random <= 85)
        {
            int levelDisponible[2] = {26, 28};
            pkWild = createPokemon(PK_VENONAT, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            pkWild = createPokemon(PK_DITTO, 26,WILD);
            return pkWild;
        }
    case 16:
        if (random <= 30)
        {
            int levelDisponible[3] = {18, 20, 22};
            pkWild = createPokemon(PK_RATTATA, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 35)
        {
            int levelDisponible[2] = {23, 25};
            pkWild = createPokemon(PK_RATICATE, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {20, 22};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {18, 20, 22};
            pkWild = createPokemon(PK_DODUO, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 17:
        if (random <= 30)
        {
            int levelDisponible[3] = {25, 27, 29};
            pkWild = createPokemon(PK_RATICATE, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 70)
        {
            int levelDisponible[2] = {20, 22};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {25, 27};
            pkWild = createPokemon(PK_FEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {24, 26, 28};
            pkWild = createPokemon(PK_DODUO, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 18:
        if (random <= 20)
        {
            int levelDisponible[2] = {25, 29};
            pkWild = createPokemon(PK_RATICATE, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[2] = {20, 22};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[3] = {25, 27, 29};
            pkWild = createPokemon(PK_FEAROW, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {24, 26, 28};
            pkWild = createPokemon(PK_DODUO, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 20:
    case 19:
        if (random <= 75)
        {
            int levelDisponible[7] = {5, 10, 15, 20, 30, 35, 40};
            pkWild = createPokemon(PK_TENTACOOL, levelDisponible[rand() % 7],WILD);
            return pkWild;
        }
    case 21:
        if (random <= 25)
        {
            int levelDisponible[2] = {21, 23};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 40)
        {
            int levelDisponible[2] = {30, 32};
            pkWild = createPokemon(PK_PIDGEOTTO, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 75)
        {
            int levelDisponible[2] = {21, 23};
            pkWild = createPokemon(PK_RATTATA, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 90)
        {
            pkWild = createPokemon(PK_RATICATE, 30,WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {28, 30, 32};
            pkWild = createPokemon(PK_TANGELA, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 22:
        if (random <= 45)
        {
            int levelDisponible[3] = {2, 3, 4};
            pkWild = createPokemon(PK_RATTATA, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 55)
        {
            int levelDisponible[2] = {3, 5};
            pkWild = createPokemon(PK_SPEAROW, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[2] = {3, 4};
            pkWild = createPokemon(PK_NIDORANf, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {2, 3, 4};
            pkWild = createPokemon(PK_NIDORANf, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 23:
        if (random <= 15)
        {
            pkWild = createPokemon(PK_SPEAROW, 26,WILD);
            return pkWild;
        }
        else if (random <= 40)
        {
            int levelDisponible[3] = {38, 41, 43};
            pkWild = createPokemon(PK_FEAROW, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else if (random <= 65)
        {
            pkWild = createPokemon(PK_EKANS, 26,WILD);
            return pkWild;
        }
        else if (random <= 70)
        {
            pkWild = createPokemon(PK_ARBOK, 41,WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {33, 38, 43};
            pkWild = createPokemon(PK_DITTO, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 24:
        if (random <= 20)
        {
            pkWild = createPokemon(PK_WEEDLE, 7,WILD);
            return pkWild;
        }
        else if (random <= 40)
        {
            pkWild = createPokemon(PK_KAKUNA, 8,WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            int levelDisponible[2] = {12, 13};
            pkWild = createPokemon(PK_PIDGEY, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
        else if (random <= 85)
        {
            int levelDisponible[3] = {12, 13, 14};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[3] = {8, 10, 12};
            pkWild = createPokemon(PK_ABRA, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
    case 25:
        if (random <= 1)
        {
            pkWild = createPokemon(PK_CATERPIE, 8,WILD);
            return pkWild;
        }
        else if (random <= 5)
        {
            pkWild = createPokemon(PK_METAPOD, 7,WILD);
            return pkWild;
        }
        else if (random <= 25)
        {
            pkWild = createPokemon(PK_WEEDLE, 8,WILD);
            return pkWild;
        }
        else if (random <= 45)
        {
            pkWild = createPokemon(PK_KAKUNA, 9,WILD);
            return pkWild;
        }
        else if (random <= 60)
        {
            pkWild = createPokemon(PK_PIDGEY, 13,WILD);
            return pkWild;
        }
        else if (random <= 85)
        {
            int levelDisponible[3] = {12, 13, 14};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 3],WILD);
            return pkWild;
        }
        else
        {
            int levelDisponible[2] = {12, 14};
            pkWild = createPokemon(PK_ODDISH, levelDisponible[rand() % 2],WILD);
            return pkWild;
        }
    default:
        break;
    }
}

void *catchPokemon(Player *player, Pokemon wild)
{
    if (player->pokemonCount != 6)
    {
        for (int id = 0; id < PokemonMax; ++id)
        {
            if (player->pokemon[id].MaxHP == NULL)
            {
                // printWait();
                player->pokemon[id] = wild; //affect to empty slot wild Pokemon
                player->pokemonCount += 1;
                // printf("All right ! ");
                //getColorByType(wild.type1);
                // printf("%s" reset " was caught !", wild.name);
                // fgetc(stdin);
                // system("clear");
                break;
            }
            //Passe un tour
        }
    }

    //If no then go to PC
}

int pokemonCatch(Pokeball pb, Pokemon wild)
{
    int max, ball;
    if (pb.type == P_POKEBALL)
    {
        max = 256;
        ball = 12;
    }
    else if (pb.type == P_GREATBALL)
    {
        max = 201;
        ball = 8;
    }
    else if (pb.type == P_MASTERBALL)
    {
        return 1;
    }
    else
    {
        ball = 12;
        max = 151;
    }
    //^Define Ball Type
    int N = (rand() % max);
    if ((wild.status.id == S_SLEEP || wild.status.id == S_FREEZE) && N < 25)
        return 1;
    else if ((wild.status.id == S_PARALYSIS || wild.status.id == S_BURN || wild.status.id == S_POISON) && N < 12)
        return 1;
    else
    {
        int M = (rand() % 256);
        float f = (wild.MaxHP * 255 * 4) / (wild.currentHP * ball);
        if ((int)f >= M)
            return 1;
        else
            return 0;
    }
}

//gcc -g tests/test_Pokemon_stats.c src/moves.c src/fight.c src/rules.c src/species.c -lm && ./a.out