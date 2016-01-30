#ifndef EDITSTATE_H
#define EDITSTATE_H

#include <memory>

#include "../Editor/ShipObjects/ship.h"

#include "../texturemanager.h"
#include "../program.h"
#include "../Editor/dotmap.h"
#include "../Editor/ghost.h"
#include "../Editor/UI/currentlyselected.h"
#include "../Editor/UI/roommenu.h"
#include "../Editor/UI/button.h"

#include "state.h"

#include <fstream>

enum Mode
{
    modeWall,
    modeRoom
};


class EditState : public State
{
    public:
                EditState       (Program* p, const std::string& filePath, const std::string& shipName, const sf::Texture& mShipTexture, const std::string& infoFile);
                EditState       (Program* p, const std::string& filePath, const std::string& shipName, const sf::Texture& mShipTexture);

        void    input           () override;
        void    update          () override;
        void    draw            () override;

    private:
        void    roomInput       ();
        void    wallInput       ();

        void    roomUpdate      ();
        void    wallUpdate      ();

//Methods up the next "private:" are to do with file handling.
        void    save            ();

        void                        load            (const std::string& filePath);

        void                        loadRoom        (std::ifstream& shipFile, std::vector<Room>& rooms, std::vector<std::shared_ptr<Wall>>& walls);

        Room                        addRoom         (std::ifstream& shipFile);
        void                        addWall         (std::vector<std::shared_ptr<Wall>>& walls, std::ifstream& shipFile);

        void                        connectDoors    (std::vector<Room>& rooms);

    private:

        sf::Sprite          mShipSprite;

        DotMap              mDotMap;
        TextureManager      mTextures;
        Ghost               mGhost;

        int                 mShipHeight, mShipWidth;

        Ship                mShip;
        CurrentlySelected   mCurrentlySelectedUI;
        RoomMenu            mRoomMenuUI;



        RoomType            mSelectedRoom;
        bool                selectionHasChanged;

        Mode mMode;

        Button              mSwToWallMdeBtn;
        Button              mSwToRoomMdeBtn;

        std::string         mShipName;



};

#endif // EDITSTATE_H
