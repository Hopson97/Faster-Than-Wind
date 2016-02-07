#include "entity.h"

#include <iostream>
#include <cmath>

#include "random.h"
#include "constants.h"

Entity::Entity      (const sf::Texture& t)
: mSprite(t)
{

}

Entity::Entity(const sf::Texture& t, const std::string& text, const sf::Vector2f& pos)
: mSprite(t)
{
    setUpText(text, pos);
}

Entity::Entity(const sf::Texture& t, const std::string& text)
{

}

Entity::Entity()
{

}

/*****************************************************************************************************************************************************************
*   setUpText() if the entity should have some text to show, this this the place where it is set up, and tries to estimate where the text should be
*   param1  :   The text to be displayed on the button
*   param2  :   The position of the text
***************************************************************************************************************************************************************/
void Entity::setUpText(const std::string& text, const sf::Vector2f& pos)
{
    mFont.loadFromFile    ( "Resources/Fonts/MTCORSVA.ttf"      );
    mText.setString       ( text                                );
    mText.setFont         ( mFont                               );
    mText.setCharacterSize( 60                                  );
    mText.setColor        ( col::TEXT_COLOUR                    );

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin( sf::Vector2f(  textRect.width  / 2,
                                    textRect.height / 2 ) );

    sf::FloatRect spriteRect = _mSprite().getLocalBounds();

    sf::Vector2f spriteCenteredOrigin(  spriteRect.width  / 2,
                                        spriteRect.height / 2 );


    mText.setPosition     (  pos.x + spriteCenteredOrigin.x / 2 + textRect.width / 2 ,
                             pos.y + spriteCenteredOrigin.y / 2 ) ;
}

/*****************************************************************************************************************************************************************
*   draw()      draws the sprite to the screen
*   param1  :   the game window
**************************************************************************************************************************************************************/
void  Entity::draw (sf::RenderWindow& window)
{
    window.draw(mSprite);
    window.draw(mText);
}

/*****************************************************************************************************************************************************************
*   _mSprite() returns the sprite for the derived classes
***************************************************************************************************************************************************************/
sf::Sprite& Entity::_mSprite()
{
    return mSprite;
}

/*****************************************************************************************************************************************************************
*   setToRandColour () sets the sprite's colour to a random colour for each RGB value, using functions in random.h, use primary by this->dance method
***************************************************************************************************************************************************************/
void Entity::setToRandColour()
{
    mSprite.setColor(random::colour());
}

/*****************************************************************************************************************************************************************
*   centerOrigin() simply centers the origin of the sprite, and of course doing so might move the sprite a by half its width and height
*   param 1 :   an SFML vector2f to define the new position of the sprite, because centring the origin causes an offset
***************************************************************************************************************************************************************/
void Entity::centerOrigin( const sf::Vector2f& newPos )
{
    sf::FloatRect f = mSprite.getLocalBounds();

    mSprite.setOrigin       ( sf::Vector2f( f.width/ 2 , f.height/ 2  ) );
    mSprite.setPosition(newPos);
}

/*****************************************************************************************************************************************************************
*   setTextureRect() sets the area of the sprite sheet which is visible to the player
***************************************************************************************************************************************************************/
void Entity::setTextureRect(const sf::IntRect& rect)
{
    mSprite.setTextureRect(rect);
}

/*****************************************************************************************************************************************************************
*   setTextSize ()  sets the size of the text (if there is any)
*   param1  :   the size of the text
***************************************************************************************************************************************************************/
void Entity::setTextSize        ( const int cSize               )
{
    mText.setCharacterSize(cSize);
    mText.move (0, mText.getCharacterSize() - 10 );
}

void Entity::centerOrigin()
{
    sf::FloatRect r = mSprite.getLocalBounds();

    mSprite.setOrigin(  r.width     / 2,
                        r.height    / 2);
}

void Entity::dance(const float dt)
{
    dancer.dance(dt, mSprite);
}

void Entity::moveText           ( const sf::Vector2f& offset    )   { mText.move(offset);               }   //moves the text

void Entity::setPos             ( const sf::Vector2f& pos       )   { mSprite.setPosition(pos);         }   //Sets the position of the sprite

void Entity::setRot             ( const int rot                 )   { mSprite.setRotation(rot);         }   //Sets the rotation of the sprite

void Entity::setColour          ( const sf::Color& c            )   { mSprite.setColor(c);              }   //Sets the colour of the sprite

void Entity::setOrigin          ( const sf::Vector2f& org       )   { mSprite.setOrigin(org);           }   //Sets the origin of the sprite

const sf::Vector2f Entity::getPos     () const                            { return mSprite.getPosition();     }   //Returns position of the sprite

const sf::Sprite Entity::getSprite    () const                            { return mSprite;                   }   //Returns the sprite itself
