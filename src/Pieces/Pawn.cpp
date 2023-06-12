//
// Created by 22max on 12.06.2023.
//

#include "Pawn.h"

void Pawn::Draw(Vector2 position, int tileSize)
{
    DrawCircle(position.x, position.y, tileSize / 2 * 0.8, RED);
}

Pawn::Pawn(int posX, int posY)
{
    this->x = posX;
    this->y = posY;
}
