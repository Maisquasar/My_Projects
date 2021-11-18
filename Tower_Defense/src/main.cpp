#include "datas.hpp"
#include "render.hpp"
#include "textureloader.hpp"
#include "action.hpp"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defense");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    GameDatas in;
    for (int i = 0; i < 10; i++)
        in.btnState[i] = 0;
    for (int j = 0; j < 17; j++)
        for (int i = 0; i < 31; i++)
            in.isTower[j][i] = 0;
    
    in.type = MAIN;
    in.rounds = 1;
    in.enemiesCount = 0;
    in.overlayId = -1;
    bool exit = false;
    TexturesLoad(&in);
    while (!exit && !WindowShouldClose())
    {
        in.mousePoint = GetMousePosition();
        switch (in.type)
        {
        case MAIN:
            if (in.btnState[0])
            {
                in.type = GAME;
                in.btnState[0] = false;
                in.inGame = true;
                getRounds(&in);
                initPlayer(&in);
                // initTower(&in);
            }
            if (in.btnState[1])
            {
                in.type = SETTINGS;
                in.btnState[1] = false;
            }
            if (in.btnState[2])
                exit = true;
            break;
        case GAME:
            handleEnemies(&in);
            handleTowers(&in);
            if (IsKeyPressed(KEY_TAB)) SetTargetFPS(600);
            if (IsKeyReleased(KEY_TAB)) SetTargetFPS(60);
            if (in.btnState[0])
            {
                in.btnState[10] = false;
                in.btnState[0] = false;
            }
            if (in.btnState[1])
            {
                in.type = SETTINGS;
                in.btnState[1] = false;
            }
            if (in.btnState[2])
            {
                in.btnState[2] = false;
                in.enemiesCount = 0;
                in.type = MAIN;
                in.inGame = false;
            }
            break;
        case SETTINGS:
            if (in.btnState[0])
            {
                if (in.inGame)
                {
                    in.btnState[10] = false;
                    in.type = GAME;
                }
                else
                    in.type = MAIN;
                in.btnState[0] = false;
            }
            break;
        default:
            break;
        }
        render(&in);
        in.frameCounter++;
        ClearBackground(RAYWHITE);
    }
    for (int i = 0; i < 150; i++)
        UnloadTexture(in.texture[i]);
    CloseWindow();
    return 0;
}