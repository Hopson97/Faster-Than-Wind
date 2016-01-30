#include "entity.h"

#include <iostream>
#include <cmath>

#include "random.h"
#include "constants.h"

Entity::Entity      (const sf::Texture& t)
: mSprite(t)
, isRedAdded    ( random::num( 0, 1 )  )
, isGreenAdded  ( random::num( 0, 1 )  )
, isBlueAdded   ( random::num( 0, 1 )  )
, danceCount    ( random::num(0, 5000) )
{

}

Entity::Entity(const sf::Texture& t, const std::string& text, const sf::Vector2f& pos)
: mSprite(t)
, isRedAdded    ( random::num( 0, 1 )  )
, isGreenAdded  ( random::num( 0, 1 )  )
, isBlueAdded   ( random::num( 0, 1 )  )
, danceCount    ( random::num(0, 5000) )
{
    setUpText(text, pos);
}

Entity::Entity(const sf::Texture& t, const std::string& text)
: isRedAdded    ( random::num( 0, 1 )  )
, isGreenAdded  ( random::num( 0, 1 )  )
, isBlueAdded   ( random::num( 0, 1 )  )
, danceCount    ( random::num(0, 5000) )
{

}

Entity::Entity()
: isRedAdded    ( random::num( 0, 1 )  )
, isGreenAdded  ( random::num( 0, 1 )  )
, isBlueAdded   ( random::num( 0, 1 )  )
, danceCount    ( random::num(0, 5000) )
{

}

void Entity::setUpText(const std::string& text, const sf::Vector2f& pos)
{
    mFont.loadFromFile    ( "Resources/Fonts/MTCORSVA.ttf"      );
    mText.setString       ( text                                );
    mText.setFont         ( mFont                               );
    mText.setCharacterSize( 60                                  );
    mText.setColor        ( col::TEXT_COLOUR                    );

    sf::FloatRect buttonRect = mText.getLocalBounds();
    mText.setOrigin( sf::Vector2f( buttonRect.width  / 2,
                                         buttonRect.height / 2 ) );
    sf::FloatRect spriteRect = _mSprite().getLocalBounds();

    sf::Vector2f spriteCenteredOrigin(  spriteRect.width  / 2,
                                        spriteRect.height / 2 );


    mText.setPosition     (  pos.x + spriteCenteredOrigin.x / 2 + buttonRect.width / 2 ,
                             pos.y + spriteCenteredOrigin.y / 2 ) ;
}

sf::Color Entity::sineColour()
{
    int r = mSprite.getColor().r;
    int g = mSprite.getColor().g;
    int b = mSprite.getColor().b;

    changeColour(r, isRedAdded);
    changeColour(g, isGreenAdded);
    changeColour(b, isBlueAdded);

    return sf::Color(r, g, b);
}

/**
=================================================================================================================================================================
*   changeColour () changes the colour of the Entity, primarily used by the Entity::dance method
*   param1  :   integer to represent 0 - 255 RGB value of either red, green or blue
*   param2   :   boolean to that shows if the R, G or B value is increasing (true) or decreasing (false)
=================================================================================================================================================================
*/
void Entity::changeColour(int& colour, bool& isAdding)
{
    if( isAdding ) {
        colour++;
        if( colour >= 255 ) {
            isAdding = false;
            colour = 254;
        }
    } else {
        colour--;
        if( colour <= 0 ) {
            isAdding = true;
            colour = 1;
        }
    }
}

/**
=================================================================================================================================================================
*   dance()     makes the Entity's sprite "dance" in the form of scaling in and out while fading colours
*   param1  :   float that is the delta time of the game
=================================================================================================================================================================
*/
void Entity::dance(const float& dt)
{

    danceCount += dt;
    mSprite.setScale(sf::Vector2f   (
                                    ( 1.5 +  sin( danceCount ) )  ,
                                    ( 1.5 +  sin( danceCount ) )  ) );
    mSprite.setColor(sineColour());
}

/**
=================================================================================================================================================================
*   draw()      draws the sprite to the screen
*   param1  :   the game window
=================================================================================================================================================================
*/
void  Entity::draw (sf::RenderWindow& window)
{
    window.draw(mSprite);
    window.draw(mText);
}

/**
=================================================================================================================================================================
*   _mSprite() returns the sprite for the derived classes
=================================================================================================================================================================
*/
sf::Sprite& Entity::_mSprite()
{
    return mSprite;
}

/**
=================================================================================================================================================================
*   setToRandColour () sets the sprite's colour to a random colour for each RGB value, using functions in random.h, use primary by this->dance method
=================================================================================================================================================================
*/
void Entity::setToRandColour()
{
    mSprite.setColor(random::colour());
}

/**
=================================================================================================================================================================
*   centerOrigin() simply centers the origin of the sprite, and of course doing so might move the sprite a by half its width and height
*   param 1 :   an SFML vector2f to define the new position of the sprite, because centring the origin causes an offset
=================================================================================================================================================================
*/
void Entity::centerOrigin( const sf::Vector2f& newPos )
{
    sf::FloatRect f = mSprite.getLocalBounds();

    mSprite.setOrigin       ( sf::Vector2f( f.width/ 2 , f.height/ 2  ) );
    mSprite.setPosition(newPos);
}

/**
=================================================================================================================================================================
*   setTextureRect() sets the area of the sprite sheet which is visible to the player
=================================================================================================================================================================
*/
void Entity::setTextureRect(const sf::IntRect& rect)
{
    mSprite.setTextureRect(rect);
}

void Entity::setTextSize        ( const int cSize               )
{
    mText.setCharacterSize(cSize);
     mText.move (0, mText.getCharacterSize() - 10 );
}

void Entity::moveText           ( const sf::Vector2f& offset    )   { mText.move(offset);               }


void Entity::setPos             ( const sf::Vector2f& pos       )   { mSprite.setPosition(pos);         }

void Entity::setRot             ( const int rot                 )   { mSprite.setRotation(rot);         }

void Entity::setColour          ( const sf::Color& c            )   { mSprite.setColor(c);              }

void Entity::setOrigin          ( const sf::Vector2f& org       )   { mSprite.setOrigin(org);           }

sf::Vector2f Entity::getPos     () const                            { return mSprite.getPosition();     }

sf::Sprite Entity::getSprite    () const                            { return mSprite;                   }
