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
        in->enemy[i].pos = Vector2{5, 609};
        in->enemy[i].alive = false;
        in->enemy[i].dead = false;
        in->enemy[i].type = type;
        in->enemy[i].rot = 90;
        in->enemy[i].dir = 0;
        in->enemy[i].tmpdir = 0;
        in->enemy[i].spawnCooldoown = in->delaySpawn;
        in->delaySpawn += 10;
        switch (in->enemy[i].type)
        {
        case SLOW:
            in->enemy[i].speed = 1;
            in->enemy[i].life = 100 + ((in->rounds - 1) * 10);
            in->enemy[i].coinsToDeliver = 40 - (in->rounds - 1 * 5);
            break;
        case FAST:
            in->enemy[i].speed = 2;
            in->enemy[i].life = 20 + ((in->rounds - 1) * 5);
            in->enemy[i].coinsToDeliver = 20 - (in->rounds - 1 * 2);
            break;
        case STRONG:
            in->enemy[i].speed = 0.75;
            in->enemy[i].life = 250 + ((in->rounds - 1) * 25);
            in->enemy[i].coinsToDeliver = 100 - (in->rounds - 1 * 10);
            break;
        case BOSS:
            in->enemy[i].speed = 0.5;
            in->enemy[i].life = 3000 + ((in->rounds - 1) * 50);
            in->enemy[i].coinsToDeliver = 500 - (in->rounds - 1 * 20);
            in->delaySpawn += 500;
            break;
        default:
            break;
        }
        in->enemy[i].maxLife = in->enemy[i].life;
        in->enemy[i].MaxCoinsToDeliver = in->enemy[i].coinsToDeliver;
    }
    in->enemiesCount += Number;
    in->delaySpawn = 0;
}