#ifndef SHIP_H
#define SHIP_H


#include "../room.h"
#include "../Unit/unit.h"
#include "ResourceManagers/texturemanager.h"

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

class Ship
{
    public:
        explicit        Ship(TextureManager& textures);

                void            update      (const float dt);
                void            draw        (sf::RenderWindow& window);

        const   sf::Texture&    getTexture  () const;
                sf::Texture*    getTexture  (const RoomType roomType);
                sf::Texture*    getTexture  (const UnitType unitType);

                void            setRooms    (const std::vector<Room> rooms);
                void            setUnits    (const std::vector<Unit> units);

                void            setTexture  (const sf::Texture& t);

                void            setPosition (const sf::Vector2f pos, const bool moving);
        const   sf::Vector2f    getPosition () const;
                void            translate   (const sf::Vector2f& offset, const float dt);

                void            setName     (const std::string& name);
        const   std::string&    getName     () const;

    private:
        void            registerRoomsToTextures (TextureManager& textures);
        void            registerUntisToTextures (TextureManager& textures);

    private:
        std::map<RoomType, sf::Texture*> roomTextures;
        std::map<UnitType, sf::Texture*> unitTextures;

        std::vector<Room>       mRooms;
        std::vector<Unit>       mUnits;

        sf::Vector2f            mPosition;
        sf::Sprite              mShipSprite;
        sf::Texture             mCurrShipTexture;

        std::string             shipName;
};

#endif // SHIP_H
