//
// Created by 22max on 12.06.2023.
//

#pragma once

#include "raylib.h"
#include "Piece.h"

class Pawn : public Piece
{

public:
    Pawn(int posX, int posY);
    void Draw(Vector2 position, int tileSize) override;
};

