#include "map.hpp"

void generateMap(GameDatas *in)
{
    if (1)
/*     {
        for (int j = 0; j < 17; j++)
        {
            for (int i = 0; i < 31; i++)
            {
                if (map1[j][i] == '=') //RIGHT
                    DrawTextureEx(in->texture[2], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == 'd') //GRASS
                    DrawTextureEx(in->texture[(i ^ ((j * i) & 0x4)) ? 1 : 0], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '|') //UP
                    DrawTextureEx(in->texture[3], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == ']') //LEFT UP
                    DrawTextureEx(in->texture[4], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '{') //DOWN LEFT
                    DrawTextureEx(in->texture[6], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '}') //RIGHT DOWN
                    DrawTextureEx(in->texture[7], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '[') //UP RIGHT
                    DrawTextureEx(in->texture[5], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '>') //RIGHT UP DOWN
                    DrawTextureEx(in->texture[8], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (map1[j][i] == '<') //LEFT UP DOWN
                    DrawTextureEx(in->texture[9], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            }
        }
    }
    else */
    {
        int x = in->mapId;
        for (int j = 0; j < 17; j++)
        {
            for (int i = 0; i < 31; i++)
            {
                if (in->maps[x][j][i] == '=') //RIGHT
                    DrawTextureEx(in->texture[2], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == 'd') //GRASS
                    DrawTextureEx(in->texture[(i ^ ((j * i) & 0x4)) ? 1 : 0], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '|') //UP
                    DrawTextureEx(in->texture[3], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == ']') //LEFT UP
                    DrawTextureEx(in->texture[4], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '{') //DOWN right
                    DrawTextureEx(in->texture[6], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '}') //left DOWN
                    DrawTextureEx(in->texture[7], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '[') //UP RIGHT
                    DrawTextureEx(in->texture[5], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '>') //RIGHT UP DOWN
                    DrawTextureEx(in->texture[8], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '<') //LEFT UP DOWN
                    DrawTextureEx(in->texture[9], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == 'v') //LEFT DOWN RIGHT
                    DrawTextureEx(in->texture[10], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '^') //LEFT UP RIGHT
                    DrawTextureEx(in->texture[11], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
                else if (in->maps[x][j][i] == '+') //LEFT UP RIGHT DOWN
                    DrawTextureEx(in->texture[12], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            }
        }
    }
}

void createMap(GameDatas *in)
{
}

void reinitMap(GameDatas *in)
{
    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 31; i++)
        {
            in->maps[in->mapId][j][i] = 'd';
        }
    }
    in->tilesRec[1] = {1800, 120, 64, 64};
    in->tilesRec[2] = {1800, 220, 64, 64};
}