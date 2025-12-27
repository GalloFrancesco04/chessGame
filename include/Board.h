#pragma once
#include "enums/Piece.h"
#include "enums/Color.h"
#include "Square.h"

class Board
{
private:
    chess::Square board[8][8];

public:
    Board();
    const chess::Square& getSquare(int row, int column) const;
    void setSquare(int row, int column, const chess::Square &square);
};