#ifndef ROOMMENU_H
#define ROOMMENU_H



#include "../ShipObjects/room.h"

#include "../../texturemanager.h"

#include "../object.h"

#include "button.h"


class RoomMenu : public Object
{
    public:
        RoomMenu(const sf::Texture& bottomMenuTexture, TextureManager& textures);

        bool checkButtonInput(RoomType& rS, sf::RenderWindow& window);  //Check to see if any of the buttons are pressed

    private:
        int x, y;
        Button emptyRoomSmButton;
        Button emptyRoomLgButton;
        Button emptyRoomSmWdButton;
        Button emptyRoomSmTlButton;
        Button emptyRoomHugeButton;
        Button cannonRoomUpButton;
};

#endif // ROOMMENU_H
