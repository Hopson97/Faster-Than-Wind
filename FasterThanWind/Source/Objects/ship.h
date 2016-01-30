#ifndef SHIP_H
#define SHIP_H


#include "room.h"
#include "ResourceManagers/texturemanager.h"

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

class Ship
{
    public:
        explicit        Ship(TextureManager& textures);

        sf::Texture*    getTexture  (const RoomType roomType);

        sf::Vector2f    getPosition () const;

        void            update      (const float dt);
        void            draw        (sf::RenderWindow& window);
        void            setRooms    (const std::vector<Room> rooms);

        void            setTexture  (const sf::Texture& t);

        void            setPosition (const sf::Vector2f pos);

    private:
        void            registerRoomsToTextures (TextureManager& textures);



    private:
        std::map<RoomType, sf::Texture*> roomTextures;

        std::vector<Room>       mRooms;
        sf::Vector2f            mPosition;
        sf::Sprite              mShipSprite;
        sf::Texture             mCurrShipTexture;
};

#endif // SHIP_H
