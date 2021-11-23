#pragma once
#include "datas.hpp"
#include "action.hpp"
#include "map.hpp"
#include <iostream>
#include <fstream>

void render(GameDatas*);
void renderSettings(GameDatas*);
void renderMain(GameDatas*);
void renderCreate(GameDatas*);
void renderGame(GameDatas*);
void renderPause(GameDatas*);
void renderTower(GameDatas*);
void renderParticles(Particle *);
void renderEnemies(GameDatas*);