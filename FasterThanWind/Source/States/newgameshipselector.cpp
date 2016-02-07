#include "newgameshipselector.h"

#include "mainmenu.h"
#include <string>
#include <iostream>

#include "constants.h"
#include "toStr.h"

#include "play_stationary.h"

namespace state {

NewGameShipSelector::NewGameShipSelector(Game* game,  TextureManager& manager)
:   State                   ( game    )
,   LIST_BUTTON_Y           ( 100     )
,   mCurrentShipNumber      ( 0       )
,   mCurrentShip            ( manager )
,   shipYardLogo            ( game->getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL                                              ) )
,   mPrevShipButton         ( game->getTextures().getTexture( RES_TXR_NEWGAME_PREV_ARROW ), sf::Vector2f( 0,    LIST_BUTTON_Y      ) )
,   mListButtonText         ( game->getTextures().getTexture( RES_TXR_NEWGAME_LIST_ICON                                            ) )
,   mNextShipButton         ( game->getTextures().getTexture( RES_TXR_NEWGAME_NEXT_ARROW ), sf::Vector2f( 399,  LIST_BUTTON_Y      ) )
,   mLayout1Button          ( game->getTextures().getTexture( RES_TXR_GBL_SMALL_SCROLL   ), sf::Vector2f( win::WIDTH - 570,    LIST_BUTTON_Y      ), "Layout 1" )
,   mLayout2Button          ( game->getTextures().getTexture( RES_TXR_GBL_SMALL_SCROLL   ), sf::Vector2f( win::WIDTH - 380,    LIST_BUTTON_Y      ), "Layout 2" )
,   mLayout3Button          ( game->getTextures().getTexture( RES_TXR_GBL_SMALL_SCROLL   ), sf::Vector2f( win::WIDTH - 190,    LIST_BUTTON_Y      ), "Layout 3" )
,   mConfirmSelectionButton ( game->getTextures().getTexture( RES_TXR_GBL_SMALL_SCROLL   ), sf::Vector2f( win::WIDTH - 190,    win::HEIGHT - 100  ), "Select Ship")
,   mBackToMainMenuButton   ( game->getTextures().getTexture( RES_TXR_GBL_SMALL_SCROLL   ), sf::Vector2f( 0, 0                                    ), "\t  Back to \n Main Menu" )
,   mCurrentLayout          ( 1, 3, 1) //Ranged num, 1 - 3, starting value = 1
{
    shipYardLogo.setPos(sf::Vector2f(win::WIDTH / 2 - shipYardLogo.getSprite().getLocalBounds().width / 2,
                                           0));
    shipYardLogo.setUpText( "Ship Yard", shipYardLogo.getSprite().getPosition() );

    mListButtonText.setPos( sf::Vector2f( 97, LIST_BUTTON_Y ) );

    setUpButtons();
    addEntitysToVector();
    addShipsToVector();

    shipString = mshipNameList[0];


    mCurrentShip.setPosition(sf::Vector2f((win::WIDTH  / 2) - ship::WIDTH,
                             (win::HEIGHT / 2) - 50),
                             false);
    resetShip();
}

/*****************************************************************************************************************************************************************
*   input() handle input of this class
*   param1  :   games's delta time
***************************************************************************************************************************************************************/
void NewGameShipSelector::input (const float dt)
{
    if ( mPrevShipButton.clicked ( _mGame().window() ) ) {
        changeCurrentShip(-1);
    }
    if ( mNextShipButton.clicked ( _mGame().window() ) ) {
        changeCurrentShip(1);
    }

    if ( mLayout1Button.clicked ( _mGame().window() ) ) {
        mCurrentLayout.setValue( 1 );
        resetShip();
    }
    if ( mLayout2Button.clicked ( _mGame().window() ) ) {
        mCurrentLayout.setValue( 2 );
        resetShip();
    }
    if ( mLayout3Button.clicked ( _mGame().window() ) ) {
        mCurrentLayout.setValue( 3 );
        resetShip();
    }
    if ( mConfirmSelectionButton.clicked( _mGame().window() ) ) {
        _mGame().getStates(false).changeState(std::make_shared<Play_Stationary>( &_mGame(), mCurrentShip));
    }
    if ( mBackToMainMenuButton.clicked( _mGame().window() ) ) {
        _mGame().getStates(false).popState();
    }
}

