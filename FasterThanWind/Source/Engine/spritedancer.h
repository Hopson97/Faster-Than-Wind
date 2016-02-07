#ifndef SPRITEDANCER_H
#define SPRITEDANCER_H

#include <SFML/Graphics.hpp>

class SpriteDancer
{
    public:
                        SpriteDancer    ();
        void            dance           (const float& dt, sf::Sprite& sprite);



    private:

        sf::Color      newColour       (const sf::Sprite& _sprite);
        void           changeColour    (int& colour, bool& isAdding);



        bool        isRedAdded;
        bool        isGreenAdded;
        bool        isBlueAdded;

        double      danceCount;

};

#endif // SPRITEDANCER_H
