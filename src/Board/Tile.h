//
// Created by 22max on 23.05.2023.
//

#pragma once

#include <memory>
#include "raylib.h"
#include "../Pieces/Piece.h"

class Tile
{
public:

    std::shared_ptr<Piece> contents = nullptr;
    Color color;
    bool shouldHighlight = false;

    Vector2Int coordinates;

    Tile(Vector2Int coordinates, Color color);

};

