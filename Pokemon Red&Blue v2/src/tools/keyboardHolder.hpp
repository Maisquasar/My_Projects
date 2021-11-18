#pragma once
#include <raylib.h>

typedef struct Inputs
{
    bool esc;
    bool space;
    bool nbr[6];
} Inputs;

void handleInputs(Inputs*);