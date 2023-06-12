//
// Created by 22max on 12.06.2023.
//

#include "Knight.h"

Knight::Knight(int posX, int posY, bool ownedByPlayer)
{
    this->x = posX;
    this->y = posY;
    isOwnedByPlayer = ownedByPlayer;
}

void Knight::Draw(Vector2 position, int tileSize)
{
    Color drawColor;
    if (isOwnedByPlayer)
        drawColor = BLUE;
    else
        drawColor = RED;

    DrawCircle(position.x, position.y, tileSize / 2 * 0.8, drawColor);
}

std::vector<Vector2Int> Knight::GetMovementOptions()
{
    std::vector<Vector2Int> returnVec;

    returnVec.push_back({-1, 2});
    returnVec.push_back({1, 2});
    returnVec.push_back({-2, 1});
    returnVec.push_back({-2, -1});
    returnVec.push_back({2, 1});
    returnVec.push_back({2, -1});
    returnVec.push_back({-1, -2});
    returnVec.push_back({1, -2});

    return returnVec;
}
