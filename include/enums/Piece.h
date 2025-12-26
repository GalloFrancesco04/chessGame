#pragma once
#include <cstdint>

namespace chess
{
    enum class Piece : uint8_t // this way it occupies 1 byte instead of an int
    {
        EMPTY,
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };
}
