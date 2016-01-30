#include "ship.h"

#include <iostream>

#include "constants.h"

Ship::Ship(TextureManager& textures)
{
    registerRoomsToTextures( textures );
}

/**
=================================================================================================================================================================
*   registerRoomsToTextures()   sets up the std::map<room type, texture>
*   param1  :   the texture manager for the textures to point to
=================================================================================================================================================================
*/
void Ship::registerRoomsToTextures(TextureManager& textures)
{
    roomTextures[ RT_EMPTY_SMALL ]          = &textures.getTexture( RES_TXR_SP_RM_EMPTY_SMALL        );
    roomTextures[ RT_EMPTY_LARGE ]          = &textures.getTexture( RES_TXR_SP_RM_EMPTY_LARGE        );
    roomTextures[ RT_EMPTY_SMALL_WIDE ]     = &textures.getTexture( RES_TXR_SP_RM_EMPTY_SMALL_WIDE   );
    roomTextures[ RT_EMPTY_SMALL_TALL ]     = &textures.getTexture( RES_TXR_SP_RM_EMPTY_SMALL_TALL   );
    roomTextures[ RT_EMPTY_HUGE ]           = &textures.getTexture( RES_TXR_SP_RM_EMPTY_HUGE         );
    roomTextures[ RT_CANNON ]               = &textures.getTexture( RES_TXR_SP_RM_CANNON             );

}

/**
=================================================================================================================================================================
*   getTexture()    returns a texture for the rooms
*   param1  :   the RoomType that it will be returning
=================================================================================================================================================================
*/
sf::Texture* Ship::getTexture(const RoomType roomType)
{
    return roomTextures[ roomType ];
}

/**
=================================================================================================================================================================
*   getPosition() returns the position of the ship
=================================================================================================================================================================
*/
sf::Vector2f Ship::getPosition() const
{
    return mPosition;
}

/**
=================================================================================================================================================================
*   setRooms()  set the wall std::vector of the room aka "build the ships rooms"
*   param1  :   the vector that the ship will be build from
=================================================================================================================================================================
*/
void Ship::setRooms(const std::vector<Room> rooms)
{
    mRooms = rooms;
}

/**
=================================================================================================================================================================
*   draw()      draws the ships background texture and the rooms within
*   param1  :   window to draw the sprites to
=================================================================================================================================================================
*/
void Ship::draw(sf::RenderWindow& window)
{
    window.draw(mShipSprite);
    for(auto& room : mRooms)
    {
        room.draw(window);
    }
}

/**
=================================================================================================================================================================
*   setTexture()    sets the background texture of the ship
*   param1  :   the texture
=================================================================================================================================================================
*/
void Ship::setTexture(const sf::Texture& t)
{
    sf::Sprite s;               //Need to create a temporary sprite so that ship can change size
    s.setPosition(mPosition);   //Set the temporary sprite's position to that of the ship
    mShipSprite = s;            //Set the ships sprite to be that of the tempoary sprite.
    mCurrShipTexture = t;
    mShipSprite.setTexture(mCurrShipTexture);
}

/**
=================================================================================================================================================================
*   update()    update the ship eg the doors open/ closed state
*   param 1 :   the game's delta time
=================================================================================================================================================================
*/
void Ship::update(const float dt)
{
    for(auto& room : mRooms)
    {
        room.logic(dt);
    }
}

/**
=================================================================================================================================================================
*   setPosition()
*   param1  :   The new position for the sprite
=================================================================================================================================================================
*/
void Ship::setPosition (const sf::Vector2f pos)
{
    mShipSprite.setPosition(pos);
    mPosition = pos;
}

