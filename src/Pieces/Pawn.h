//
// Created by 22max on 12.06.2023.
//

#pragma once

#include "raylib.h"
#include "Piece.h"

class Pawn : public Piece
{

public:
    bool isFirstAction = true;

    Pawn(int posX, int posY, bool ownedByPlayer);
    void Draw(Vector2 position, int tileSize) override;
    std::vector<Vector2Int> GetMovementOptions() override;
};

