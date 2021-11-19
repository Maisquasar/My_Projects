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
                in->enemy[i].tmpdir = 0;//NORTH
                in->enemy[i].rot = -90;//EAST
                in->enemy[i].pos.x += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == ']')
            {
                in->enemy[i].rot = 180;//SOUTH
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '[')
            {
                in->enemy[i].rot = -90;//EAST
                in->enemy[i].pos.y += in->enemy[i].speed;
                in->enemy[i].pos.x += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '|')
            {
                in->enemy[i].tmpdir = 180;//SOUTH
                if (in->enemy[i].rot == 0)//NORTH
                    in->enemy[i].pos.y += in->enemy[i].speed;
                else//SOUTH
                    in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '{')
            {
                in->enemy[i].rot = -90;//EAST
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y -= in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '}')
            {
                in->enemy[i].rot = 0;//NORTH
                in->enemy[i].pos.x += in->enemy[i].speed;
                in->enemy[i].pos.y += in->enemy[i].speed;
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '>')
            {
                if (in->enemy[i].tmpdir == 180)//SOUTH
                    in->enemy[i].tmpdir = GetRandomValue(1, 2);
                if (in->enemy[i].tmpdir == 1)
                {
                    in->enemy[i].rot = -90;//EAST
                    in->enemy[i].pos.x += in->enemy[i].speed;
                    in->enemy[i].pos.y += in->enemy[i].speed;
                }
                else
                {
                    if (in->enemy[i].rot == 0)//NORTH
                        in->enemy[i].pos.y += in->enemy[i].speed;
                    else//SOUTH
                        in->enemy[i].pos.y -= in->enemy[i].speed;
                }
            }
            else if (map1[((int)in->enemy[i].pos.y / 64)][((int)in->enemy[i].pos.x / 64)] == '<')
            {
                if (in->enemy[i].tmpdir == 0)//NORTH
                    in->enemy[i].tmpdir = GetRandomValue(1, 2);
                if (in->enemy[i].rot == -90 || in->enemy[i].rot == 360 + 180)//EAST || NORTH
                {
                    in->enemy[i].rot = 360+180;
                    in->enemy[i].pos.x += in->enemy[i].speed;
                    in->enemy[i].pos.y -= in->enemy[i].speed;
                }
                if (in->enemy[i].rot == 180)//SOUTH
                {
                    in->enemy[i].pos.y -= in->enemy[i].speed;
                }
            }
            else
            {
                int *tmp;
                int test = *tmp;
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
        if (in->enemy[i].life <= 0 && in->enemy[i].dead == false)
        {
            in->player.coins += in->enemy[i].coinsToDeliver;
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

Vec2D getFurtherEnemies(GameDatas *in, Vec2D targetPos)
{
    Vec2D tmp2 = createWith(0, 0);
    for (int i = 0; i < in->enemiesCount; ++i)
    {
        if (in->enemy[i].spawnCooldoown <= 0 && !in->enemy[i].dead)
        {
            Vec2D tmp = sub(V2toV(in->enemy[i].pos), targetPos);
            int temp = getLength(tmp);
            if (tmp2.x == 0 || getLength(tmp2) < temp)
            {
                tmp2 = tmp;
            }
        }
    }
    return tmp2;
}

void handleTowers(GameDatas *in)
{
    if (!in->btnState[10]) //If not in pause
    {
        for (int i = 0; i < in->player.numberOfTowers; i++)
        {
            if (in->player.tower[i].type == BASIC || in->player.tower[i].type == ADVANCED)
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
                    }
                    else
                        in->player.tower[i].shootCooldown -= 1;
                }
                else
                    in->player.tower[i].shootCooldown = 0;
            }
            else
            {
                Vec2D pPos = getNearestEnemies(in, V2toV(in->player.tower[i].pos));
                if (getLength(pPos) <= in->player.tower[i].radius)
                {
                    if (in->player.tower[i].shootCooldown <= 15)
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
                    }
                    if (in->player.tower[i].shootCooldown == 0)
                    {
                        in->player.tower[i].shootCooldown = 180;
                        shootRocket(in, in->player.tower[i], V2toV(in->enemy[getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos))].pos), getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos)));
                        if (in->player.tower[i].type == ULTIMATE)
                            shootRocket(in, in->player.tower[i], V2toV(in->enemy[getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos))].pos), getNearestEnemieIndex(in, V2toV(in->player.tower[i].pos)));
                    }
                    else
                        in->player.tower[i].shootCooldown -= 1;
                }
                else
                    in->player.tower[i].shootCooldown -= 1;
            }
            if (in->player.tower[i].shootCooldown <= 0)
                in->player.tower[i].shootCooldown = 0;
        }
    }
}

void shootRocket(GameDatas *in, Tower t, Vec2D PPos, int index)
{
    createExplosion(in, VtoV2(PPos));
    for (int i = 0; i < in->enemiesCount; i++)
    {
        // float distance = getDistance(PPos, V2toV(in->enemy[i].pos));
        float ePos = getDistance(V2toV(in->enemy[i].pos), PPos);
        if (ePos <= EXPLOSION_RADIUS)
        {
            int damage = t.damage - (ePos / (EXPLOSION_RADIUS / 2));
            in->enemy[i].life -= damage;
        }
    }
}
void createTower(GameDatas *in, int type, int x, int y)
{
    if (type == 1)
        type = ELITE;
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
        tmp.upgradeCost = 450;
        break;
    case ELITE:
        tmp.radius = 200;
        tmp.damage = 20;
        tmp.shootCooldown = 0;
        tmp.price = 500;
        tmp.upgradeCost = 700;
    default:
        break;
    }
    in->player.tower[tmp.index] = tmp;
}

Tower upgradeTower(GameDatas *in, Tower tmp)
{
    if (tmp.type == BASIC)
    {
        in->player.coins -= 450;
        tmp.radius = 200;
        tmp.damage = 10;
        tmp.shootCooldown = 0;
        tmp.type = ADVANCED;
    }
    else if (tmp.type == ELITE)
    {
        in->player.coins -= 700;
        tmp.radius = 250;
        tmp.damage = 20;
        tmp.shootCooldown = 0;
        tmp.type = ULTIMATE;
    }
    return tmp;
}

void initTower(GameDatas *in)
{
    for (int i = 0; i < 1000; i++)
    {
        in->player.tower[i].pos = {0, 0};
    }
}