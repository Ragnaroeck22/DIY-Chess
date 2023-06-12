#include "Piece.h"

//
// Created by 22max on 12.06.2023.
//

#pragma once

class King : public Piece
{
public:
    King(int posX, int posY, bool ownedByPlayer);
    void Draw(Vector2 position, int tileSize) override;
    std::vector<Vector2Int> GetMovementOptions() override;
};
