//
// Created by 22max on 12.06.2023.
//

#include "King.h"

King::King(int posX, int posY, bool ownedByPlayer)
{
    this->x = posX;
    this->y = posY;
    isOwnedByPlayer = ownedByPlayer;
}

void King::Draw(Vector2 position, int tileSize)
{
    Color drawColor;
    if (isOwnedByPlayer)
        drawColor = BLUE;
    else
        drawColor = RED;

    DrawCircle(position.x, position.y, tileSize / 2 * 0.8, drawColor);
}

std::vector<Vector2Int> King::GetMovementOptions()
{
    std::vector<Vector2Int> returnVec;

    returnVec.push_back({-1, -1});
    returnVec.push_back({1, -1});
    returnVec.push_back({-1, 1});
    returnVec.push_back({1, 1});
    returnVec.push_back({-1, 0});
    returnVec.push_back({1, 0});
    returnVec.push_back({0, -1});
    returnVec.push_back({0, 1});


    return returnVec;
}
