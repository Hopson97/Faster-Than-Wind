#include "button.h"
#include <iostream>


namespace ui {

/*****************************************************************************************************************************************************************
*   Button is class that is a.. well a button that can be clicked.
*   param1 : takes in a texture for the button
*   param2  : takes in a positional vector for the button
***************************************************************************************************************************************************************/
Button::Button(const sf::Texture& texture, const sf::Vector2f& pos, sf::Sound& clickSound)
:   Entity( texture )
{
    _mSprite().setPosition( pos );   //Set position
    mClickSound = &clickSound;
}

Button::Button(const sf::Texture& texture, const sf::Vector2f& pos, const std::string& buttonText, const int textSize, const sf::Font& font, sf::Sound& clickSound)
:   Entity(texture, buttonText, pos, textSize, font)
{
    mClickSound = &clickSound;
}

/*****************************************************************************************************************************************************************
*   clicked() returns true if the button is clicked
*   param1 takes in the main game window so that mouse has something to be relative to
***************************************************************************************************************************************************************/
bool Button::clicked(sf::RenderWindow& window)
{
    window.draw( _mSprite() );
    if ( touchingMouse( window ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) )   // If clicked
    {
        if( !beenClicked ) {        //Conditional exists for the sake of the sound only plays once
            mClickSound->play();
            beenClicked = true;
        }
        _mSprite().setColor( sf::Color( 200, 200, 200, 255 ) );     //Change colour
        return true;
    }
    else if (touchingMouse( window) )                               //If mouse rolled over
    {
        _mSprite().setColor( sf::Color( 220, 220, 220, 255 ) );     //Change colour
        return false;
    }
    else
    {
        _mSprite().setColor( sf::Color( 255, 255, 255, 255 ) );     //Go to default colour
        beenClicked = false;
        return false;
    }
}


/*****************************************************************************************************************************************************************
*   touchingMouse() returns true if the button is touching the mouse
*   param1 : takes in the main game window so that mouse has something to be relative to
***************************************************************************************************************************************************************/
bool Button::touchingMouse(sf::RenderWindow& window)
{
    sf::IntRect bound( _mSprite().getLocalBounds() );            //For getting button size
    sf::Vector2i mouse( sf::Mouse::getPosition(window) );     //Location of mouse relative to window

    if (mouse.x > _mSprite().getPosition().x                   //If mouse is to the right of the button
        &&                                                  //and
        mouse.x < _mSprite().getPosition().x + bound.width     //If mouse is to the left of the button
        &&                                                  //and
        mouse.y > _mSprite().getPosition().y                   //If mouse is below of the button
        &&                                                  //and
        mouse.y < _mSprite().getPosition().y + bound.height)   //If mouse is above the button
        {
            return true;                                    //Return true
        }
        else
        {
            return false;                                   //Else, return false
        }
}

}//namespace ui
