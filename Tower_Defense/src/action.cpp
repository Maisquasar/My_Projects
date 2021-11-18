#include "action.hpp"

void initPlayer(GameDatas *in)
{
    in->player.numberOfTowers = 0;
    in->towerRec[0] = {1810, 120, 64, 64};
    in->towerRec[1] = {1810, 220, 64, 64};
    for (int i = 0; i < 2; i++)
        in->drag[i] = false;
    in->player.coins = 200;
    in->rounds = 1;
}

/* void initEnemies(GameDatas *in)
{
    in->delaySpawn = 200;
    for (int i = 0; i < in->enemiesCount; i++)
    {
    }
} */
void handleEnemies(GameDatas *in)
{
    int NumberOfEnemies = in->enemiesCount;
    for (int i = 0; i < in->enemiesCount; i++)
    {
        if (in->enemy[i].alive && !in->btnState[10] && !in->enemy[i].dead)
        {

            if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '=')
            {
                in->enemy[i].tmpdir = 0;
                in->enemy[i].rot = -90;
                in->enemy[i].pos.x += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == ']')
            {
                in->enemy[i].rot = 180;
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '[')
            {
                in->enemy[i].rot = -90;
                in->enemy[i].pos.y += in->enemy[i].speed;
                in->enemy[i].pos.x += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '|')
            {
                in->enemy[i].tmpdir = 180;
                if (in->enemy[i].rot == 0)
                    in->enemy[i].pos.y += in->enemy[i].speed;
                else
                    in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '{')
            {
                in->enemy[i].rot = -90;
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '}')
            {
                in->enemy[i].rot = 0;
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '>')
            {
                if (in->enemy[i].tmpdir == 180)
                    in->enemy[i].tmpdir = GetRandomValue(1, 2);
                if (in->enemy[i].tmpdir == 1)
                {
                    in->enemy[i].rot = -90;
                    in->enemy[i].pos.x += in->enemy[i].speed;
                    in->enemy[i].pos.y += in->enemy[i].speed;
                }
                else
                {
                    if (in->enemy[i].rot == 0)
                        in->enemy[i].pos.y += in->enemy[i].speed;
                    else
                        in->enemy[i].pos.y -= in->enemy[i].speed;
                }
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '<')
            {
                if (in->enemy[i].tmpdir == 0)
                    in->enemy[i].tmpdir = GetRandomValue(1, 2);
                if (in->enemy[i].rot == -90 || in->enemy[i].rot == 360)
                {
                    in->enemy[i].rot = 360;
                    in->enemy[i].pos.x += in->enemy[i].speed;
                    in->enemy[i].pos.y -= in->enemy[i].speed;
                }
                if (in->enemy[i].rot == 180)
                {
                    in->enemy[i].pos.y -= in->enemy[i].speed;
                }
            }
            if (in->enemy[i].life == 0)
                in->enemy[i].alive = false;
        }
        else
        {
            in->enemy[i].spawnCooldoown -= 1;
            if (in->enemy[i].spawnCooldoown == 0)
                in->enemy[i].alive = true;
        }
        if (in->enemy[i].life <= 0)
        {
            in->enemy[i].alive = false;
            in->enemy[i].dead = true;
        }
        if (!in->enemy[i].alive && in->enemy[i].spawnCooldoown <= 0)
            NumberOfEnemies -= 1;
    }
    if (NumberOfEnemies <= 0)
    {
        in->rounds += 1;
        in->enemiesCount = 0;
        getRounds(in);
    }
}

Vec2D getNearestEnemies(GameDatas *in, Vec2D targetPos) //Detect the NearestPlayer
{
    Vec2D tmp2 = createWith(0, 0);
    for (int i = 0; i < in->enemiesCount; ++i)
    {
        if (in->enemy[i].spawnCooldoown <= 0 && !in->enemy[i].dead)
        {
            Vec2D tmp = sub(V2toV(in->enemy[i].pos), targetPos);
            int temp = getLength(tmp);
            if (tmp2.x == 0 || getLength(tmp2) > temp)
            {
                tmp2 = tmp;
            }
        }
    }
    return tmp2;
}

int getNearestEnemieIndex(GameDatas *in, Vec2D targetPos) //Detect the NearestPlayer
{
    int tmp2 = 0;
    int index;
    for (int i = 0; i < in->enemiesCount; ++i)
    {
        if (!in->enemy[i].dead)
        {
            Vec2D tmp = sub(V2toV(in->enemy[i].pos), targetPos);
            int temp = getLength(tmp);
            if (tmp2 == 0 || tmp2 > temp)
            {
                tmp2 = temp;
                index = i;
            }
        }
    }
    return index;
}

Vector2 VtoV2(Vec2D vec)
{
    Vector2 v;
    v.x = vec.x;
    v.y = vec.y;
    return v;
}

Vec2D V2toV(Vector2 vec)
{
    Vec2D v;
    v.x = vec.x;
    v.y = vec.y;
    return v;
}

void handleTowers(GameDatas *in)
{
    if (!in->btnState[10]) //If not in pause
    {
        for (int i = 0; i < in->player.numberOfTowers; i++)
        {
            Vec2D pPos = getNearestEnemies(in, V2toV(in->player.tower[i].pos));
            if (getLength(pPos) <= in->player.tower[i].radius)
            {
                float dir;
                if (pPos.x == 0)
                {
                    if (pPos.y > 0)
                        dir = 90;
                    else
                        dir = -90;
                }
                else
                {
                    dir = (atanf(pPos.y / pPos.x) / PI * 180);
                    if (pPos.x < 0)
                        dir += 180;
                }
                in->player.tower[i].rot = dir + 90;
                if (in->player.tower[i].shootCooldown == 0)
                {
                    in->player.tower[i].shootCooldown = in->player.tower[i].type == BASIC ? 30 : 15;
                    in->enemy[getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos))].life -= in->player.tower[i].damage;
                    if (in->enemy[getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos))].life <= 0)
                        in->player.coins += in->enemy[getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos))].coinsToDeliver;
                }
                else
                    in->player.tower[i].shootCooldown -= 1;
            }
            else
                in->player.tower[i].shootCooldown = 0;
        }
    }
}

void createTower(GameDatas *in, int type, int x, int y)
{
    in->player.numberOfTowers += 1;
    Tower tmp;
    tmp.index = in->player.numberOfTowers - 1;
    tmp.pos.x = x + 32;
    tmp.pos.y = y + 32;
    tmp.rot = 0;
    tmp.overlay = false;
    in->player.tower[tmp.index] = tmp;
    tmp.type = (TowerType)type;
    switch (type)
    {
    case BASIC:
        tmp.radius = 150;
        tmp.damage = 10;
        tmp.shootCooldown = 30;
        break;
    case ADVANCED:
        tmp.radius = 200;
        tmp.damage = 10;
        tmp.shootCooldown = 15;
        break;
    default:
        break;
    }
    in->player.tower[tmp.index] = tmp;
}

void upgradeTower(GameDatas *in, int index)
{
    in->player.coins -= 450;
    Tower tmp = in->player.tower[index];
    tmp.radius = 200;
    tmp.damage = 10;
    tmp.shootCooldown = 15;
    tmp.type = ADVANCED;
    in->player.tower[index] = tmp;
}

void initTower(GameDatas *in)
{
    for (int i = 0; i < 1000; i++)
    {
        in->player.tower[i].pos = {0, 0};
    }
}