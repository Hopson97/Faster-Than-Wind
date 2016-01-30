#include "editstate.h"

#include <fstream>

/*
=================================================================================================================================================================
Edit State is a state in this program that handles everything editing

constructor for a new ship
=================================================================================================================================================================
*/
EditState::EditState(Program* p, const std::string& filePath, const std::string& shipName, const sf::Texture& mShipTexture):
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

    std::cout << "Editor loaded" << std::endl;
}

/*
=================================================================================================================================================================
handle input such as clicking
=================================================================================================================================================================
*/
void EditState::input  ()
{
    mRoomMenuUI        .draw(mProgram->window());          //Needs to be put here because we can't see buttons under a scroll
    selectionHasChanged = mRoomMenuUI.checkButtonInput(mSelectedRoom, mProgram->window()); //Check if selected button has changed

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        save();
    }


    if (mMode == modeRoom)
    {
        roomInput();
        return;
    }
    else if (mMode == modeWall)
    {
        wallInput();
        return;
    }
}

/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
void EditState::update ()
{
    mGhost.logic(sf::Mouse::getPosition(mProgram->window()),                        //Do Ghost::logic()
                 mShipWidth, mShipHeight,
                 mProgram->window());

    if (mMode == modeRoom)
    {
        roomUpdate();
        return;
    }
    else if (mMode == modeWall)
    {
        wallUpdate();
        return;
    }

}

/*
=================================================================================================================================================================

=================================================================================================================================================================
*/
void EditState::draw   ()
{
    mProgram->window()                       .draw(mShipSprite);         //Draw the ship
    mShip                                    .draw(mProgram->window());  //Draw the rooms on the ship
    mGhost                                   .draw(mProgram->window());  //Draw the ghost/ selection rectangle

    mDotMap                                  .draw(mProgram->window());  //Draw the dot map
    mSwToWallMdeBtn                          .draw(mProgram->window());
    mSwToRoomMdeBtn                          .draw(mProgram->window());
    mCurrentlySelectedUI                             .draw(mProgram->window());  //Draw the currently selected stuffs
}

void EditState::roomInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)                                 //If left mouse button is pressed
       && !mGhost.isOutOfBounds(mShipWidth, mShipHeight)                            //and ghost is not out of bounds
       && !mGhost.isMouseOutOfBounds(mShipWidth, mShipHeight, mProgram->window()))  //and mouse is not out of bounds
    {
        mShip.addRoom(mSelectedRoom, mGhost.getRect());     //Add a room at location
    }

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)                                //If right mouse button is pressed
       && !mGhost.isOutOfBounds(mShipWidth, mShipHeight)                            //and ghost is not out of bounds
       && !mGhost.isMouseOutOfBounds(mShipWidth, mShipHeight, mProgram->window() ) ) ) { //and mouse is not out of bounds

        mShip.removeRoom(mGhost.getRect());                                         //Remove a room at location
        }

    if (mSwToWallMdeBtn.clicked(mProgram->window())) {
        mMode = modeWall;
        mGhost.updateRectSize(sf::Vector2f(2,38));
        mGhost.setMode(wall);
        std::cout << "Changing to wall mode. \n";

        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
         while(sf::Keyboard::isKeyPressed(sf::Keyboard::R));
         mShip.rotateRoom(mGhost.getRect());
    }
}

void EditState::roomUpdate()
{
    if (selectionHasChanged)  {
        selectionHasChanged = mCurrentlySelectedUI.updateSelected(mSelectedRoom,
                                                          mShip.getRoomTexture(mSelectedRoom)); //Update the "currently selected" scroll
        mGhost.updateRectSize(mShip.getRoomSize(mSelectedRoom));                                //Update ghosts size
        }

    if (mShip.roomPresent(mGhost.getRect() ) ) {                   //If a room is present at the location of the ghost
        mGhost.updateRectColour(sf::Color(255, 0, 0, 170));     //Change it's colour to red
        }
    else {                                                       //If no room is present
        mGhost.updateRectColour(sf::Color(0, 255, 0, 170));     //Change is to green
    }
}

void EditState::wallInput()
{
    if (mSwToRoomMdeBtn.clicked(mProgram->window() ) ) {
        mMode = modeRoom;
        mGhost.updateRectSize(mShip.getRoomSize(mSelectedRoom));                                //Update ghosts size
        mGhost.setMode(room);
        std::cout << "Changing to room mode \n";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::R));
        mGhost.rotate();

    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mShip.checkForWallorDoor(mGhost.getRect(), WT_WALL, WT_DOOR);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        mShip.checkForWallorDoor(mGhost.getRect(), WT_DOOR, WT_WALL);
    }

}

void EditState::wallUpdate()
{

}
