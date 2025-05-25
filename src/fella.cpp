#include <raylib.h>
#include "fella.h"

Fella::Fella()
{
    position = { 0.0f, 0.5f, 0.0f };   // on the floor
}

void Fella::Draw() const
{
    DrawCube(position, 1.0f, 1.0f, 1.0f, BLUE);
}