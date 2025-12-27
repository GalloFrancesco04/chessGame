#include "Board.h"

namespace
{
    constexpr int BLACK_BACK_RANK = 0;
    constexpr int BLACK_PAWN_RANK = 1;
    constexpr int WHITE_PAWN_RANK = 6;
    constexpr int WHITE_BACK_RANK = 7;

    // Standard chess back rank: ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK
    constexpr chess::Piece BACK_RANK_PIECES[8] = {
        chess::Piece::ROOK,
        chess::Piece::KNIGHT,
        chess::Piece::BISHOP,
        chess::Piece::QUEEN,
        chess::Piece::KING,
        chess::Piece::BISHOP,
        chess::Piece::KNIGHT,
        chess::Piece::ROOK};
}

Board::Board()
{
    // Initialize all squares to empty
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            board[row][col] = chess::emptySquare;
        }
    }

    // Place black back rank
    for (int col = 0; col < 8; ++col)
    {
        board[BLACK_BACK_RANK][col] = {BACK_RANK_PIECES[col], chess::Color::BLACK};
    }

    // Place black pawns
    for (int col = 0; col < 8; ++col)
    {
        board[BLACK_PAWN_RANK][col] = {chess::Piece::PAWN, chess::Color::BLACK};
    }

    // Place white pawns
    for (int col = 0; col < 8; ++col)
    {
        board[WHITE_PAWN_RANK][col] = {chess::Piece::PAWN, chess::Color::WHITE};
    }

    // Place white back rank
    for (int col = 0; col < 8; ++col)
    {
        board[WHITE_BACK_RANK][col] = {BACK_RANK_PIECES[col], chess::Color::WHITE};
    }
}

const chess::Square &Board::getSquare(int row, int column) const
{
    return board[row][column];
}

void Board::setSquare(int row, int column, const chess::Square &square)
{
    board[row][column] = square;
}
