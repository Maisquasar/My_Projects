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
    }
    for (int i = 0; i < 3; i++)
    {
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
    Rectangle LeaveRec = {515, 905, 200, 50};
    if (CheckCollisionPointRec(in->mousePoint, LeaveRec))
    {
        DrawRectanglePro(LeaveRec, (Vector2){0, 0}, 0, CLITERAL(Color){200, 200, 200, 150});
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            in->btnState[0] = true;
        else
            in->btnState[0] = false;
    }
    else
        DrawRectanglePro(LeaveRec, (Vector2){0, 0}, 0, CLITERAL(Color){146, 45, 38, 150});
    DrawTextPro(in->font[0], "LEAVE", (Vector2){LeaveRec.x + 22, LeaveRec.y + 2}, (Vector2){0, 0}, 0, 50, 1, BLACK);
}

void renderGame(GameDatas *in)
{
    //Map
    generateMap(in);
    //Render
    renderEnemies(in);
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
        for (int i = 0; i < 1; i++)
        {
            if (CheckCollisionPointRec(in->mousePoint, in->towerRec[i]))
            {
                DrawTexturePro(in->texture[101 + i], Rectangle{0, 0, 64, 64}, in->towerRec[i], Vector2{0, 0}, 0, in->player.coins >= (i == 0 ? 100 : 500) ? YELLOW : RED);
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->player.coins >= (i == 0 ? 100 : 500))
                {
                    in->drag[i] = !in->drag[i]; //Invert drag or not
                    in->overlayId = -1;
                    int tmpx = (int)(in->towerRec[i].x / 64 + 0.5) * 64;
                    int tmpy = (int)(in->towerRec[i].y / 64 + 0.5) * 64;
                    if (map1[tmpy / 64][tmpx / 64] == 'd' && in->drag[i] == false && in->isTower[tmpy / 64][tmpx / 64] == 0) //If grass
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
                DrawTexturePro(in->texture[101 + i], Rectangle{0, 0, 64, 64}, in->towerRec[i], Vector2{0, 0}, 0, WHITE);
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
            if (in->enemy[i].type != STRONG)
                DrawTexturePro(in->texture[50 + in->enemy[i].type], Rectangle{0, 0, 42, 46}, Rectangle{in->enemy[i].pos.x, in->enemy[i].pos.y, 32, 32}, Vector2{16, 16}, in->enemy[i].rot, WHITE);
            else
                DrawTexturePro(in->texture[50 + in->enemy[i].type], Rectangle{0, 0, 52, 60}, Rectangle{in->enemy[i].pos.x, in->enemy[i].pos.y, 32, 32}, Vector2{16, 16}, in->enemy[i].rot + 180, WHITE);
            DrawRectangle(in->enemy[i].pos.x - 25, in->enemy[i].pos.y + 20, in->enemy[i].life * 50 / in->enemy[i].maxLife, 10, GREEN);
            DrawRectangleLines(in->enemy[i].pos.x - 25, in->enemy[i].pos.y + 20, 50, 10, BLACK);
        }
    }
}

