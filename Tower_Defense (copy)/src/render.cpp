#include "render.hpp"

void render(GameDatas *in)
{
    BeginDrawing();
    switch (in->type)
    {
    case MAIN:
        renderMain(in);
        break;
    case GAME:
        renderGame(in);
        break;
    case SETTINGS:
        renderSettings(in);
        break;
    case CREATE:
        renderCreate(in);
    default:
        break;
    }
    EndDrawing();
}

void renderMain(GameDatas *in)
{
    //Background
    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 30; i++)
        {
            DrawTextureEx(in->texture[(i ^ ((j * i) & 0x4)) ? 1 : 0], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
        }
    }
    //Main Rectangle
    Rectangle MainRec = {500, 100, SCREEN_WIDTH - 1000, SCREEN_HEIGHT - 200};
    DrawRectangleRounded(MainRec, 0.05, 0, CLITERAL(Color){17, 85, 136, 150});
    //Title
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){MainRec.x + 100, MainRec.y + 25}, (Vector2){0, 0}, 0, 101, 1, YELLOW);
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){MainRec.x + 100, MainRec.y + 25}, (Vector2){1, 0}, 0, 100, 1, RED);

    //========Buttons========
    Rectangle ButtonsRec[3];
    for (int i = 0; i < 3; i++)
    {
        ButtonsRec[i] = {(MainRec.x + MainRec.width) / 2, 250 + 250 * (float)i, 500, 200};
        if (CheckCollisionPointRec(in->mousePoint, ButtonsRec[i]))
        {
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                in->btnState[i] = true;
            else
                in->btnState[i] = false;
        }
        else
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    }
    DrawTextPro(in->font[0], "PLAY", (Vector2){ButtonsRec[0].x + 130, ButtonsRec[0].y + 50}, (Vector2){0, 0}, 0, 100, 1, BLACK);
    DrawTextPro(in->font[0], "SETTINGS", (Vector2){ButtonsRec[1].x + 130, ButtonsRec[1].y + 50}, (Vector2){75, 0}, 0, 100, 1, BLACK);
    DrawTextPro(in->font[0], "LEAVE", (Vector2){ButtonsRec[2].x + 130, ButtonsRec[2].y + 50}, (Vector2){25, 0}, 0, 100, 1, BLACK);
}

void renderSettings(GameDatas *in)
{
    //Background
    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 30; i++)
        {
            DrawTextureEx(in->texture[(i ^ ((j * i) & 0x4)) ? 1 : 0], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
        }
    }
    Rectangle MainRec = {500, 100, SCREEN_WIDTH - 1000, SCREEN_HEIGHT - 200};
    DrawRectangleRounded(MainRec, 0.05, 0, CLITERAL(Color){17, 85, 136, 150});
    //Title
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){MainRec.x + 100, MainRec.y + 25}, (Vector2){0, 0}, 0, 101, 1, YELLOW);
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){MainRec.x + 100, MainRec.y + 25}, (Vector2){1, 0}, 0, 100, 1, RED);
    Rectangle ButtonsRec[3];
    for (int i = 0; i < 3; i++)
    {
        ButtonsRec[i] = {(MainRec.x + MainRec.width) / 2, 250 + 250 * (float)i, 500, 200};
        in->btnState[i] = false;
    }
    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionPointRec(in->mousePoint, ButtonsRec[i]))
        {
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                in->btnState[i] = true;
            else
                in->btnState[i] = false;
        }
        else
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    }

    DrawTextPro(in->font[0], "CREATE", (Vector2){ButtonsRec[0].x + 130, ButtonsRec[0].y + 25}, (Vector2){25, 0}, 0, 100, 1, BLACK);
    DrawTextPro(in->font[0], "LEAVE", (Vector2){ButtonsRec[2].x + 130, ButtonsRec[2].y + 25}, (Vector2){0, 0}, 0, 100, 1, BLACK);
}

