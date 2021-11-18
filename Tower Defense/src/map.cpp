#include "map.hpp"

void generateMap(GameDatas *in)
{
    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 31; i++)
        {
            if (map1[j][i] == '=')//RIGHT
                DrawTextureEx(in->texture[2], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == 'd')//GRASS
                DrawTextureEx(in->texture[(i ^ ((j * i) & 0x4)) ? 1 : 0], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '|')//UP
                DrawTextureEx(in->texture[3], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == ']')//LEFT UP
                DrawTextureEx(in->texture[4], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '{')//DOWN LEFT
                DrawTextureEx(in->texture[6], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '}')//RIGHT DOWN
                DrawTextureEx(in->texture[7], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '[')//UP RIGHT
                DrawTextureEx(in->texture[5], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '>')//RIGHT UP DOWN
                DrawTextureEx(in->texture[8], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
            else if (map1[j][i] == '<')//LEFT UP DOWN
                DrawTextureEx(in->texture[9], (Vector2){(float)i * 64, (float)j * 64}, 0, 1, WHITE);
        }
    }
}