void renderTower(GameDatas *in)
{
    for (int i = 0; i < in->player.numberOfTowers; i++)
    {
        Color color = WHITE;
        Rectangle rec = {in->player.tower[i].pos.x - 32, in->player.tower[i].pos.y - 32, 64, 64};
        Rectangle upgradeRec = {20, 20, 250, 50};
        Rectangle upgradeDamageRec = {1800, 510 - 100, 100, 25};
        Rectangle upgradeRadiusRec = {1800, 590 - 100, 100, 25};
        if (in->overlayId == i)
        {
            color = YELLOW;
            DrawCircle(in->player.tower[i].pos.x, in->player.tower[i].pos.y, in->player.tower[i].radius, CLITERAL(Color){150, 0, 0, 50});
            if (in->player.tower[i].type == BASIC)
            {
                DrawRectangleLinesEx(upgradeRec, 1, BLACK);
                DrawText("UPGRADE 450$", 25, 25, 30, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeRec))
                {
                    DrawRectangleRec(upgradeRec, in->player.coins > 450 ? CLITERAL(Color){150, 150, 0, 100} : CLITERAL(Color){255, 0, 0, 150});
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && in->player.coins > 450)
                    {
                        upgradeTower(in, i);
                    }
                }
                else
                    DrawRectangleRec(upgradeRec, CLITERAL(Color){150, 0, 0, 100});
                if (IsKeyDown(KEY_U) && in->player.coins > 450)
                {
                    upgradeTower(in, i);
                }
            }
            else
            {
                //Upgrade Damage button
                DrawText(TextFormat("Damage : %d", in->player.tower[i].damage), 1700, 470 - 100, 30, BLACK);
                DrawRectangleLinesEx(upgradeDamageRec, 1, BLACK);
                DrawText("UPGRADE 100$", 1810, 515 - 100, 5, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeDamageRec))
                {
                    DrawRectangleRec(upgradeDamageRec, in->player.coins > 200 ? CLITERAL(Color){150, 150, 0, 100} : CLITERAL(Color){255, 0, 0, 150});
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->player.coins > 200 && in->player.tower[i].damage < 50)
                    {
                        in->player.coins -= 100;
                        in->player.tower[i].damage += 2;
                    }
                }
                else
                    DrawRectangleRec(upgradeDamageRec, CLITERAL(Color){150, 0, 0, 100});
                if (IsKeyReleased(KEY_D) && in->player.coins > 100 && in->player.tower[i].damage < 50)
                {
                    in->player.coins -= 100;
                    in->player.tower[i].damage += 2;
                }
                //Upgrade Radius button
                DrawText(TextFormat("Radius : %d", in->player.tower[i].radius), 1700, 550 - 100, 30, BLACK);
                DrawRectangleLinesEx(upgradeRadiusRec, 1, BLACK);
                DrawText("UPGRADE 100$", 1810, 595 - 100, 5, BLACK);
                if (CheckCollisionPointRec(in->mousePoint, upgradeRadiusRec))
                {
                    DrawRectangleRec(upgradeRadiusRec, in->player.coins > 200 ? CLITERAL(Color){150, 150, 0, 100} : CLITERAL(Color){255, 0, 0, 150});
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->player.coins > 200 && in->player.tower[i].radius < 300)
                    {
                        in->player.coins -= 100;
                        in->player.tower[i].radius += 20;
                    }
                }
                else
                    DrawRectangleRec(upgradeRadiusRec, CLITERAL(Color){150, 0, 0, 100});
                if (IsKeyReleased(KEY_R) && in->player.coins > 100 && in->player.tower[i].radius < 300)
                {
                    in->player.coins -= 100;
                    in->player.tower[i].radius += 20;
                }
            }
        }
        DrawTexturePro(in->texture[100], Rectangle{0, 0, 64, 64}, Rectangle{in->player.tower[i].pos.x - 32, in->player.tower[i].pos.y - 32, 64, 64}, Vector2{0, 0}, 0, color);
        if (in->player.tower[i].shootCooldown == 3)
            DrawTexturePro(in->texture[111 + in->player.tower[i].type], Rectangle{0, 0, 64, 80}, Rectangle{in->player.tower[i].pos.x, in->player.tower[i].pos.y, 64, 80}, Vector2{32, 49}, in->player.tower[i].rot, color);
        else
            DrawTexturePro(in->texture[101 + in->player.tower[i].type], Rectangle{0, 0, 64, 64}, Rectangle{in->player.tower[i].pos.x, in->player.tower[i].pos.y, 64, 64}, Vector2{32, 32}, in->player.tower[i].rot, color);

        if (CheckCollisionPointRec(in->mousePoint, rec))
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && in->overlayId == i)
                in->overlayId = -1;
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                in->overlayId = i;
        }
    }
}