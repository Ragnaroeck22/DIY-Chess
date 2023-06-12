//
// Created by 22max on 12.06.2023.
//

#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(int posX, int posY, bool ownedByPlayer);
    void Draw(Vector2 position, int tileSize) override;
    std::vector<Vector2Int> GetMovementOptions() override;
};
