#include "unit.h"

Unit::Unit(const sf::Texture& texture, const UnitType _type, const int xPos, const int yPos)
:   Object  ( texture)
,   mType   ( _type  )
,   mXPos   ( xPos   )
,   mYPos   ( yPos   )
{
    mSprite.setTextureRect  (sf::IntRect(0, 0, 38, 38 ) );
    mSprite.setPosition     ( xPos * 40, yPos * 40);
}
