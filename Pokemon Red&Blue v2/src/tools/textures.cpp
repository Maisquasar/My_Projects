#include "textures.hpp"

void getTexturesPokemons(GameDatas* in)
{
    Image Pks = LoadImage("assets/sprites.png");
    int x = 0;
    int tab[10][16];
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            if (i > 7 && j == 16) break;
            else
            {
                tab[j][i] = x;
                Image temp = ImageCopy(Pks);
                ImageCrop(&temp, (Rectangle){64 * i, 64 * j, 64, 64});
                Texture2D tmp2 = LoadTextureFromImage(temp);
                UnloadImage(temp);
                in->PkSprites[x] = tmp2;
                x++;
            }
        }
    }
    UnloadImage(Pks);
}

void loadTextures(GameDatas* in)
{
    getTexturesPokemons(in);
}
//1024*640
//16*10