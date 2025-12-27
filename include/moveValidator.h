#pragma once
#include "Board.h"

class moveValidator
{
public:
    static bool isValidMove(const Board &board, int fromRow, int fromCol, int toRow, int toCol);

private:
    static bool hasObstacle(const Board &board, int fromRow, int fromCol, int toRow, int toCol);
};