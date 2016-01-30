#include "roommenu.h"

/*
=================================================================================================================================================================
This class is a scroll window which displays the different rooms for using.
=================================================================================================================================================================
*/
RoomMenu::RoomMenu(const sf::Texture& bottomMenuTexture, TextureManager& textures)
: Object(bottomMenuTexture)
, x(45)
, y(365)
, emptyRoomSmButton     (textures.getTexture(RES_TXR_ROOMS_EMPTY_SM),    sf::Vector2f(x, y))   //Button
, emptyRoomLgButton     (textures.getTexture(RES_TXR_ROOMS_EMPTY_LG),    sf::Vector2f(x + 45 * 1, y)             )
, emptyRoomSmWdButton   (textures.getTexture(RES_TXR_ROOMS_EMPTY_SM_WD),   sf::Vector2f(x + 45 * 3, y)             )
, emptyRoomSmTlButton   (textures.getTexture(RES_TXR_ROOMS_EMPTY_SM_TL),   sf::Vector2f(x + 45 * 5, y)             )
, emptyRoomHugeButton   (textures.getTexture(RES_TXR_ROOMS_EMPTY_HG),     sf::Vector2f(x + 45 * 7, y)             )
, cannonRoomUpButton    (textures.getTexture(RES_TXR_ROOMS_CANNON),      sf::Vector2f(x + 45 * 1, y + 160 * 1)   )
{
    mSprite.setPosition(0, 340);

}

/*
=================================================================================================================================================================
each item on the menu is a button, this checks if one of those is clicked
=================================================================================================================================================================
*/
bool RoomMenu::checkButtonInput(RoomType& rS, sf::RenderWindow& window)
{
    if (emptyRoomSmButton.clicked(window) ) {     //If "empty small room select" clicked
        rS = RT_EMPTY_SMALL;                      //Set room type to "room type empty small"
        return true;                            //Return true
    }

    if (emptyRoomLgButton.clicked(window) ) {
        rS = RT_EMPTY_LARGE;
        return true;
    }

    if (emptyRoomSmWdButton.clicked(window) ) {
        rS = RT_EMPTY_SMALL_WIDE;
        return true;
    }

    if (emptyRoomSmTlButton.clicked(window)) {
        rS = RT_EMPTY_SMALL_TALL;
        return true;
    }

    if (emptyRoomHugeButton.clicked(window))
    {
        rS = RT_EMPTY_HUGE;
        return true;
    }

    if(cannonRoomUpButton.clicked(window))
    {
        rS = RT_CANNON;
        return true;
    }


    return false;
}
