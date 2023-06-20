//
// Created by 22max on 23.05.2023.
//

#include "Board.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Queen.h"
#include "../Pieces/King.h"

#include <iostream>

Board::Board()
{
    GenerateBoard();

    // Tests
    pieces.push_back(std::make_shared<Queen>(4, 3, true));
    pieces.push_back(std::make_shared<Rook>(7, 4, false));
    pieces.push_back(std::make_shared<Knight>(6, 3, true));
    tiles[4][3]->contents = pieces[0];
    tiles[7][4]->contents = pieces[1];
    tiles[6][3]->contents = pieces[2];
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


            if (tiles[j][i]->highlightType == HIGHLIGHT)
            {
                DrawRectangle(startPos.x + j * tileSize,
                              startPos.y + i * tileSize,
                              tileSize, tileSize, ColorAlpha(YELLOW, 0.5));
            }
            else if (tiles[j][i]->highlightType == CAPTURE)
            {
                DrawRectangle(startPos.x + j * tileSize,
                              startPos.y + i * tileSize,
                              tileSize, tileSize, ColorAlpha(RED, 0.5));
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

    // Do a check if piece is controlled by the correct player


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
        newTile->highlightType == NONE)
    {
        draggedPiece->isBeingDragged = false;
        DeselectPiece();
        return;
    }

    DeselectPiece();

    tiles[draggedPiece->x][draggedPiece->y]->contents = nullptr;
    draggedPiece->x = newTile->coordinates.x;
    draggedPiece->y = newTile->coordinates.y;

    if (newTile->highlightType == CAPTURE && newTile->contents != nullptr)
    {
        // Here is the last opportunity to do something with the captured piece
        for (int i = 0; i < pieces.size(); i++)
        {
            if (pieces[i] == newTile->contents)
            {
                pieces.erase(pieces.cbegin() + i);
            }
        }
    }

    newTile->contents = draggedPiece;

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

    HighlightTiles();
}

void Board::DeselectPiece()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            tiles[i][j]->highlightType = NONE;
        }
    }
}

void Board::HighlightTiles()
{
    std::vector<Vector2Int> movementOptions = draggedPiece->GetMovementOptions();
    for (int i = 0; i < movementOptions.size(); i++)
    {
        int indexX = draggedPiece->x + movementOptions[i].x;
        int indexY = draggedPiece->y + movementOptions[i].y;

        if (indexX >= 0 && indexX < boardSize &&
            indexY >= 0 && indexY < boardSize)
        {
            tiles[indexX][indexY]->highlightType = HIGHLIGHT;
        }
    }

    Vector2Int upperLimit = {10, 10};
    Vector2Int lowerLimit = {-10, -10};

    for (int i = 0; i < pieces.size(); i++)
    {
        std::shared_ptr<Tile> tileToCheck = tiles[pieces[i]->x][pieces[i]->y];

        if (pieces[i] != draggedPiece)
        {

            if (tileToCheck->highlightType == HIGHLIGHT)
            {

                std::cout << "Piece: " + std::to_string(pieces[i]->x) + " | " + std::to_string(pieces[i]->y)
                          << std::endl;
                std::cout << "Tile: " + std::to_string(tileToCheck->coordinates.x) + " | " +
                             std::to_string(tileToCheck->coordinates.y) << std::endl;


                if (draggedPiece->x < tileToCheck->coordinates.x && tileToCheck->coordinates.x < upperLimit.x)
                {
                    upperLimit.x = tileToCheck->coordinates.x;

                    if (!tileToCheck->contents->isOwnedByPlayer)
                    {
                        upperLimit.x++;
                    }
                }
                if (draggedPiece->x > tileToCheck->coordinates.x && tileToCheck->coordinates.x > lowerLimit.x)
                {
                    lowerLimit.x = tileToCheck->coordinates.x;

                    if (!tileToCheck->contents->isOwnedByPlayer)
                    {
                        lowerLimit.x--;
                    }
                }

                if (draggedPiece->y < tileToCheck->coordinates.y && tileToCheck->coordinates.y < upperLimit.y)
                {
                    upperLimit.y = tileToCheck->coordinates.y;

                    if (!tileToCheck->contents->isOwnedByPlayer)
                    {
                        upperLimit.y++;
                    }
                }
                if (draggedPiece->y > tileToCheck->coordinates.y && tileToCheck->coordinates.y > lowerLimit.y)
                {
                    lowerLimit.y = tileToCheck->coordinates.y;

                    if (!tileToCheck->contents->isOwnedByPlayer)
                    {
                        lowerLimit.y--;
                    }
                }


                for (int i = 0; i < movementOptions.size(); i++)
                {
                    int indexX = draggedPiece->x + movementOptions[i].x;
                    int indexY = draggedPiece->y + movementOptions[i].y;

                    if (indexX >= 0 && indexX < boardSize &&
                        indexY >= 0 && indexY < boardSize)
                    {
                        tileToCheck = tiles[indexX][indexY];

                        if ((tileToCheck->coordinates.x >= upperLimit.x && tileToCheck->coordinates.y == draggedPiece->y) ||
                            (tileToCheck->coordinates.x <= lowerLimit.x && tileToCheck->coordinates.y == draggedPiece->y) ||
                            (tileToCheck->coordinates.y <= lowerLimit.y && tileToCheck->coordinates.x == draggedPiece->x) ||
                            (tileToCheck->coordinates.y >= upperLimit.y && tileToCheck->coordinates.x == draggedPiece->x))
                        {
                            tileToCheck->highlightType = NONE;
                        }
                    }
                }
            }
        }
    }

    HighlightCapture();

}

void Board::HighlightCapture()
{
    for (int i = 0; i < pieces.size(); i++)
    {
        if (tiles[pieces[i]->x][pieces[i]->y]->highlightType == HIGHLIGHT &&
            !pieces[i]->isOwnedByPlayer)
        {
            tiles[pieces[i]->x][pieces[i]->y]->highlightType = CAPTURE;
        }
    }
}
