#pragma once
#include "mathHelper.hpp"
#include "datas.hpp"
#include "rounds.hpp"
#include "particle.hpp"

void initPlayer(GameDatas *);
void initEnemies(GameDatas *);
void handleEnemies(GameDatas *);
void handleTowers(GameDatas *);
Vec2D getNearestPlayers(GameDatas *, Vec2D); //Detect the NearestPlayer
Tower upgradeTower(GameDatas *, Tower);
void shootRocket(GameDatas *, Tower, Vec2D, int);
void createTower(GameDatas *, int, int, int);