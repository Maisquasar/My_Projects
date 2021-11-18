#include "../third_party/include/raylib.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "datas/gamedatas.hpp"
#include "core/render.hpp"
#include "tools/textures.hpp"
#include "rules/rules.hpp"
#include "core/fight.hpp"
/* 
void test3()
{
    GameDatas in;
    in.player = createPlayer();
    in.player.pokemon[1] = createPokemon(149, 80);
    in.wild = createPokemon(150, 80);
    in.player.pokemonCount = 2;
    in.player.pokemonInLife = 2;
    // WildFight(&in);
    system("clear");
    HealPokemons(&in);
    in.wild = createPokemon(6, 80);
    // WildFight(&player, wild);

    //wild = createWildPkByRoad(1);
   // WildFight(&player, wild);

}
 */
int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Pokemon");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    ClearBackground(BLACK);
    GameDatas in;
    /* in.player.pokemon[0] = createPokemon(PK_BLASTOISE, 100, PLAYER);
    in.player.pokemon[1] = createPokemon(PK_CHARIZARD, 25, PLAYER);
    in.player.pokemon[2] = createPokemon(PK_VENUSAUR, 50, PLAYER);
    in.player.pokemon[3] = createPokemon(PK_MEWTWO, 87, PLAYER);
    in.player.pokemon[4] = createPokemon(PK_MEW, 69, PLAYER);
    in.player.pokemon[5] = createPokemon(PK_JIGGLYPUFF, 10, PLAYER);
    in.player.pokemon[4].currentHP = 10; 
    in.player.pokemonCount = 1; */
    in.player = createPlayer();
    in.wild = createPokemon(PK_CHARIZARD, 50, WILD);
    in.currentPK = 0;
    in.frameCounter = 0;
    in.messageId = 0;
    in.render = M_FIGHT;
    loadTextures(&in);
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        in.screen.width = GetScreenWidth();
        in.screen.height = GetScreenHeight();
        handleInputs(&in.inputs);
        switch (in.render)
        {
        case M_FIGHT:
            switch (in.action)
            {
            case A_ATTACK:
                for (int i = 0; i < 4; i++)
                    if (in.inputs.nbr[i])
                    {
                        handleAttack(&in.player.pokemon[in.currentPK], in.player.pokemon[in.currentPK].moveSlots[i], &in.wild);
                        in.inputs.nbr[i] = false;
                    }
                if (in.inputs.esc)
                {
                    in.action = A_NONE;
                }
                break;
            case A_PKMN:
                for (int i = 0; i < 6; i++)
                    if (in.inputs.nbr
                            [i])
                    {
                    }
                if (in.inputs.esc)
                {
                    in.action = A_NONE;
                }
                break;
            case A_ITEM:
                if (IsKeyPressed(KEY_ONE))
                {
                }
                if (in.inputs.esc)
                {
                    in.action = A_NONE;
                }
                break;
            default:
                if (in.inputs.nbr[0])
                    in.action = A_ATTACK;
                else if (in.inputs.nbr[1])
                    in.action = A_PKMN;
                else if (in.inputs.nbr[2])
                    in.action = A_ITEM;
                else if (in.inputs.nbr[3])
                    in.action = A_RUN;
                for (int i = 0; i < 6; i++)
                        in.inputs.nbr[i] = false;
                if (IsKeyPressed(KEY_SPACE) && in.messageId < 2)
                {
                    in.frameCounter = 0;
                    in.messageId++;
                }
                break;
            }
            break;
        default:

            break;
        }
        renderList(&in);
        in.frameCounter++;
    }
    for (int i = 0; i < 150; i++)
        UnloadTexture(in.PkSprites[i]);
    CloseWindow();
    return 0;
}
