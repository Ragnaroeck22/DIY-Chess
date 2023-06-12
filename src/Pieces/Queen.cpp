//
// Created by 22max on 12.06.2023.
//

#include "Queen.h"

Queen::Queen(int posX, int posY, bool ownedByPlayer)
{
    this->x = posX;
    this->y = posY;
    isOwnedByPlayer = ownedByPlayer;
}

void Queen::Draw(Vector2 position, int tileSize)
{
    Color drawColor;
    if (isOwnedByPlayer)
        drawColor = BLUE;
    else
        drawColor = RED;

    DrawCircle(position.x, position.y, tileSize / 2 * 0.8, drawColor);
}

std::vector<Vector2Int> Queen::GetMovementOptions()
{
    std::vector<Vector2Int> returnVec;

    for (int i = 1; i <= 8; i++)
    {
        returnVec.push_back({-i, -i});
        returnVec.push_back({i, -i});
        returnVec.push_back({-i, i});
        returnVec.push_back({i, i});
        returnVec.push_back({-i, 0});
        returnVec.push_back({i, 0});
        returnVec.push_back({0, -i});
        returnVec.push_back({0, i});
    }

    return returnVec;
}