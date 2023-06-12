//
// Created by 22max on 12.06.2023.
//

#include "Pawn.h"


Pawn::Pawn(int posX, int posY, bool ownedByPlayer)
{
    this->x = posX;
    this->y = posY;
    isOwnedByPlayer = ownedByPlayer;
}

void Pawn::Draw(Vector2 position, int tileSize)
{
    Color drawColor;
    if (isOwnedByPlayer)
        drawColor = BLUE;
    else
        drawColor = RED;

    DrawCircle(position.x, position.y, tileSize / 2 * 0.8, drawColor);
}

std::vector<Vector2Int> Pawn::GetMovementOptions()
{
    std::vector<Vector2Int> returnVec;

    returnVec.push_back({0, 1});

    if (isFirstAction)
        returnVec.push_back({0, 2});


    if (isOwnedByPlayer)
    {
        for (int i = 0; i < returnVec.size(); i++)
        {
            returnVec[i].x = returnVec[i].y * -1;
        }
    }

    return returnVec;

}

