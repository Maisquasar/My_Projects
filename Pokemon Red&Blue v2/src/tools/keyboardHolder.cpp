#include "keyboardHolder.hpp"

void handleInputs(Inputs *in)
{
    in->esc = false;
    in->space = false;
    for (int i = 0; i < 6; i++)
    {
        in->nbr[i] = false;
    }
    if (IsKeyPressed(KEY_ESCAPE))
        in->esc = true;
    if (IsKeyPressed(KEY_SPACE))
        in->space = true;
    if (IsKeyPressed(KEY_ONE))
        in->nbr[0] = true;
    if (IsKeyPressed(KEY_TWO))
        in->nbr[1] = true;
    if (IsKeyPressed(KEY_THREE))
        in->nbr[2] = true;
    if (IsKeyPressed(KEY_FOUR))
        in->nbr[3] = true;
    if (IsKeyPressed(KEY_FIVE))
        in->nbr[4] = true;
    if (IsKeyPressed(KEY_SIX))
        in->nbr[5] = true;
}