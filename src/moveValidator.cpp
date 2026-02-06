#include "moveValidator.h"
#include <cmath>

bool moveValidator::hasObstacle(const Board &board, int fromRow, int fromCol, int toRow, int toCol)
{
    // Horizontal movement
    if (fromRow == toRow)
    {
        if (fromCol > toCol)
        {
            for (int i = fromCol - 1; i > toCol; i--)
            {
                if (board.getSquare(toRow, i).piece != chess::Piece::EMPTY)
                    return true;
            }
            return false;
        }
        if (fromCol < toCol)
        {
            for (int i = fromCol + 1; i < toCol; i++)
            {
                if (board.getSquare(toRow, i).piece != chess::Piece::EMPTY)
                    return true;
            }
            return false;
        }
    }

    // Vertical movement
    if (fromCol == toCol)
    {
        if (fromRow < toRow)
        {
            for (int i = fromRow + 1; i < toRow; i++)
            {
                if (board.getSquare(i, toCol).piece != chess::Piece::EMPTY)
                    return true;
            }
            return false;
        }
        if (fromRow > toRow)
        {
            for (int i = fromRow - 1; i > toRow; i--)
            {
                if (board.getSquare(i, toCol).piece != chess::Piece::EMPTY)
                    return true;
            }
            return false;
        }
    }

    // Diagonal movement
    if (std::abs(toRow - fromRow) == std::abs(toCol - fromCol))
    {
        int stepRow = (toRow > fromRow) ? 1 : -1;
        int stepCol = (toCol > fromCol) ? 1 : -1;
        int i = fromRow + stepRow;
        int j = fromCol + stepCol;
        while (i != toRow && j != toCol)
        {
            if (board.getSquare(i, j).piece != chess::Piece::EMPTY)
                return true;
            i += stepRow;
            j += stepCol;
        }
        return false;
    }
    return false;
}

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

    int rowDelta = std::abs(toRow - fromRow);
    int colDelta = std::abs(toCol - fromCol);

    switch (fromSquare.piece)
    {
    case chess::Piece::PAWN:
        // Check direction
        if ((fromSquare.color == chess::Color::BLACK && fromRow > toRow) ||
            (fromSquare.color == chess::Color::WHITE && fromRow < toRow))
            return false;
        {
            if (colDelta == 0)
            {
                if (rowDelta == 0)
                    return false;
                if (rowDelta == 2)
                {
                    if (!(fromRow == 1 || fromRow == 6))
                        return false;
                    if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
                        return false;
                }
                else if (rowDelta != 1)
                    return false;

                if (toSquare.piece != chess::Piece::EMPTY)
                    return false;
                break;
            }

            if (colDelta == 1)
            {
                if (rowDelta != 1)
                    return false;
                if (toSquare.piece == chess::Piece::EMPTY || toSquare.color == fromSquare.color)
                    return false;
                break;
            }
            return false;
        }
        break;

    case chess::Piece::KNIGHT:
        if (!((rowDelta == 2 && colDelta == 1) ||
              (rowDelta == 1 && colDelta == 2)))
            return false;
        break;

    case chess::Piece::BISHOP:
        if (!(rowDelta == colDelta))
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    case chess::Piece::ROOK:
        if (!(fromRow == toRow || fromCol == toCol))
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    case chess::Piece::QUEEN:
        if (!(fromRow == toRow || fromCol == toCol || rowDelta == colDelta))
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    case chess::Piece::KING:
        if (rowDelta > 1 || colDelta > 1)
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    default:
        break;
    }

    return true;
}