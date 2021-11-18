#include "mathHelper.hpp"
#include "datas.hpp"
#include "rounds.hpp"

void initPlayer(GameDatas* in);
void initEnemies(GameDatas* in);
void handleEnemies(GameDatas* in);
void handleTowers(GameDatas* in);
Vec2D getNearestPlayers(GameDatas *in, Vec2D targetPos); //Detect the NearestPlayer
Vec2D V2toV(Vector2 vec);
Vector2 VtoV2(Vec2D vec);
void upgradeTower(GameDatas *in, int index);
void createTower(GameDatas *in, int type, int x, int y);