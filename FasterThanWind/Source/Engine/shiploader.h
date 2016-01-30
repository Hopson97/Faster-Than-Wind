#ifndef SHIPLOADER_H
#define SHIPLOADER_H

#include <vector>

#include "room.h"
#include "ship.h"

class ShipLoader
{
    public:
                ShipLoader  ();
        void    loadShip    (Ship* ship, const std::string& shipPath, TextureManager& textureManager);

    private:
        void    loadRoom    (std::ifstream& loader, TextureManager& textureManager);
        Room    addRoom     (std::ifstream& loader);
        Wall    addWall     (std::ifstream& loader, TextureManager& textureManager);

        void    matchUpDoors    ();


    private:
        std::vector<Room> mRooms;
        Ship* mShip;
};

#endif // SHIPLOADER_H
