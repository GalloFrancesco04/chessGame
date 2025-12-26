#pragma once
#include "enums/Piece.h"
#include "enums/Color.h"

namespace chess
{
    struct Square
    {
        Piece piece{Piece::EMPTY};
        Color color{Color::NONE};
    };

    // helpers
    inline constexpr bool isEmpty(const Square &s) { return s.piece == Piece::EMPTY; }
    inline constexpr Square emptySquare{Piece::EMPTY, Color::NONE};

}