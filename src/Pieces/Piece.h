//
// Created by 22max on 23.05.2023.
//

#pragma once

#include <vector>
#include "raylib.h"
#include "../Structs.h"

class Piece
{

public:

    int x, y;
    bool isBeingDragged = false;
    bool isOwnedByPlayer;

    virtual void Draw(Vector2 position, int tileSize) = 0;
    virtual std::vector<Vector2Int> GetMovementOptions() = 0;

};

