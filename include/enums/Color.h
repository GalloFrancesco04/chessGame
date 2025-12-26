#pragma once
#include <cstdint>

namespace chess
{
    enum class Color : uint8_t // this way it occupies 1 byte instead of an int
    {
        NONE,
        WHITE,
        BLACK
    };
}
