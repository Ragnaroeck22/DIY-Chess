//
// Created by 22max on 23.05.2023.
//

#include "Board.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Rook.h"

#include <iostream>

Board::Board()
{
    GenerateBoard();

    // Tests
    pieces.push_back(std::make_shared<Rook>(4, 3, true));
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

            Vector2Int coords = {y, x};
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


            if (tiles[j][i]->shouldHighlight)
            {
                DrawRectangle(startPos.x + j * tileSize,
                              startPos.y + i * tileSize,
                              tileSize, tileSize, ColorAlpha(YELLOW, 0.5));
            }

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
    SelectPiece();
}

void Board::EndDrag()
{
    if (draggedPiece == nullptr)
    {
        DeselectPiece();
        return;
    }

    std::shared_ptr<Tile> newTile = GetTileFromPosition(GetMousePosition());
    if (newTile == nullptr)
    {
        draggedPiece->isBeingDragged = false;
        DeselectPiece();
        return;
    }


    if (newTile->coordinates.x == draggedPiece->x && newTile->coordinates.y == draggedPiece->y ||
        !newTile->shouldHighlight)
    {
        draggedPiece->isBeingDragged = false;
        DeselectPiece();
        return;
    }

    DeselectPiece();

    // Maybe check if the tile isn't empty
    newTile->contents = draggedPiece;
    tiles[draggedPiece->x][draggedPiece->y]->contents = nullptr;
    draggedPiece->x = newTile->coordinates.x;
    draggedPiece->y = newTile->coordinates.y;

    std::cout << "New coords: " + std::to_string(draggedPiece->x) + " | " + std::to_string(draggedPiece->y) << std::endl;

    draggedPiece->isBeingDragged = false;
    draggedPiece = nullptr;
}

void Board::SelectPiece()
{
    if (draggedPiece == nullptr)
        return;

    std::shared_ptr<Tile> originTile = GetTileFromPosition({static_cast<float>(draggedPiece->x), static_cast<float>(draggedPiece->y)});

    if (originTile == nullptr)
        return;

    std::vector<Vector2Int> movementOptions = draggedPiece->GetMovementOptions();
    for (int i = 0; i < movementOptions.size(); i++)
    {
        int indexX = draggedPiece->x + movementOptions[i].x;
        int indexY = draggedPiece->y + movementOptions[i].y;

        if (indexX >= 0 && indexX < boardSize &&
            indexY >= 0 && indexY < boardSize)
        {

            tiles[indexX][indexY]->shouldHighlight = true;


        }
    }
}

void Board::DeselectPiece()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            tiles[i][j]->shouldHighlight = false;
        }
    }
}