void renderCreate(GameDatas *in)
{
    generateMap(in);
    Rectangle ButtonRec = {1850, 50, 80, 50}, TilesRec = {1750, 100, 280, 200};
    if (CheckCollisionPointRec(in->mousePoint, ButtonRec))
    {
        DrawRectanglePro(ButtonRec, Vector2{0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            in->btnState[9] = !in->btnState[9];
    }
    else
        DrawRectanglePro(ButtonRec, Vector2{0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    if (in->btnState[9])
    {
        DrawRectanglePro(TilesRec, Vector2{0, 0}, 0, CLITERAL(Color){17, 85, 136, 150});
        for (int i = 1; i < 3; i++)
        {
            DrawTexture(in->texture[i], in->tilesRec[i].x, in->tilesRec[i].y, WHITE);
            if (CheckCollisionPointRec(in->mousePoint, in->tilesRec[i]))
            {
                DrawRectangleLinesEx(in->tilesRec[i], 1, RED);
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    in->overlayId = i;
            }
            if (in->overlayId == i)
            {
                DrawRectangleLinesEx(in->tilesRec[i], 1, RED);
                DrawTexture(in->texture[i], in->mousePoint.x + 10, in->mousePoint.y + 10, WHITE);
                DrawRectangleLines(in->mousePoint.x + 10, in->mousePoint.y + 10, 64, 64, RED);
                if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                {
                    int tmpx = (int)((in->mousePoint.x - 32) / 64 + 0.5) * 64;
                    int tmpy = (int)((in->mousePoint.y - 32) / 64 + 0.5) * 64;
                    int tx = (tmpx / 64);
                    int ty = (tmpy / 64);
                    if (i == 2 && (tmpx < 1920 && tmpx >= 0) && (tmpy < 1080 && tmpy >= 0))
                    {
                        in->maps[in->mapId][ty][tx] = '=';
                    }
                    else
                        in->maps[in->mapId][ty][tx] = 'd';
                }
            }
        }
    }
    for (int z = 0; z < 17; z++)
    {
        for (int w = 0; w < 31; w++)
        {
            bool east = false, west = false, south = false, north = false;
            if (in->maps[in->mapId][z][w] != 'd')
            {
                if ((z != 16) && in->maps[in->mapId][z + 1][w] != 'd')
                {
                    south = true;
                }
                if ((z != 0) && in->maps[in->mapId][z - 1][w] != 'd')
                {
                    north = true;
                }
                if ((w != 31) && in->maps[in->mapId][z][w + 1] != 'd')
                {
                    east = true;
                }
                if (w == 29)
                {
                    east = true;
                }
                if ((w != 0) && in->maps[in->mapId][z][w - 1] != 'd')
                {
                    west = true;
                }
            }
            if (east && south && north && west)
            {
                in->maps[in->mapId][z][w] = '+';
            }
            else if (west && south && east)
            {
                in->maps[in->mapId][z][w] = 'v';
            }
            else if (west && north && east)
            {
                in->maps[in->mapId][z][w] = '^';
            }
            else if (west && south && north)
            {
                in->maps[in->mapId][z][w] = '<';
            }
            else if (east && south && north)
            {
                in->maps[in->mapId][z][w] = '>';
            }
            else if (east && north)
            {
                in->maps[in->mapId][z][w] = '[';
            }
            else if (east && south)
            {
                in->maps[in->mapId][z][w] = '{';
            }
            else if (west && north)
            {
                in->maps[in->mapId][z][w] = ']';
            }
            else if (west && south)
            {
                in->maps[in->mapId][z][w] = '}';
            }
            else if (north || south || (north && south))
            {
                in->maps[in->mapId][z][w] = '|';
            }
            else if ((east) || (west) || (west && east))
            {
                in->maps[in->mapId][z][w] = '=';
            }
        }
    }
    in->maps[in->mapId][9][0] = '=';
    Rectangle SaveRec = {1750, 1010, 300, 100};
    if (CheckCollisionPointRec(in->mousePoint, SaveRec))
    {
        DrawRectanglePro(SaveRec, Vector2{0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            in->btnState[7] = true;
            std::ofstream file("src/map.txt");
            file.write((char *)in->maps, sizeof(in->maps));
            file.close();
        }
    }
    else
        DrawRectanglePro(SaveRec, Vector2{0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    DrawRectangleLinesEx(SaveRec, 1, RED);
    DrawText("SAVE", 1765, 1020, 50, BLACK);
}

void renderGame(GameDatas *in)
{
    //Map
    generateMap(in);
    //Render
    renderEnemies(in);
    renderParticles(in->particle);
    renderTower(in);
    //Tower Overlay
    Rectangle TowerButtonRec = {1850, 50, 80, 50}, TowerRec = {1750, 100, 280, 200};
    if (CheckCollisionPointRec(in->mousePoint, TowerButtonRec))
    {
        DrawRectanglePro(TowerButtonRec, Vector2{0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            in->btnState[9] = !in->btnState[9];
    }
    else
        DrawRectanglePro(TowerButtonRec, Vector2{0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});

    //Tower Drag
    if (in->btnState[9])
    {
        DrawRectanglePro(TowerRec, Vector2{0, 0}, 0, CLITERAL(Color){17, 85, 136, 150});
        for (int i = 0; i < 2; i++)
        {
            if (CheckCollisionPointRec(in->mousePoint, in->towerRec[i]))
            {
                DrawTexturePro(in->texture[101 + 2 * i], Rectangle{0, 0, 64, 64}, in->towerRec[i], Vector2{0, 0}, 0, in->player.coins >= (i == 0 ? 100 : 500) ? YELLOW : RED);
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->player.coins >= (i == 0 ? 100 : 500))
                {
                    in->drag[i] = !in->drag[i]; //Invert drag or not
                    in->overlayId = -1;
                    int tmpx = (int)(in->towerRec[i].x / 64 + 0.5) * 64;
                    int tmpy = (int)(in->towerRec[i].y / 64 + 0.5) * 64;
                    if (in->maps[in->mapId][tmpy / 64][tmpx / 64] == 'd' && in->drag[i] == false && in->isTower[tmpy / 64][tmpx / 64] == 0) //If grass
                    {
                        if ((in->towerRec[i].x < 1680 || in->towerRec[i].x > 1920) || (in->towerRec[i].y < 30 || in->towerRec[i].y > 300))
                        {
                            in->player.coins -= i == 0 ? 100 : 500;
                            in->isTower[tmpy / 64][tmpx / 64] = true;
                            createTower(in, i, tmpx, tmpy);
                        }
                    }
                    if (i == 0)
                        in->towerRec[i] = {1810, 120, 64, 64};
                    else
                        in->towerRec[i] = {1810, 220, 64, 64};
                }
            }
            else
                DrawTexturePro(in->texture[101 + 2 * i], Rectangle{0, 0, 64, 64}, in->towerRec[i], Vector2{0, 0}, 0, WHITE);
            if (in->drag[i])
            {
                in->towerRec[i].x = in->mousePoint.x - 32;
                in->towerRec[i].y = in->mousePoint.y - 32;
            }
        }
        DrawText("100 $", TowerRec.x + 70, TowerRec.y + 80, 20, BLACK);
        DrawText("500 $", TowerRec.x + 70, TowerRec.y + 180, 20, BLACK);
    }

    //Pause Button
    Rectangle PauseRec = {1850, 1010, 70, 70};
    if (CheckCollisionPointRec(in->mousePoint, PauseRec))
    {
        DrawRectanglePro(PauseRec, Vector2{0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            in->btnState[10] = !in->btnState[10];
    }
    else
        DrawRectanglePro(PauseRec, Vector2{0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    DrawRectangle(1860, 1025, 20, 45, BLACK);
    DrawRectangle(1890, 1025, 20, 45, BLACK);
    if (in->btnState[10] == true)
        renderPause(in);
    DrawText(TextFormat("%d", in->player.coins), 100, 1000, 50, YELLOW);
    DrawTextureEx(in->texture[25], Vector2{10, 980}, 0, 1.2, YELLOW);
    DrawText(TextFormat("%d", GetFPS()), 1800, 0, 50, YELLOW);
    //Tower List
}

void renderPause(GameDatas *in)
{
    Rectangle PauseRec = {500, 100, SCREEN_WIDTH - 1000, SCREEN_HEIGHT - 200};
    DrawRectanglePro(PauseRec, Vector2{0, 0}, 0, CLITERAL(Color){17, 85, 136, 150});
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){PauseRec.x + 100, PauseRec.y + 25}, (Vector2){0, 0}, 0, 101, 1, YELLOW);
    DrawTextPro(in->font[0], "TOWER DEFENSE", (Vector2){PauseRec.x + 100, PauseRec.y + 25}, (Vector2){1, 0}, 0, 100, 1, RED);

    //========Buttons========
    Rectangle ButtonsRec[3];
    for (int i = 0; i < 3; i++)
    {
        ButtonsRec[i] = {(PauseRec.x + PauseRec.width) / 2, 250 + 250 * (float)i, 500, 200};
    }
    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionPointRec(in->mousePoint, ButtonsRec[i]))
        {
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                in->btnState[i] = true;
            else
                in->btnState[i] = false;
        }
        else
            DrawRectanglePro(ButtonsRec[i], (Vector2){0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    }
    DrawTextPro(in->font[0], "PLAY", (Vector2){ButtonsRec[0].x + 130, ButtonsRec[0].y + 50}, (Vector2){0, 0}, 0, 100, 1, BLACK);
    DrawTextPro(in->font[0], "SETTINGS", (Vector2){ButtonsRec[1].x + 130, ButtonsRec[1].y + 50}, (Vector2){75, 0}, 0, 100, 1, BLACK);
    DrawTextPro(in->font[0], "LEAVE", (Vector2){ButtonsRec[2].x + 130, ButtonsRec[2].y + 50}, (Vector2){25, 0}, 0, 100, 1, BLACK);
}

void renderEnemies(GameDatas *in)
{
    for (int i = 0; i < in->enemiesCount; i++)
    {
        if (in->enemy[i].alive && !in->enemy[i].dead)
        {
            if (in->enemy[i].type == SLOW || in->enemy[i].type == FAST)
                DrawTexturePro(in->texture[50 + in->enemy[i].type], Rectangle{0, 0, 42, 46}, Rectangle{in->enemy[i].pos.x, in->enemy[i].pos.y, 32, 32}, Vector2{16, 16}, in->enemy[i].rot, WHITE);
            else if (in->enemy[i].type == BOSS)
                DrawTexturePro(in->texture[50 + in->enemy[i].type], Rectangle{0, 0, 62, 76}, Rectangle{in->enemy[i].pos.x, in->enemy[i].pos.y, 62, 76}, Vector2{31, 38}, in->enemy[i].rot + 180, WHITE);
            else
                DrawTexturePro(in->texture[50 + in->enemy[i].type], Rectangle{0, 0, 52, 60}, Rectangle{in->enemy[i].pos.x, in->enemy[i].pos.y, 32, 32}, Vector2{16, 16}, in->enemy[i].rot + 180, WHITE);
            DrawRectangle(in->enemy[i].pos.x - 25, in->enemy[i].pos.y + 20, in->enemy[i].life * 50 / in->enemy[i].maxLife, 10, GREEN);
            DrawRectangleLines(in->enemy[i].pos.x - 25, in->enemy[i].pos.y + 20, 50, 10, BLACK);
        }
    }
}

void renderTower(GameDatas *in)
{
    if (in->player.tower[0].rot == 0 && in->rounds > 1)
        TraceLog(LOG_INFO, "Test");
    for (int i = 0; i < in->player.numberOfTowers; i++)
    {
        //Init
        Tower tmp = in->player.tower[i];
        Color color[10] = {};
        Rectangle rec = {tmp.pos.x - 32, tmp.pos.y - 32, 64, 64};
        Rectangle upgradeRec = {20, 20, 250, 50};
        Rectangle upgradeDamageRec = {1800, 510 - 100, 100, 25};
        Rectangle upgradeRadiusRec = {1800, 590 - 100, 100, 25};
        color[0] = CLITERAL(Color){255, 255, 255, 255};
        //Overlay
        if (in->overlayId == i)
        {
            DrawCircle(tmp.pos.x, tmp.pos.y, tmp.radius, CLITERAL(Color){150, 0, 0, 50}); //Radius Circle
            //Upgrade Button
            if (tmp.type == BASIC || tmp.type == ELITE)
            {
                DrawRectangleLinesEx(upgradeRec, 1, BLACK);
                DrawText(TextFormat("UPGRADE %d$", tmp.upgradeCost), 25, 25, 30, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeRec)) //Color if collision
                {
                    if (tmp.type == ELITE ? in->player.coins > 700 : in->player.coins > 450)
                        color[1] = CLITERAL(Color){150, 150, 0, 100};
                    else
                        color[1] = CLITERAL(Color){255, 0, 0, 150};
                }
                else
                    color[1] = CLITERAL(Color){150, 0, 0, 100};
                DrawRectangleRec(upgradeRec, color[1]);
                //Key for Upgrade
                if ((IsKeyDown(KEY_U) || (CheckCollisionPointRec(in->mousePoint, upgradeRec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))) && (tmp.type == ELITE ? in->player.coins > 700 : in->player.coins > 450))
                {
                    tmp = upgradeTower(in, tmp);
                }
            }
            else
            {
                //Upgrade Damage button
                DrawText(TextFormat("Damage : %d", tmp.damage), 1700, 470 - 100, 30, BLACK);
                DrawRectangleLinesEx(upgradeDamageRec, 1, BLACK);
                DrawText("UPGRADE 100$", 1810, 515 - 100, 5, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeDamageRec))
                {
                    DrawRectangleRec(upgradeDamageRec, in->player.coins > 200 ? CLITERAL(Color){150, 150, 0, 100} : CLITERAL(Color){255, 0, 0, 150});
                }
                else
                    DrawRectangleRec(upgradeDamageRec, CLITERAL(Color){150, 0, 0, 100});
                if ((IsKeyReleased(KEY_D) || (CheckCollisionPointRec(in->mousePoint, upgradeDamageRec) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))) && in->player.coins > 100 && tmp.damage < 50)
                {
                    in->player.coins -= 100;
                    tmp.damage += 2;
                }

                //Upgrade Radius button
                DrawText(TextFormat("Radius : %d", tmp.radius), 1700, 550 - 100, 30, BLACK);
                DrawRectangleLinesEx(upgradeRadiusRec, 1, BLACK);
                DrawText("UPGRADE 100$", 1810, 595 - 100, 5, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeRadiusRec))
                {
                    DrawRectangleRec(upgradeRadiusRec, in->player.coins > 200 ? CLITERAL(Color){150, 150, 0, 100} : CLITERAL(Color){255, 0, 0, 150});
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->player.coins > 200 && tmp.radius < 300)
                    {
                        in->player.coins -= 100;
                        tmp.radius += 20;
                    }
                }
                DrawRectangleRec(upgradeRadiusRec, CLITERAL(Color){150, 0, 0, 100});
                if (IsKeyReleased(KEY_R) && in->player.coins > 100 && tmp.radius < 300)
                {
                    in->player.coins -= 100;
                    tmp.radius += 20;
                }
            }
        }
        //Select
        if (CheckCollisionPointRec(in->mousePoint, rec)) //Check collision with tower
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->overlayId == i) //Re-init Overlay id
                in->overlayId = -1;
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //Overlay id
            {
                in->overlayId = i;
            }
        }
        if (in->overlayId == i)
        {
            color[0] = YELLOW;
        }
        //Render Tower
        float height = 64;
        int textureID = 101;
        if (tmp.shootCooldown >= 15)
        {
            height = (tmp.type == BASIC || tmp.type == ADVANCED) ? 80 : 64;
            textureID = 111;
        }
        DrawTexturePro(in->texture[100], Rectangle{0, 0, 64, 64}, Rectangle{tmp.pos.x - 32, tmp.pos.y - 32, 64, 64}, Vector2{0, 0}, 0, color[0]);                                                  //Tower Base
        DrawTexturePro(in->texture[textureID + tmp.type], Rectangle{0, 0, 64, height}, Rectangle{tmp.pos.x, tmp.pos.y, 64, height}, Vector2{32, height == 80 ? 49.0f : 32.0f}, tmp.rot, color[0]); //Tower Up
        in->player.tower[i] = tmp;
    }
}

void renderParticles(Particle *in) //Particles renderoui
{
    for (int i = 0; i < 1000; i++)
    {
        if (in[i].type != NONE)
        {
            Particle *tmp = &in[i];
            switch (tmp->type)
            {
            case EXPLOSION:
                tmp->radius = 10;
                if (tmp->timer <= 5)
                    DrawCircle(tmp->pos.x, tmp->pos.y, tmp->radius, CLITERAL(Color){97, 106, 107, (unsigned char)tmp->opacity});
                break;
            default:
                break;
            }
        }
    }
}