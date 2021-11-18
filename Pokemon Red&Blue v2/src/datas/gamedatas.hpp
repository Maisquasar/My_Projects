#pragma once
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "player.hpp"
#include "../tools/keyboardHolder.hpp"
#include "../tools/text.hpp"
#include "../../third_party/include/raylib.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

typedef struct Screen
{
    int width;
    int height;
}Screen;

typedef enum Action
{
    A_NONE,
    A_ATTACK,
    A_PKMN,
    A_ITEM,
    A_RUN
}Action;
typedef enum renderType
{
    M_MAIN,
    M_FIGHT,
    M_PKMN,
}renderType;


typedef struct GameDatas
{
    Screen screen;
    renderType render;
    Action action;
    Player player;
    Pokemon wild;
    Inputs inputs;
    int messageId;
    int currentPK;
    int frameCounter;
    Texture2D PkSprites[151];
}GameDatas;