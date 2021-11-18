#pragma once
#include <raylib.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef enum renderType : int
{
    MAIN,
    GAME,
    SETTINGS,
}renderType;

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

struct GameDatas
{
    Font font[5];
    Texture2D texture[150];
    Player player;
    Enemy enemy[100000];
    renderType type;
    Vector2 mousePoint;
    Rectangle towerRec[10];
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
