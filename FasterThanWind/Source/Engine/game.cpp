#include "game.h"

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "splashscreen.h"
#include "mainmenu.h"

#include "constants.h"

Game::Game()
: mWindow(sf::VideoMode(win::WIDTH, win::HEIGHT), "Faster Than Wind", sf::Style::Close, sf::ContextSettings(8)) //Window Constructor
{
    mWindow.setPosition(sf::Vector2i(-1300, 0) );
    mWindow.setFramerateLimit(win::FRAME_RATE_LIMIT);

    quickload();
    //usualload();
}

void Game::quickload()
{
    mTextures.loadTexturesSS();
    mTextures.loadTexturesMenu();
    mTextures.loadTexturesRooms();
    mTextures.loadTexturesNewGame();
    mStates.changeState(std::make_shared<state::MainMenu>( this ) );
}

void Game::usualload()
{
    mTextures.loadTexturesSS();
    sf::Thread loader   (&TextureManager::loadTexturesMenu,         &mTextures);
    sf::Thread loader2  (&TextureManager::loadTexturesRooms,        &mTextures);
    sf::Thread loader3  (&TextureManager::loadTexturesNewGame,      &mTextures);


    loader.launch   ();
    loader2.launch  ();
    loader3.launch  ();
    mStates.changeState(std::make_shared<state::SplashScreen>( this ) );
}

/**
=================================================================================================================================================================
*    runGame() defines the main loop of the game
=================================================================================================================================================================
*/
void Game::runGame()
{
    sf::Clock c;                                    //Clock will be used to work out "delta time" aka time between frames
    changeSong("Resources/Music/windwaker.ogg");
    mMusic.setVolume(1);


    while(mWindow.isOpen())
    {
        mWindow.clear(mClearColour);
        float dt = deltaTime( c );

        mStates.getState()->input  ( dt );      //Do the input logic   of the current state
        mStates.getState()->update ( dt );      //Do the input update  of the current state
        mStates.getState()->draw   ( dt );      //Do the input drawing of the current state

        mWindow.display();                  //Display whatever has been drawn to the window
        windowEvents();
    }
    mMusic.stop();
}

/**
=================================================================================================================================================================
*   getStates() returns the states of the game, primarily for the purpose of the game states
*   param1  : boolean asking the caller of said function if it wishes to clear the resources
=================================================================================================================================================================
*/
StateHandler& Game::getStates(const bool clearResources)
{
    if(clearResources) {
        //mResourceManager.clearAll();
    }

    return mStates;
}

/**
=================================================================================================================================================================
*   window() returns the window so that it is able to be used for the purpose of drawing sprites and other things to the game window
=================================================================================================================================================================
*/
sf::RenderWindow& Game::window  ()
{
    return mWindow;                         //Returns the game window        (as a reference)
}

/**
=================================================================================================================================================================
*   deltaTime() calculates and returns "delta time" aka time since the previous game frame
=================================================================================================================================================================
*/
float Game::deltaTime(sf::Clock& clock)
{
    sf::Time t = clock.restart();
    return t.asSeconds();
}

/**
=================================================================================================================================================================
*   changeSong()

PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE # PLEASE CHANGE #
=================================================================================================================================================================
*/
void Game::changeSong(const std::string& filePath)
{
    if(mMusic.Playing)
        mMusic.stop();

     mMusic.openFromFile(filePath);

     mMusic.play();
}


/**
=================================================================================================================================================================
*   getTextures() returns the texture manager
=================================================================================================================================================================
*/
TextureManager& Game::getTextures()
{
    return mTextures;                //Returns the resource manager  (as a reference)
}


/**
=================================================================================================================================================================
*   gteSounds() returns the sound manager
=================================================================================================================================================================
*/
SoundManager& Game::getSounds()
{
    return mSounds;                //Returns the resource manager  (as a reference)
}

/**
=================================================================================================================================================================
*   windowEvents() checks for events such as window closure, and handles them
=================================================================================================================================================================
*/
void Game::windowEvents()
{
    sf::Event e;                            //Create a variable to handle window events
    while (mWindow.pollEvent(e)) {          //While the window polls events...
        if (e.type == sf::Event::Closed) {  // if the event type is closed (aka, red cross button)
            mWindow.close();                // the close the window.
        }
    }
}


