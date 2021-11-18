#pragma once
#include "../datas/gamedatas.hpp"
#include "../tools/text.hpp"
#include "../tools/textures.hpp"
#include "../../third_party/include/raylib.h"

const char message1[5][128] = {
    {"Wild %s appeared !"},
    {"Go ! %s !"},
    {""},
    {"%s used %s"},
    {"%s inflicted %.0f damages"}
};

void renderFight(GameDatas *in);
void renderAttack(GameDatas *in);
void renderPKMN(GameDatas *in);
void renderItem(GameDatas *in);
void renderList(GameDatas *in);