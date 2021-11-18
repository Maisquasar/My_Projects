//Program for Species of Pokemon
//Data don't change
#pragma once
#include "type.hpp"
#include <cstdlib>
#include <cstdio>

typedef enum ExperienceGrowth
{
    EG_FAST,
    EG_MEDIUM_SLOW,
    EG_MEDIUM_FAST,
    EG_SLOW
} ExperienceGrowth;

typedef enum SpeciesId : int 
{
    PK_BULBASAUR,
    PK_IVYSAUR,
    PK_VENUSAUR,
    PK_CHARMANDER,
    PK_CHARMELEON,
    PK_CHARIZARD,
    PK_SQUIRTLE,
    PK_WARTORTLE,
    PK_BLASTOISE,
    PK_CATERPIE,
    PK_METAPOD,
    PK_BUTTERFREE,
    PK_WEEDLE,
    PK_KAKUNA,
    PK_BEEDRILL,
    PK_PIDGEY,
    PK_PIDGEOTTO,
    PK_PIDGEOT,
    PK_RATTATA,
    PK_RATICATE,
    PK_SPEAROW,
    PK_FEAROW,
    PK_EKANS,
    PK_ARBOK,
    PK_PIKACHU,
    PK_RAICHU,
    PK_SANDSHREW,
    PK_SANDSLASH,
    PK_NIDORANf,
    PK_NIDORINA,
    PK_NIDOQUEEN,
    PK_NIDORANm,
    PK_NIDORINO,
    PK_NIDOKING,
    PK_CLEFAIRY,
    PK_CLEFABLE,
    PK_VULPIX,
    PK_NINETALES,
    PK_JIGGLYPUFF,
    PK_WIGGLYTUFF,
    PK_ZUBAT,
    PK_GOLBAT,
    PK_ODDISH,
    PK_GLOOM,
    PK_VILEPLUME,
    PK_PARAS,
    PK_PARASECT,
    PK_VENONAT,
    PK_VENOMOTH,
    PK_DIGLETT,
    PK_DUGTRIO,
    PK_MEOWTH,
    PK_PERSIAN,
    PK_PSYDUCK,
    PK_GOLDUCK,
    PK_MANKEY,
    PK_PRIMEAPE,
    PK_GROWLITHE,
    PK_ARCANINE,
    PK_POLIWAG,
    PK_POLIWHIRL,
    PK_POLIWRATH,
    PK_ABRA,
    PK_KADABRA,
    PK_ALAKAZAM,
    PK_MACHOP,
    PK_MACHOKE,
    PK_MACHAMP,
    PK_BELLSPROUT,
    PK_WEEPINBELL,
    PK_VICTREEBEL,
    PK_TENTACOOL,
    PK_TENTACRUEL,
    PK_GEODUDE,
    PK_GRAVELER,
    PK_GOLEM,
    PK_PONYTA,
    PK_RAPIDASH,
    PK_SLOWPOKE,
    PK_SLOWBRO,
    PK_MAGNEMITE,
    PK_MAGNETON,
    PK_FARFETCHD,
    PK_DODUO,
    PK_DODRIO,
    PK_SEEL,
    PK_DEWGONG,
    PK_GRIMER,
    PK_MUK,
    PK_SHELLDER,
    PK_CLOYSTER,
    PK_GASTLY,
    PK_HAUNTER,
    PK_GENGAR,
    PK_ONIX,
    PK_DROWZEE,
    PK_HYPNO,
    PK_KRABBY,
    PK_KINGLER,
    PK_VOLTORB,
    PK_ELECTRODE,
    PK_EXEGGCUTE,
    PK_EXEGGUTOR,
    PK_CUBONE,
    PK_MAROWAK,
    PK_HITMONLEE,
    PK_HITMONCHAN,
    PK_LICKITUNG,
    PK_KOFFING,
    PK_WEEZING,
    PK_RHYHORN,
    PK_RHYDON,
    PK_CHANSEY,
    PK_TANGELA,
    PK_KANGASKHAN,
    PK_HORSEA,
    PK_SEADRA,
    PK_GOLDEEN,
    PK_SEAKING,
    PK_STARYU,
    PK_STARMIE,
    PK_MRMIME,
    PK_SCYTHER,
    PK_JYNX,
    PK_ELECTABUZZ,
    PK_MAGMAR,
    PK_PINSIR,
    PK_TAUROS,
    PK_MAGIKARP,
    PK_GYARADOS,
    PK_LAPRAS,
    PK_DITTO,
    PK_EEVEE,
    PK_VAPOREON,
    PK_JOLTEON,
    PK_FLAREON,
    PK_PORYGON,
    PK_OMANYTE,
    PK_OMASTAR,
    PK_KABUTO,
    PK_KABUTOPS,
    PK_AERODACTYL,
    PK_SNORLAX,
    PK_ARTICUNO,
    PK_ZAPDOS,
    PK_MOLTRES,
    PK_DRATINI,
    PK_DRAGONAIR,
    PK_DRAGONITE,
    PK_MEWTWO,
    PK_MEW
}SpeciesId;

typedef struct Species
{
    SpeciesId pokedexId;
    char name[32];
    Type primaryType;
    Type secondaryType;
    ExperienceGrowth experienceGrowth;
    int healthStat;
    int defenseStat;
    int attackStat;
    int specialStat;
    int speedStat;
    int HealthEV;
    int attackEV;
    int defenseEV;
    int specialAttackEV;
    int specialDefenseEV;
    int speedEV;
    int catchRate;
    int ExperienceYield;
    char evolutionDetails[128];

} Species;

Species *getSpecies(int *count);
Species *getSpeciesByIndex(int index);