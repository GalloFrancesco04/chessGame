#include "moveValidator.h"

bool moveValidator::isValidMove(const Board &board, int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow > 7 || fromCol > 7 || toRow > 7 || toCol > 7 || fromRow < 0 || fromCol < 0 || toRow < 0 || toCol < 0)
        return false;

    chess::Square fromSquare = board.getSquare(fromRow, fromCol);
    chess::Square toSquare = board.getSquare(toRow, toCol);

    if (fromSquare.piece == chess::Piece::EMPTY)
        return false;

    if (fromSquare.color == toSquare.color && fromSquare.color != chess::Color::NONE)
        return false;

    return true;
}