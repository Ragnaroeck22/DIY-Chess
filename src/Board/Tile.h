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

    Vector2 coordinates;

    Tile(Vector2 coordinates, Color color);

};

