#include "render.hpp"
#include "../../third_party/include/raylib.h"

int getSizeW(GameDatas *in, int x)
{
    if (x > 0)
        return in->screen.width * x / 1920;
    if (x < 0)
        return in->screen.width - in->screen.width * x / 1920;
}

int getSizeH(GameDatas *in, int x)
{
    if (x > 0)
        return in->screen.height * x / 1080;
    if (x < 0)
        return in->screen.height - in->screen.height * x / 1080;
}

void DrawRectanglePokemon(GameDatas *in, Pokemon pk)
{
    if (pk.owner == PLAYER)
    {
        Rectangle Rec = {getSizeW(in, 1270), getSizeH(in, 530), getSizeW(in, 600), getSizeH(in, 200)};
        DrawRectangleRounded(Rec, 0.2, 0, GRAY);
        DrawRectangleRoundedLines(Rec, 0.2, 0, 10, DARKBROWN);
        DrawText(pk.name, getSizeW(in, Rec.x + 10), getSizeH(in, Rec.y + 10), 50, BLACK);
        DrawText(TextFormat("l %d", pk.level), getSizeW(in, Rec.x + 10), getSizeH(in, Rec.y + 70), 30, RAYWHITE);
        DrawText(TextFormat("%.0f/%0.f", pk.currentHP, pk.MaxHP), getSizeW(in, Rec.x + 275), getSizeH(in, Rec.y + 100), 30, RAYWHITE);
        if (pk.currentHP > 0)
            DrawRectangle(getSizeW(in, Rec.x + 85), getSizeH(in, Rec.y + 72), getSizeW(in, pk.currentHP * 300 / pk.MaxHP), getSizeH(in, 20), pk.currentHP * 100 / pk.MaxHP < 25 ? (RED) : pk.currentHP * 100 / pk.MaxHP < 50 ? ORANGE
                                                                                                                                                                                                                             : GREEN);
        DrawRectangleLines(getSizeW(in, Rec.x + 85), getSizeH(in, Rec.y + 72), getSizeW(in, 300), getSizeH(in, 20), DARKBROWN);
    }
    else
    {
        Color color;
        Rectangle Rec = {getSizeW(in, 50), getSizeH(in, 50), getSizeW(in, 600), getSizeH(in, 200)};
        DrawRectangleRounded(Rec, 0.2, 0, GRAY);
        DrawRectangleRoundedLines(Rec, 0.2, 0, 10, DARKBROWN);
        DrawText(pk.name, getSizeW(in, 60), getSizeH(in, 55), 50, BLACK);                                              //Name
        DrawText(TextFormat("l %d", pk.level), getSizeW(in, 60), getSizeH(in, 120), 30, RAYWHITE);                     //Level
        DrawText(TextFormat("%.0f/%.0f", pk.currentHP, pk.MaxHP), getSizeW(in, 280), getSizeH(in, 150), 30, RAYWHITE); //Life
        if (pk.currentHP)
            if (pk.currentHP * 100 / pk.MaxHP < 25)
                color = RED;
            else if (pk.currentHP * 100 / pk.MaxHP < 50)
                color = ORANGE;
            else
                color = GREEN;
        DrawRectangle(getSizeW(in, 130), getSizeH(in, 120), getSizeW(in, pk.currentHP * 300 / pk.MaxHP), getSizeH(in, 20), color);
        DrawRectangleLines(getSizeW(in, 130), getSizeH(in, 120), getSizeW(in, 300), getSizeH(in, 20), DARKBROWN);
    }
}
void DrawRectangleText(GameDatas *in)
{
    Rectangle TextRec = {getSizeW(in, 10), getSizeH(in, 770), getSizeW(in, 1920 - 20), getSizeH(in, 300)};
    DrawRectangleRounded(TextRec, 0.05, 0, GRAY);
    DrawRectangleRoundedLines(TextRec, 0.05, 0, 5, DARKBROWN);
}

int getNumberOfCaracter(char t[])
{
    int x = 0;
    for (int i = 0; i < 1000; i++)
        if (t[i] != NULL)
            x++;
    return x;
}

