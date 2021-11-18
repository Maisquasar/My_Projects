//Program to print texts
#include "text.hpp"

void getColorByType(Type type)
{
    switch (type)
    {
    case T_NORMAL:
        printf(UWHT);
        break;
    case T_FIRE:
        printf(BHRED);
        break;
    case T_WATER:
        printf(BHBLU);
        break;
    case T_ELECTRIC:
        printf(BHYEL);
        break;
    case T_GRASS:
        printf(BHGRN);
        break;
    case T_ICE:
        printf(BHCYN);
        break;
    case T_FIGHTING:
        printf(MAG);
        break;
    case T_GROUND:
        printf(BHBLK);
        break;
    case T_FLYING:
        printf(BWHT);
        break;
    case T_POISON:
        printf(MAG);
        break;
    case T_PSYCHIC:
        printf(BMAG);
        break;
    case T_BUG:
        printf(GRN);
        break;
    case T_ROCK:
        printf(BBLK);
        break;
    case T_GHOST:
        printf(WHT);
        break;
    case T_DRAGON:
        printf(BHMAG);
        break;
    default:
        break;
    }
}

void printType(Type type)
{
    switch (type)
    {
    case T_NORMAL:
        printf("Normal");
        break;
    case T_FIRE:
        printf("Fire");
        break;
    case T_WATER:
        printf("Water");
        break;
    case T_ELECTRIC:
        printf("Electric");
        break;
    case T_GRASS:
        printf("Grass");
        break;
    case T_ICE:
        printf("Ice");
        break;
    case T_FIGHTING:
        printf("Fighting");
        break;
    case T_GROUND:
        printf("Ground");
        break;
    case T_FLYING:
        printf("Flying");
        break;
    case T_POISON:
        printf("Poison");
        break;
    case T_PSYCHIC:
        printf("Psychic");
        break;
    case T_BUG:
        printf("Bug");
        break;
    case T_ROCK:
        printf("Rock");
        break;
    case T_GHOST:
        printf("Ghost");
        break;
    case T_DRAGON:
        printf("Dragon");
        break;
    default:
        break;
    }
}

void printWait()
{
    system("clear");
    fgetc(stdin);
    printf(".");
    system("clear");
    fgetc(stdin);
    printf("..");
    system("clear");
    fgetc(stdin);
    printf("...\n");
    system("clear");
    system("clear");
}

