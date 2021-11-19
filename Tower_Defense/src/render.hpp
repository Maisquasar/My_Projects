#pragma once
#include "datas.hpp"
#include "action.hpp"
#include "map.hpp"

void render(GameDatas*);
void renderSettings(GameDatas*);
void renderMain(GameDatas*);
void renderGame(GameDatas*);
void renderPause(GameDatas*);
void generateMap(GameDatas*);
void renderTower(GameDatas*);
void renderParticles(Particle *);
void renderEnemies(GameDatas*);