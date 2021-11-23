#pragma once
#include <raylib.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define UPGRADE_COST_BASIC 450
#define UPGRADE_COST_ELITE 450
#define EXPLOSION_RADIUS 100

enum renderType : int
{
    MAIN,
    GAME,
    SETTINGS,
    CREATE
};

enum TowerType : int
{
    BASIC,
    ADVANCED,
    ELITE,
    ULTIMATE
};

enum EnemyType : int
{
    SLOW,
    FAST,
    STRONG,
    BOSS
};

class Entity
{
public:
    Vector2 pos;
    float rot;
    Entity();
    ~Entity();
};

class Tower : public Entity
{
private:
    TowerType type;
    int radius;
    int shootCooldown;
    int price;
    int index;
    int damage;
    int upgradeCost;
    bool overlay;

public:
    Tower();
    Tower(GameDatas *in, int type, int x, int y)
    {
        if (type == 1)
            type = ELITE;
        in
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
    ~Tower();
    int getShootCooldown();
};

class Player
{
private:
    Tower tower[1000];
    int coins;
    int numberOfTowers;

public:
    Player()
    {
        numberOfTowers = 0;
        coins = 200;
    }
    ~Player();
    int getNumberOfTowers()
    {
        return numberOfTowers;
    }
    void addNumberofTowers()
    {
        numberOfTowers++;
    }
};

const char map1[17][31] = {
    {"dddddddddddddddddddddddddddddd"},
    {"dddddddddddddddddddddddddddddd"},
    {"dddddddddddddddddddddddddddddd"},
    {"dddddddddddddddddddddddddddddd"},
    {"dddddd{======}dddddddddddddddd"},
    {"dddddd|dddddd|dddddddddddddddd"},
    {"dddddd|dddddd|dddddddddddddddd"},
    {"dddddd|dddddd|dddddddddddddddd"},
    {"dddddd|dddddd|dddddddddddddddd"},
    {"======]dddddd|dddddddddddddddd"},
    {"ddddddddddddd|dddddddd{======="},
    {"ddddddddddddd|dddddddd|ddddddd"},
    {"ddddddddddddd|dddddddd|ddddddd"},
    {"ddddddddddddd>========<ddddddd"},
    {"ddddddddddddd|dddddddd|ddddddd"},
    {"ddddddddddddd[========]ddddddd"},
    {"dddddddddddddddddddddddddddddd"},
};

class Enemy : public Entity
{
private:
    EnemyType type;
    int dir;
    int tmpdir;
    int life;
    int maxLife;
    float speed;
    int coinsToDeliver;
    int MaxCoinsToDeliver;
    bool alive;
    bool dead;
    int sens;
    int spawnCooldoown;

public:
    Enemy();
    Enemy(GameDatas *in)
    {
        pos = Vector2{0, 600};
        alive = false;
        dead = false;
        type = type;
        rot = 270;
        dir = 270;
        tmpdir = 0;
        spawnCooldoown = in->getDelaySpawn();
        in->addDelaySpawn(10);
        switch (type)
        {
        case SLOW:
            speed = 1;
            life = 100 + ((in->getRounds() - 1) * 10);
            coinsToDeliver = 40 - (in->getRounds() - 1 * 5);
            break;
        case FAST:
            speed = 2;
            life = 20 + ((in->getRounds() - 1) * 5);
            coinsToDeliver = 20 - (in->getRounds() - 1 * 2);
            break;
        case STRONG:
            speed = 0.75;
            life = 250 + ((in->getRounds() - 1) * 25);
            coinsToDeliver = 100 - (in->getRounds() - 1 * 10);
            break;
        case BOSS:
            speed = 0.5;
            life = 3000 + ((in->getRounds() - 1) * 50);
            coinsToDeliver = 500 - (in->getRounds() - 1 * 20);
            in->addDelaySpawn(500);
            break;
        default:
            break;
        }
        maxLife = life;
        MaxCoinsToDeliver = coinsToDeliver;
    }
    ~Enemy();
};

enum ParticleType : int
{
    NONE,
    EXPLOSION
};

struct Particle
{
    Vector2 pos;
    Vector2 vel;
    int timer;
    ParticleType type;
    float radius;
    int opacity;
};

class GameDatas
{
private:
    Font font[5];
    Texture2D texture[150];
    Player player;
    Enemy enemy[100000];
    renderType type;
    Vector2 mousePoint;
    Rectangle towerRec[10];
    Rectangle tilesRec[10];
    Particle particle[1000];
    char maps[2][17][31];
    int delaySpawn;
    int mapId;
    int overlayId;
    bool btnState[10];
    bool inGame;
    bool drag[2];
    bool isTower[17][31];
    int frameCounter;
    int enemiesCount;
    int precEnemiesCount;
    int precDir;
    int rounds;

public:
    GameDatas()
    {
        Player player();
    }
    ~GameDatas();
    void setTexture(int index, Texture2D t)
    {
        texture[index] = t;
    }
    void setFont(int index, Font f)
    {
        font[index] = f;
    }
    int getRounds() const
    {
        return rounds;
    }
    void addDelaySpawn(int a)
    {
        delaySpawn += a;
    }
    void setDelaySpawn(int a)
    {
        delaySpawn = a;
    }
    int getDelaySpawn()
    {
        return delaySpawn;
    }
};
