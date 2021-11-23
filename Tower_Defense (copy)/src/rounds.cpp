#include "rounds.hpp"

void getRounds(GameDatas *in)
{
    switch (in->rounds)
    {
    case 1:
        createEnemies(in, 5, FAST);
        createEnemies(in, 3, SLOW);
        break;
    case 2:
        createEnemies(in, 1, STRONG);
        createEnemies(in, 10, FAST);
        createEnemies(in, 10, SLOW);
        break;
    case 3:
        createEnemies(in, 3, STRONG);
        createEnemies(in, 20, FAST);
        createEnemies(in, 20, SLOW);
        break;
    case 4:
        createEnemies(in, 5, STRONG);
        createEnemies(in, 40, FAST);
        createEnemies(in, 40, SLOW);
        in->precEnemiesCount = in->enemiesCount;
        break;
    default:
        createEnemies(in, in->precEnemiesCount * 1 / 8, STRONG);
        createEnemies(in, in->precEnemiesCount, FAST);
        createEnemies(in, in->precEnemiesCount, SLOW);
        createEnemies(in, in->precEnemiesCount * 1 / 32, BOSS);
        in->precEnemiesCount = in->enemiesCount;
        break;
    }
}

void createEnemies(GameDatas *in, int Number, EnemyType type)
{
    Number++;
    for (int i = in->enemiesCount; i < in->enemiesCount + Number; i++)
    {
       /*  for (int y = 0; y < 17; y++)
        {
            if (in->maps[in->mapId][y][0] == '=')
                in->enemy[i].pos.y = (y * 64) + 32;
        } */
        
    }
    in->enemiesCount += Number;
    in->delaySpawn = 0;
}