void renderList(GameDatas *in)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    switch (in->render)
    {
    case M_FIGHT:
        renderFight(in);
        switch (in->action)
        {
        case A_ATTACK:
            renderAttack(in);
            break;
        case A_PKMN:
            renderPKMN(in);
            break;
        case A_ITEM:
            renderItem(in);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    EndDrawing();
}

void renderAttack(GameDatas *in)
{
    //Render all Attacks
    int j = 0;
    Rectangle AttackRec = {getSizeW(in, 600), getSizeH(in, 770), getSizeW(in, 1920 - 610), getSizeH(in, 300)};
    DrawRectangleRounded(AttackRec, 0.05, 0, GRAY);
    DrawRectangleRoundedLines(AttackRec, 0.05, 0, 5, DARKBROWN);
    for (int i = 0; i < in->player.pokemon[in->currentPK].moveCount; i++)
    {
        if (i < 2)
            DrawText(TextFormat("%s", in->player.pokemon->moveSlots[i].name), AttackRec.x + 200 + 550 * i, AttackRec.y + 50, 80, BLACK);
        else
        {
            if (i == 2)
                j = 200;
            else
                j = 750;
            DrawText(TextFormat("%s", in->player.pokemon->moveSlots[i].name), AttackRec.x + j, AttackRec.y + 150, 80, BLACK);
        }
    }
}

void renderPKMN(GameDatas *in)
{
    DrawRectangle(0, 0, 1920, 1080, BLACK);
    DrawRectangleText(in);
    DrawText(TextSubtext(message1[3], 0, in->frameCounter / 2), getSizeW(in, 110), getSizeH(in, 800), 50, MAROON);
    for (int i = 0; i < in->player.pokemonCount; i++)
    {
        DrawText(TextFormat("%s: lvl %d", in->player.pokemon[i].name, in->player.pokemon[i].level), 300, 20 + 100 * i, 50, WHITE);
        DrawTextureEx(in->PkSprites[in->player.pokemon[i].speciesId], (Vector2){175, 20 + 100 * i}, 0, 1, RAYWHITE);
        DrawText(TextFormat("%.0f / %.0f", in->player.pokemon[i].currentHP, in->player.pokemon[i].MaxHP), 600, 70 + 100 * i, 25, WHITE);
        DrawRectangle(getSizeW(in, 275), getSizeH(in, 70 + 100 * i), getSizeW(in, in->player.pokemon[i].currentHP * 300 / in->player.pokemon[i].MaxHP), getSizeH(in, 20), in->player.pokemon[i].currentHP * 100 / in->player.pokemon[i].MaxHP < 25 ? (RED) : in->player.pokemon[i].currentHP * 100 / in->player.pokemon[i].MaxHP < 50 ? ORANGE
                                                                                                                                                                                                                                                                                                                                      : GREEN);
        DrawRectangleLines(getSizeW(in, 275), getSizeH(in, 70 + 100 * i), getSizeW(in, 300), getSizeH(in, 20), WHITE);
    }
}

void renderItem(GameDatas *in)
{
    Rectangle TextRec2 = {getSizeW(in, 1000), getSizeH(in, 300), getSizeW(in, 900), getSizeH(in, 460)};
    DrawRectangleRounded(TextRec2, 0.05, 0, GRAY);
    DrawRectangleRoundedLines(TextRec2, 0.05, 0, 5, DARKBROWN);
    DrawText(TextFormat("POKé BALL  x%d", in->player.pokeballCount), TextRec2.x + 100, TextRec2.y + 70, 50, BLACK);
}
void renderFight(GameDatas *in)
{
    int j, attempts = 0;
    DrawTextureEx(in->PkSprites[in->wild.speciesId], (Vector2){1300, 125}, 0, 5, RAYWHITE);                                                                                 //Wild
    DrawTexturePro(in->PkSprites[in->player.pokemon[in->currentPK].speciesId], (Rectangle){0, 0, -64, 64}, (Rectangle){50, 400, 456, 456}, (Vector2){32, 32}, 0, RAYWHITE); //Pokemon Sprite Player
    //Player Rectangle
    DrawRectanglePokemon(in, in->player.pokemon[in->currentPK]);
    //Wild Rectangle
    DrawRectanglePokemon(in, in->wild);
    //Text Rectangle
    DrawRectangleText(in);
    if (in->messageId == 0)
        DrawText(TextSubtext(TextFormat(message1[in->messageId], in->wild.name), 0, in->frameCounter / 2), getSizeW(in, 110), getSizeH(in, 800), 50, MAROON);
    else
        DrawText(TextSubtext(TextFormat(message1[in->messageId], in->player.pokemon[in->currentPK].name), 0, in->frameCounter / 2), getSizeW(in, 110), getSizeH(in, 800), 50, MAROON);
    if (in->messageId == 2)
    {
        //Render Fight
        Rectangle TextRec = {getSizeW(in, 600), getSizeH(in, 770), getSizeW(in, 1920 - 610), getSizeH(in, 300)};
        DrawRectangleRounded(TextRec, 0.05, 0, GRAY);
        DrawRectangleRoundedLines(TextRec, 0.05, 0, 5, DARKBROWN);
        DrawText("FIGHT", TextRec.x + 300, TextRec.y + 50, 85, BLACK);
        DrawText("PKMN", TextRec.x + 850, TextRec.y + 50, 85, BLACK);
        DrawText("ITEM", TextRec.x + 300, TextRec.y + 150, 85, BLACK);
        DrawText("RUN", TextRec.x + 850, TextRec.y + 150, 85, BLACK);
    }
}