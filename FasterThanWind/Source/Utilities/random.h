#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace random
{

    int num(int low, int high);
    sf::Color colour();
    sf::Vector2f position();

}

#endif // RANDOM_H_INCLUDED
