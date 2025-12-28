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

    switch (fromSquare.piece)
    {
    case chess::Piece::PAWN:
        // Check direction
        if ((fromSquare.color == chess::Color::BLACK && fromRow > toRow) ||
            (fromSquare.color == chess::Color::WHITE && fromRow < toRow))
            return false;

        // Check single move
        if (fromRow > 1 && fromRow < 6 && std::abs(toRow - fromRow) == 2)
            return false;

        // Check double move
        if ((fromRow == 1 || fromRow == 6) && std::abs(toRow - fromRow) > 2)
            return false;

        // Check obstacle
        if (fromCol == toCol && hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;

        // Check piece in front
        if (fromCol == toCol && toSquare.piece != chess::Piece::EMPTY)
            return false;

        // Check Diagonal
        if (fromCol != toCol)
        {
            if (std::abs(toCol - fromCol) != 1)
                return false;

            if (fromSquare.color == chess::Color::BLACK)
            {
                if (toSquare.piece == chess::Piece::EMPTY || toSquare.color != chess::Color::WHITE)
                    return false;
            }
            if (fromSquare.color == chess::Color::WHITE)
            {
                if (toSquare.piece == chess::Piece::EMPTY || toSquare.color != chess::Color::BLACK)
                    return false;
            }
        }
        break;

    case chess::Piece::KNIGHT:
        if (!((std::abs(toRow - fromRow) == 2 && std::abs(toCol - fromCol) == 1) ||
              (std::abs(toRow - fromRow) == 1 && std::abs(toCol - fromCol) == 2)))
            return false;
        break;

    case chess::Piece::BISHOP:
        if (!(std::abs(toRow - fromRow) == std::abs(toCol - fromCol)))
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
        if (!(fromRow == toRow || fromCol == toCol || std::abs(toRow - fromRow) == std::abs(toCol - fromCol)))
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    case chess::Piece::KING:
        if (std::abs(toRow - fromRow) > 1 || std::abs(toCol - fromCol) > 1)
            return false;
        if (hasObstacle(board, fromRow, fromCol, toRow, toCol))
            return false;
        break;

    default:
        break;
    }

    return true;
}