/*****************************************************************************************************************************************************************
*   update()    update this states objects
*   param1  :   games's delta time
***************************************************************************************************************************************************************/
void NewGameShipSelector::update (const float dt)
{
    mCurrentShip.update(dt);
    if ( mCurrentLayout.getValue() == 1 ) {
        mLayout1Button.setColour( col::SELECTED );
    }
    else if ( mCurrentLayout.getValue() == 2 ) {
        mLayout2Button.setColour( col::SELECTED );
    }
    else if ( mCurrentLayout.getValue() == 3 ) {
        mLayout3Button.setColour( col::SELECTED );
    }


    if ( mCurrentShip.getPosition().x > win::WIDTH ) mCurrentShip.translate({-100000, 0.0f}, dt);
    else mCurrentShip.translate({100.0f, 0.0f}, dt);

}

/*****************************************************************************************************************************************************************
*   draw()  draw this states sprites
*   param1  :   games's delta time
***************************************************************************************************************************************************************/
void NewGameShipSelector::draw (const float dt)
{
    for ( auto& entity : mEntities )
    {
        entity->draw    ( _mGame().window() );
    }
    mCurrentShip.draw   (  _mGame().window()    );
}

/*****************************************************************************************************************************************************************
*   changeCurrentShip() changes the current ship name
*   param1  :   The amount to increment the ship number by (1 or -1)
***************************************************************************************************************************************************************/
void NewGameShipSelector::changeCurrentShip(const int increment)
{
    if ( !(increment >  -1) && !(increment < 1) ) {     //Check if increment is within range
        return;
    }

    mCurrentShipNumber += increment;                    //If it is, then increment/ decrement the amount by the argument

    if ( mCurrentShipNumber < 0 ) {             //Check if the current ship number is less than than zero
        mCurrentShipNumber = 0;                 //If it is, then it means something is wrong and resets the number and returns
        return;
    }

    if ( ( unsigned int ) mCurrentShipNumber > mshipNameList.size() - 1 ) { //Check if the current ship number is greater than the ship list size
        mCurrentShipNumber = mshipNameList.size();                          //If it is, then it means something is wrong and resets the number and returns
        return;
    }

    shipString = mshipNameList[mCurrentShipNumber]; //If all the error checks pass, then change the current ship and reset it
    mCurrentLayout.setValue(1);
    resetShip();
}

/*****************************************************************************************************************************************************************
*   resetShip() resets the ship by loading a new one from the ship loader.
***************************************************************************************************************************************************************==
*/
void NewGameShipSelector::resetShip()
{
    mShipLoader.loadShip( &mCurrentShip, "Resources/Ship Info/" + shipString + util::toString(mCurrentLayout.getValue()) + ".ship", _mGame().getTextures() );
}

/*****************************************************************************************************************************************************************
*   setUpLayoutButtons() is a constructor only method that sets up the buttons that allow the player so choose the ship's layout
***************************************************************************************************************************************************************==
*/
void NewGameShipSelector::setUpButtons()
{
    const   int             LAYOUT_BTN_TEXT_SIZE = 30;

    mLayout1Button.setTextSize  ( LAYOUT_BTN_TEXT_SIZE );
    mLayout2Button.setTextSize  ( LAYOUT_BTN_TEXT_SIZE );
    mLayout3Button.setTextSize  ( LAYOUT_BTN_TEXT_SIZE );

    mConfirmSelectionButton.setTextSize     ( LAYOUT_BTN_TEXT_SIZE );
    mConfirmSelectionButton.moveText        ( sf::Vector2f(-10, 10 ) );


    mBackToMainMenuButton.setTextSize   ( 23 );
    mBackToMainMenuButton.moveText      ( sf::Vector2f(-10, 35 ) );
}

/*****************************************************************************************************************************************************************
*   addShipsToVector() is a constructor only method that sets up the list of which is the ships name
***************************************************************************************************************************************************************==
*/
void NewGameShipSelector::addShipsToVector()
{
    mshipNameList.push_back( "StarterShip" );
    mshipNameList.push_back( "Ship" );
}

/*****************************************************************************************************************************************************************
*   addEntitysToVector() is a constructor only method that adds all the entities into the entity list vector (for the this->draw() )
***************************************************************************************************************************************************************/
void NewGameShipSelector::addEntitysToVector()
{
    mEntities.push_back( &shipYardLogo    );  //Add the ship yard logo to the entity list

    mEntities.push_back( &mPrevShipButton );  //Add the ship selection entities to the entity list
    mEntities.push_back( &mNextShipButton );
    mEntities.push_back( &mListButtonText );

    mEntities.push_back( &mLayout1Button  );   //Add layout buttons to the entity list
    mEntities.push_back( &mLayout2Button  );
    mEntities.push_back( &mLayout3Button  );

    mEntities.push_back( &mConfirmSelectionButton);

    mEntities.push_back( &mBackToMainMenuButton );
}


}
