//
// Created by 22max on 23.05.2023.
//

#pragma once

#include <vector>
#include "Tile.h"

class Board
{

    // Attributes
private:

    const int boardSize = 8;

    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;

    Vector2 startPos = {0, 0};


    const int tileSize = 100;

    std::vector<std::shared_ptr<Piece>> pieces;

    // Dragging
    std::shared_ptr<Piece> draggedPiece;


public:

    // Functions

public:

    Board();

    void Update();

    void Draw();


private:
    void GenerateBoard();

    std::shared_ptr<Tile> GetTileFromPosition(Vector2 screenPosition);

    void SelectPiece();
    void DeselectPiece();

    void HighlightTiles();
    void HighlightCapture();

    // Dragging
    void BeginDrag();
    void EndDrag();
};

