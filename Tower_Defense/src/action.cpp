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
    int x = in->mapId;
    for (int i = 0; i < in->enemiesCount; i++)
    {
        Enemy temp = in->enemy[i];
        // bool east = false, west = false, north = false, south = false;
        temp.pos = VtoV2(add(V2toV(temp.pos), mul(createWith(cosf(toRadians(temp.rot + 90)), sinf(toRadians(temp.rot + 90))), temp.speed)));
        if (temp.alive && !in->btnState[10] && !temp.dead)
        { /* 
            if (((int)temp.pos.x / 64) + 1 < 31 && in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64) + 1] != 'd')
                east = true;
            if (((int)temp.pos.x / 64) - 1 > 0 && in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64) - 1] != 'd')
                west = true;
            if (((int)temp.pos.y / 64) + 1 < 17 && in->maps[x][((int)temp.pos.y / 64) + 1][((int)temp.pos.x / 64) + 1] != 'd')
                south = true;
            if (((int)temp.pos.y / 64) - 1 > 0 && in->maps[x][((int)temp.pos.y / 64) - 1][((int)temp.pos.x / 64) - 1] != 'd')
                north = true;
            if (north && )
                return;
 */

            if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '=')
            {
                temp.tmpdir = 0;
                if (temp.dir == 90)
                {
                    temp.dir = 90;
                    temp.rot = temp.dir;
                    temp.pos.x -= temp.speed;
                }
                else if (temp.dir == 270)
                {
                    temp.dir = 270;
                    temp.rot = temp.dir;
                    temp.pos.x += temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == ']') //left up
            {
                if (temp.dir == 0 || temp.dir == 90) //up
                {
                    temp.dir = 90;
                    temp.rot = temp.dir;
                    temp.pos.x -= temp.speed;
                    temp.pos.y += temp.speed;
                }
                else if (temp.dir == 270 || temp.dir == 180) //left
                {
                    temp.dir = 180;
                    temp.rot = temp.dir;
                    temp.pos.x += temp.speed;
                    temp.pos.y -= temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '[') //right up
            {
                if (temp.dir == 0 || temp.dir == 270) //up
                {
                    temp.dir = 270;
                    temp.tmpdir = 270;
                    temp.rot = temp.dir;
                    temp.pos.x += temp.speed;
                    temp.pos.y += temp.speed;
                }
                else if (temp.dir == 90 || temp.dir == 0) //right
                {
                    temp.dir = 0;
                    temp.rot = temp.dir;
                    temp.pos.x -= temp.speed;
                    temp.pos.y -= temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '|')
            {
                temp.tmpdir = 0;
                if (temp.dir == 0) //down
                {
                    temp.dir = 0;
                    temp.rot = temp.dir;
                    temp.pos.y += temp.speed;
                }
                else if (temp.dir == 180) //up
                {
                    temp.dir = 180;
                    temp.rot = temp.dir;
                    temp.pos.y -= temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '}') //Down left
            {
                if (temp.dir == 180 || temp.dir == 90) //Down
                {
                    temp.dir = 90;
                    temp.rot = temp.dir;
                    temp.pos.x -= temp.speed;
                    temp.pos.y -= temp.speed;
                }
                else if (temp.dir == 270 || temp.dir == 0) //left
                {
                    temp.dir = 0;
                    temp.rot = temp.dir;
                    temp.pos.x += temp.speed;
                    temp.pos.y += temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '{') //Down right
            {
                if (temp.dir == 180 || temp.tmpdir == 270) //Down
                {
                    temp.dir = 270;
                    temp.tmpdir = 270;
                    temp.rot = temp.dir;
                    temp.pos.x += temp.speed;
                    temp.pos.y -= temp.speed;
                }
                else if (temp.dir == 90 || temp.dir == 0) //Right
                {
                    temp.dir = 0;
                    temp.rot = temp.dir;
                    temp.pos.x -= temp.speed;
                    temp.pos.y += temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '>') //UP DOWN RIGHT
            {
                if (temp.rot == 90 || temp.tmpdir != 0)
                {
                    if (temp.tmpdir == 0)
                        temp.tmpdir = GetRandomValue(1, 2);
                    if (temp.tmpdir == 1)
                    {
                        temp.dir = 0;
                        temp.rot = 0;
                        temp.pos.x -= temp.speed;
                        temp.pos.y += temp.speed;
                    }
                    else
                    {
                        temp.dir = 180;
                        temp.rot = 180;
                        temp.pos.x -= temp.speed;
                        temp.pos.y -= temp.speed;
                    }
                }
                else if (temp.rot == 0)
                    temp.pos.y += temp.speed;
                else if (temp.rot == 180)
                    temp.pos.y -= temp.speed;
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '<')
            {
                if (temp.rot == 270 || temp.tmpdir != 0)
                {
                    if (temp.tmpdir == 0)
                        temp.tmpdir = GetRandomValue(1, 2);
                    if (temp.tmpdir == 1)
                    {
                        temp.dir = 180;
                        temp.rot = 180;
                        temp.pos.x += temp.speed;
                        temp.pos.y -= temp.speed;
                    }
                    else
                    {
                        temp.dir = 0;
                        temp.rot = 0;
                        temp.pos.x += temp.speed;
                        temp.pos.y += temp.speed;
                    }
                }
                else if (temp.rot == 0)
                    temp.pos.y += temp.speed;
                else if (temp.rot == 180)
                    temp.pos.y -= temp.speed;
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '^')
            {
                if (temp.rot == 0 || temp.tmpdir != 0)
                {
                    if (temp.tmpdir == 0)
                        temp.tmpdir = GetRandomValue(1, 2);
                    if (temp.tmpdir == 1)
                    {
                        temp.dir = 270;
                        temp.rot = 270;
                        temp.pos.x += temp.speed;
                        temp.pos.y += temp.speed;
                    }
                    else
                    {
                        temp.dir = 90;
                        temp.rot = 90;
                        temp.pos.x -= temp.speed;
                        temp.pos.y += temp.speed;
                    }
                }
                else if (temp.dir == 270)
                {
                    temp.pos.x += temp.speed;
                }
                else if (temp.rot == 90)
                    temp.pos.x -= temp.speed;
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == '+')
            {
                if (temp.rot == 270)
                {
                    temp.pos.x += temp.speed;
                }
                if (temp.rot == 90)
                {
                    temp.pos.x -= temp.speed;
                }
                if (temp.rot == 0)
                {
                    temp.pos.y -= temp.speed;
                }
                if (temp.rot == 180)
                {
                    temp.pos.y += temp.speed;
                }
            }
            else if (in->maps[x][((int)temp.pos.y / 64)][((int)temp.pos.x / 64)] == 'd')
            {
                temp.rot += 90;
            }
            if (temp.life == 0)
                temp.alive = false;
        }
        else
        {
            temp.spawnCooldoown -= 1;
            if (temp.spawnCooldoown == 0)
                temp.alive = true;
        }
        if (temp.life <= 0 && temp.dead == false)
        {
            in->player.coins += temp.coinsToDeliver;
            temp.alive = false;
            temp.dead = true;
        }
        if (!temp.alive && temp.spawnCooldoown <= 0)
            NumberOfEnemies -= 1;
        in->enemy[i] = temp;
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