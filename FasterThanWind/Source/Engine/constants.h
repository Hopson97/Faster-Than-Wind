#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "SFML/Graphics.hpp"

namespace win
{
    constexpr int WIDTH             = 1280;
    constexpr int HEIGHT            = 700;
    constexpr int FRAME_RATE_LIMIT  =  60;
}

namespace col
{
    constexpr int WHITE         = 255;
    const sf::Color BLACK       (0, 0, 0, 255);

    const sf::Color YELLOWY     ( 189, 187, 95          );
    const sf::Color SELECTED    ( 150, 150, 150, 255    );
    const sf::Color TEXT_COLOUR ( 255, 245, 188         );
}

namespace ship
{
    constexpr int TILE_SIZE     =   40;
    constexpr int WIDTH         =   600;
    constexpr int HEIGHT        =   320;
}


#endif // CONSTANTS_H_INCLUDED
