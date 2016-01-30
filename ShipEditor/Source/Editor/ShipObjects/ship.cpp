#include "ship.h"

/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
Ship::Ship(TextureManager& textures, const int width, const int height, const std::string& path)
:   mFilePath(path)
{
    setRoomDatabase(textures);
}

/*
=================================================================================================================================================================
addRoom() takes in a room type and a set of x and y co-ordinates and then places a room there (if possible)
=================================================================================================================================================================
*/
void Ship::addRoom(const RoomType rt, const sf::RectangleShape& rect)
{
    int xPos = rect.getPosition().x / 40;
    int yPos = rect.getPosition().y / 40;

    if (mRoomMap.size() == 0){                                                 //If the map is empty
        mRoomMap.emplace_back(Room(getRoomTexture(rt), rt, xPos, yPos, getRoomSize(rt), 0));    //Add room
        return;
    }

    if (roomPresent(rect)){
        return;
    }

    mRoomMap.emplace_back(Room(getRoomTexture(rt), rt, xPos, yPos, getRoomSize(rt), 0));
}

/*
=================================================================================================================================================================
removeRoom() removes a room (if there is one) at the location of the ghost/ mouse
=================================================================================================================================================================
*/

void Ship::removeRoom(const sf::RectangleShape& rect)
{
    for (unsigned int tId = 0; tId < mRoomMap.size(); tId++){                  //Go through each room
        if (mRoomMap[tId].getSprite().getGlobalBounds().intersects(rect.getGlobalBounds())){   //If intersecting between room and selection rectangle
            for(auto& wall : mRoomMap[tId].getWalls()) {           //Go through the walls of the room
                if (wall->getType() == WT_DOOR) {                  //If the wall is a door
                    wall->getOtherWall().setType(WT_WALL);        //Set it's neighbouring door into a wall
                    wall->getOtherWall().setOtherId(0);            //Set it's "other ID" to 0, as it no longer has a neighbour door
                }//if
            }//for
            mRoomMap.erase(mRoomMap.begin() + tId);                 //Remove it.
        }//if
    }//for
}

/*
=================================================================================================================================================================
roomPresent() returns true if there is a room intersecting the rectangle passed in
=================================================================================================================================================================
*/
bool Ship::roomPresent(const sf::RectangleShape& rect)
{
    for(auto& room : mRoomMap)
    {
        if(room.getSprite().getGlobalBounds().intersects(rect.getGlobalBounds())){
            return true;
        }
    }

    return false;
}


/*
=================================================================================================================================================================
checkForWallOrDoor()

Basically, this method checks how many walls are within the rectangle passed in. (which is the ghost rectangle)

Every time it find a wall `numWalls` gets incremented by one. Depending on the number of walls found within the range:  if less than 2, nothing happens
                                                                                                                        if 2, change both to be doors.
=================================================================================================================================================================
*/
void Ship::checkForWallorDoor(const sf::RectangleShape& rect, const WallOrDoor checkingFor, const WallOrDoor changingTo)
{
    std::shared_ptr<Wall> wall1;      //Pointer to first wall
    std::shared_ptr<Wall> wall2;      //Pointer to second wall

    int numWalls = 0;                           //Number of walls detected

    for (auto& room : mRoomMap) {               //For each room in the ship
        for (auto& wall : room.getWalls()) {       //iterate though each wall of said room

            if (wall->getType() == checkingFor)  {      //If the type of room is the room being checked for

                if(rect.getGlobalBounds().intersects(wall->getRect().getGlobalBounds() ) ) {    //and has an intersection with the "ghost"

                    numWalls++;                     //Increase the number of walls this is true to by 1
                    if (numWalls == 1) {            //If the number of walls this is true to in the loop is equal to 1
                        wall1 = wall;               //Set the wall1 pointer to point to the wall
                    }
                    else if (numWalls == 2) {       //If the number of walls this is true to in the loop is equal to 2
                        wall2 = wall;               //Set the wall2 pointer to point to the second wall
                    }
                }//Intersection check end
            }//Type of wall check end
        }//For each wall loop end
    }//For each room loop end

    if (numWalls == 2) {                //If two rooms were checked
        wall1->setType(changingTo);     //Set the first room to be a door
        wall2->setType(changingTo);     //Do for second room as well

        wall1->setOtherWall(wall2);
        wall2->setOtherWall(wall1);

        wall1->setOtherId   (wall2->getId());
        wall2->setOtherId   (wall1->getId());
    }
}

/*
=================================================================================================================================================================
draw the ship
=================================================================================================================================================================
*/
void Ship::draw(sf::RenderWindow& window)
{
    for (auto& room: mRoomMap){
        room.draw(window);
    }
}

/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
void Ship::setRoomDatabase(TextureManager& textures)
{
    roomTextures[RT_EMPTY_SMALL]        = textures.getTexture(RES_TXR_ROOMS_EMPTY_SM);
    roomSizes   [RT_EMPTY_SMALL]        = sf::Vector2f(40, 40);

    roomTextures[RT_EMPTY_LARGE]        = textures.getTexture(RES_TXR_ROOMS_EMPTY_LG);
    roomSizes   [RT_EMPTY_LARGE]        = sf::Vector2f(80, 80);

    roomTextures[RT_EMPTY_SMALL_WIDE]   = textures.getTexture(RES_TXR_ROOMS_EMPTY_SM_WD);
    roomSizes   [RT_EMPTY_SMALL_WIDE]   = sf::Vector2f(80, 40);

    roomTextures[RT_EMPTY_SMALL_TALL]   = textures.getTexture(RES_TXR_ROOMS_EMPTY_SM_TL);
    roomSizes   [RT_EMPTY_SMALL_TALL]   = sf::Vector2f(40, 80);

    roomTextures[RT_EMPTY_HUGE]         = textures.getTexture(RES_TXR_ROOMS_EMPTY_HG);
    roomSizes   [RT_EMPTY_HUGE]         = sf::Vector2f(160, 160);

    roomTextures[RT_CANNON]             = textures.getTexture(RES_TXR_ROOMS_CANNON);
    roomSizes   [RT_CANNON]             = sf::Vector2f(80, 80);
}



/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
sf::Texture& Ship::getRoomTexture(RoomType roomT)
{
    return roomTextures[roomT];
}

/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
sf::Vector2f Ship::getRoomSize(RoomType roomT)
{
    return roomSizes[roomT];
}

void Ship::rotateRoom(const sf::RectangleShape& rect)
{
    for (auto& room : mRoomMap) {
        if(room.getSprite().getGlobalBounds().intersects(rect.getGlobalBounds())) {
            room.rotate();
        }
    }
}

std::string& Ship::getTxrFilePath ()
{
    return mFilePath;
}


std::vector<Room>& Ship::getRoomMap()
{
    return mRoomMap;
}

 void Ship::setRooms(const std::vector<Room>& rooms)
 {
     mRoomMap = rooms;
 }















