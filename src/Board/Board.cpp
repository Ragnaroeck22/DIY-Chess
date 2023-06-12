//
// Created by 22max on 23.05.2023.
//

#include "Board.h"
#include "../Pieces/Pawn.h"

#include <iostream>

Board::Board()
{
    GenerateBoard();

    // Tests
    pieces.push_back(std::make_shared<Pawn>(4, 3));
    tiles[4][3]->contents = pieces[0];
}

void Board::GenerateBoard()
{
    bool makeBlack = false;
    Color currentColor;

    for (int y = 0; y < boardSize; y++)
    {


        std::vector<std::shared_ptr<Tile>> helperVec;
        for (int x = 0; x < boardSize; x++)
        {
            //if ((x % 2) + (y % 2) % 2 == 0)
            if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0))
            {
                currentColor = WHITE;
            }

            else
            {
                currentColor = BLACK;
            }

            Vector2 coords = {static_cast<float>(y), static_cast<float>(x)};
            helperVec.push_back(std::make_shared<Tile>(coords, currentColor));





        }


        tiles.push_back(helperVec);
        helperVec.clear();

        /*
        if (tiles[0][0]->color == (BLACK))
        {

        }
*/

    }
}

void Board::Update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 tilePos = GetTileFromPosition(GetMousePosition())->coordinates;
        std::cout << "Click at " + std::to_string((int)tilePos.x) + " | " + std::to_string((int)tilePos.y) << std::endl;
        BeginDrag();
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        EndDrag();
    }


}

void Board::Draw()
{
    // Draw board

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            DrawRectangle(startPos.x + j * tileSize,
                          startPos.y + i * tileSize,
                          tileSize, tileSize, tiles[i][j]->color);

        }

    }

    // Draw pieces
    for (int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i]->isBeingDragged)
        {
            pieces[i]->Draw(GetMousePosition(), tileSize);
        }

        else
        {
            //Vector2 drawPos = {static_cast<float>(startPos.x  * pieces[i]->x + tileSize / 2), static_cast<float>(startPos.y  * pieces[i]->y + tileSize / 2)};
            float drawX = startPos.x + pieces[i]->x * tileSize + tileSize / 2;
            float drawY = startPos.y + pieces[i]->y * tileSize + tileSize / 2;

            Vector2 drawPos = {drawX, drawY};

            pieces[i]->Draw(drawPos, tileSize);
        }

    }

}

std::shared_ptr<Tile> Board::GetTileFromPosition(Vector2 screenPosition)
{
    int coordX = startPos.x + screenPosition.x / tileSize;
    int coordY = startPos.y + screenPosition.y / tileSize;

    if (coordX < boardSize && coordX >= 0 && coordY < boardSize && coordY >= 0)
        return tiles[coordX][coordY];
    else
        return nullptr;
}


void Board::BeginDrag()
{
    draggedPiece = GetTileFromPosition(GetMousePosition())->contents;

    if (draggedPiece == nullptr)
        return;

    draggedPiece->isBeingDragged = true;
}

void Board::EndDrag()
{

    if (draggedPiece == nullptr)
        return;

    std::shared_ptr<Tile> newTile = GetTileFromPosition(GetMousePosition());
    if (newTile == nullptr)
    {
        draggedPiece->isBeingDragged = false;
        return;
    }



    // Maybe check if the tile isn't empty
    newTile->contents = draggedPiece;
    tiles[draggedPiece->x][draggedPiece->y]->contents = nullptr;
    draggedPiece->x = newTile->coordinates.x;
    draggedPiece->y = newTile->coordinates.y;
    draggedPiece->isBeingDragged = false;
    draggedPiece = nullptr;
}
