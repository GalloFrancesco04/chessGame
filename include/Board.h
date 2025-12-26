#pragma once
#include "enums/Piece.h"
#include "enums/Color.h"

class Board
{
private:
    chess::Piece board[8][8];

public:
    Board();
    chess::Piece getPiece(int row, int column);
    void setPiece(int row, int column, chess::Piece piece);
};