#pragma once
#include <raylib.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define UPGRADE_COST_BASIC 450
#define UPGRADE_COST_ELITE 450
#define EXPLOSION_RADIUS 100

typedef enum renderType : int
{
    MAIN,
    GAME,
    SETTINGS,
} renderType;

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

struct Tower
{
    Vector2 pos;
    float rot;
    TowerType type;
    int radius;
    int shootCooldown;
    int price;
    int index;
    int damage;
    int upgradeCost;
    bool overlay;
};

struct Player
{
    Tower tower[1000];
    int coins;
    int life;
    int numberOfTowers;
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

struct Enemy
{
    Vector2 pos;
    float rot;
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
    int spawnCooldoown;
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

struct GameDatas
{
    Font font[5];
    Texture2D texture[150];
    Player player;
    Enemy enemy[100000];
    renderType type;
    Vector2 mousePoint;
    Rectangle towerRec[10];
    Particle particle[1000];
    int delaySpawn;
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
};
