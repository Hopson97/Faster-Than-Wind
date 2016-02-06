#include "mainmenu.h"

#include <iostream>

#include "newgameshipselector.h"
#include "constants.h"

namespace state {

MainMenu::MainMenu( Game* game )
:   State               ( game )
,   mBackground         ( game->getTextures()     .getTexture( RES_TXR_MENU_BACKGROUND             )   )
,   mLogo               ( game->getTextures()     .getTexture( RES_TXR_LOGO_FTW                    )   )
,   mNewGameButton      ( game->getTextures()     .getTexture( RES_TXR_GBL_LONG_SCROLL   ),  sf::Vector2f( (win::WIDTH/2) -
                                                                                                            game->getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL).getSize().x / 2,
                                                                                                            50 - 45 ),
                                                                                                            "New Game")

,   mContinueButton     ( game->getTextures()     .getTexture( RES_TXR_GBL_LONG_SCROLL   ),  sf::Vector2f( (win::WIDTH/2) -
                                                                                                            game->getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL).getSize().x / 2,
                                                                                                            140 - 45 ),
                                                                                                            "Continue Game")
{
    mLogo.centerOrigin(sf::Vector2f( win::WIDTH  / 2,
                                     win::HEIGHT / 2 ) );

    mLogo.        setToRandColour();

    _mGame().setClearColour(col::YELLOWY);    //Colour value for a old paper look

    //click.setBuffer( _mGame().getSounds().getSound(RES_SOUND_GBL_CLICK) );
}

/**
=================================================================================================================================================================
*   input() handle input of this class
*   param1  :   games's delta time
=================================================================================================================================================================
*/
void MainMenu::input(const float dt)
{
    if ( mNewGameButton.clicked( _mGame().window() ) ) {
        _mGame().getStates(true).pushState( std::make_shared<state::NewGameShipSelector>( &_mGame(), _mGame().getTextures() ) );
        //click.play();
    }
    if ( mContinueButton.clicked( _mGame().window() ) ) {
        //continue
        //click.play();
    }
}

/**
=================================================================================================================================================================
*   update()    update this states objects
*   param1  :   games's delta time
=================================================================================================================================================================
*/
void MainMenu::update(const float dt)
{
    mLogo.dance(dt);
}

/**
=================================================================================================================================================================
*   draw()  draw this states sprites
*   param1  :   games's delta time
=================================================================================================================================================================
*/
void MainMenu::draw(const float dt)
{
    mBackground     .draw( _mGame().window() );
    mNewGameButton  .draw( _mGame().window() );
    mContinueButton .draw( _mGame().window() );
    mLogo           .draw( _mGame().window() );
}

} //name space state
