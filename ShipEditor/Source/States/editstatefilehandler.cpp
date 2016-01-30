#include "editstate.h"

#include <string>
#include <sstream>

/*
=================================================================================================================================================================
Edit State is a state in this program that handles everything editing

constructor for loading a ship
=================================================================================================================================================================
*/
EditState::EditState(Program* p, const std::string& filePath, const std::string& shipName, const sf::Texture& mShipTexture, const std::string& infoFile):
    State                   (p),                                                        //Parent constructor
    mDotMap                 (mShipTexture),                                             //Constructors
    mTextures               (filePath),
    mShipHeight             (mDotMap.getDotMapDimensions().y),
    mShipWidth              (mDotMap.getDotMapDimensions().x),
    mShip                   (mTextures, mShipWidth, mShipHeight, filePath),
    mCurrentlySelectedUI    (mTextures.getTexture(RES_TXR_CURRENTLY_SELECTED), mTextures),
    mRoomMenuUI             (mTextures.getTexture(RES_TXR_ROOM_MENU), mTextures),
    mSelectedRoom           (RT_EMPTY_SMALL),
    mMode                   (modeRoom),
    mSwToWallMdeBtn         (mTextures.getTexture(RES_TXR_BTN_SWITCH_TO_WALL_MODE), sf::Vector2f(750, 0)),
    mSwToRoomMdeBtn         (mTextures.getTexture(RES_TXR_BTN_SWITCH_TO_ROOM_MODE  ), sf::Vector2f(750, 60)),
    mShipName               (shipName)
{
    selectionHasChanged = false;
    mCurrentlySelectedUI.updateSelected(mSelectedRoom, mShip.getRoomTexture(mSelectedRoom));
    mShipSprite.setTexture(mTextures.getTexture(RES_TXR_SHIP));  //Set the background ship texture to the texture just loaded
    load(infoFile);
    std::cout << "Editor loaded" << std::endl;
}

void EditState::save()
{
    std::cout << "What layout is this ship: 1, 2 or 3? \n";
    int layout;
    std::cin >> layout;

    std::stringstream conv;
    conv << layout;
    std::string layoutString = conv.str();

    std::ofstream file("../FasterThanWind/Resources/Ship Info/" + mShipName + layoutString + ".ship");

    file << mShip.getTxrFilePath() << "\n";                             //File path for editor  (texture)
    file << "Resources/Textures/Ships/" + mShipName + ".png\n";     //File path for game    (texture), ignored by editor

    for(auto& room : mShip.getRoomMap())
    {
            file << "r \t"                                 << " r\t";
            file << room.pos().x                       << "\t";
            file << room.pos().y                       << "\t";
            file << room.getSprite().getRotation()     << "\t";
            file << room.getType()                     << "\n";
            for(auto& wall : room.getWalls())
            {
                file << "w"                             << "\t";
                file << wall->getPos().x                << "\t";
                file << wall->getPos().y                << "\t";
                file << wall->getRot()                  << "\t";
                file << wall->getId ()                  << "\t";
                file << wall->getOtherId()              << "\t";
                file << wall->getType()                 << "\n";
            }
    }
    file.close();
    std::cout << "Saved." << std::endl;

}

void EditState::load(const std::string& filePath)
{
    std::ifstream shipFile(filePath);
    std::string r;

    shipFile >> r;  //To read/ skip the file path
    shipFile >> r;   //To read/ skip the file path
    shipFile >> r;   //To read/ skip the first "r" in the file.
    std::vector<Room> rooms;


    while (shipFile >> r) {
        if (r == "r") {                                                                 //If it reads an "r"
            std::vector<std::shared_ptr<Wall>> walls;
            loadRoom(shipFile, rooms, walls);    //It means a room, so said room is loaded.
        }

    }

    connectDoors(rooms);
    std::cout << "Finished loading!" << std::endl;
    mShip.setRooms(rooms);
    shipFile.close();
}

void EditState::loadRoom(std::ifstream& shipFile, std::vector<Room>& rooms, std::vector<std::shared_ptr<Wall>>& walls)
{
    std::string r;
    Room room =  addRoom(shipFile);   //Create a room
    while(true) //aka while finding walls
    {
        shipFile >> r;
        if(shipFile.eof())  //If end of file, return.
        {

            room.setWalls(walls);
            rooms.push_back(room);
            return;
        }
        if(r == "r")                //If it's a new room, then finalise the room and push it into the vector
        {

            room.setWalls(walls);
            rooms.push_back(room);
            return;
        }
        if(r == "w")                //Read the walls
        {
            addWall(walls, shipFile);
            continue;
        }
    }//Room found
}

Room EditState::addRoom(std::ifstream& shipFile)
{
    int xPos, yPos, rot, type;
    shipFile >> xPos >> yPos >> rot >> type;
    if ( type == 0 ) std::cout << "i am door lol" << std::endl;
    return Room(
                mShip.getRoomTexture(static_cast<RoomType>(type)),
                static_cast<RoomType>(type),
                xPos,
                yPos,
                mShip.getRoomSize(static_cast<RoomType>(type) ),
                rot
                );
}

void EditState::addWall(std::vector<std::shared_ptr<Wall>>& walls, std::ifstream& shipFile)
{
    int xPos, yPos, rot, type, id, otherId;
    shipFile >> xPos >> yPos >> rot >> id >> otherId >> type;
    walls.emplace_back(std::make_shared<Wall>(
                                                (rot == 0)? dirVertical: dirHorizontal,
                                                xPos,
                                                yPos,
                                                (type == 0) ? WT_DOOR : WT_WALL,
                                                id,
                                                otherId)
                                                );
}




void EditState::connectDoors(std::vector<Room>& rooms)
{
    std::vector<std::shared_ptr<Wall>> wallInfo;        //Vector of shared pointers of Wall
    for(auto& room : rooms)
    {
        for(auto& wall : room.getWalls())
        {
            if(wall->getOtherId() != 0)
            {
                wallInfo.push_back(wall);
            }
        }
    }

    for(auto& room : rooms)
    {
        for(auto& wall : room.getWalls())
        {
            if(wall->getOtherId() != 0)
            {
                for(auto& wall2 : wallInfo)
                {
                    if(wall->getOtherId() == wall2->getId())
                    {
                        wall->setOtherWall(wall2);
                        wall2->setOtherWall(wall);
                    }
                }
            }
        }
    }
}

/*
        .ship file layout:
                            file path to ship texture
                            file path to ship texture (for game)
                            rooms: X position, Y position, Rotation, Type
                            walls: X position, Y position, Rotation, The ID of this wall, The ID of the other wall, Type

        For example:    ../FasterThanWind/Resources/Textures/Ships/Ship.png
                        Resources/Textures/Ships/Ship.png
                        r 	 r	0	0	0	0               room
                        w	0	1	270	1	3	0           wall
                        w	0	40	270	2	105	0           wall
                        w	0	-1	0	3	1	0           wall
                        w	39	0	0	4	0	1           wall
                        r 	 r	2	0	0	0               room
                        w	80	1	270	9	0	1           wall
                        w	80	40	270	10	0	1           wall
                        w	80	-1	0	11	0	1           wall
                        w	119	0	0	12	0	1           wall

*/











