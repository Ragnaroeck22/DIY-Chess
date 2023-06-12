//
// Created by 22max on 23.05.2023.
//

#pragma once

#include "raylib.h"

class Piece
{

public:

    int x, y;
    bool isBeingDragged = false;

    virtual void Draw(Vector2 position, int tileSize) = 0;


};

