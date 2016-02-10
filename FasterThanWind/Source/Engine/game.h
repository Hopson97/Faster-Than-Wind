#ifndef GAME_H
#define GAME_H

#include "ResourceManagers/texturemanager.h"
#include "ResourceManagers/soundmanager.h"
#include "statehandler.h"

#include <string>

#include "constants.h"

typedef std::shared_ptr<State> statePtr;

class State;
class Game
{
    public:
                                Game            ();
        void                    runGame         ();
        void                    windowEvents    ();

        void                    changeSong      (const std::string& filePath);

        TextureManager&         getTextures     ();        //"Get" resource manager
        SoundManager&           getSounds       ();
        sf::RenderWindow&       window          ();

        StateHandler&           getStates       (const bool clearResources);

        inline void             setClearColour  (const sf::Color& c)    { mClearColour = c;}

                sf::Music&       getMusic    () { return mMusic; }

    private:
        float                   deltaTime       (sf::Clock& clock);

    private:
        sf::RenderWindow    mWindow     { sf::VideoMode(win::WIDTH, win::HEIGHT), "Faster Than Wind", sf::Style::Close };
        TextureManager      mTextures;
        SoundManager        mSounds;

        StateHandler        mStates;

        sf::Color           mClearColour;

        sf::Music           mMusic;

        void quickload();
        void usualload();
};

#endif // GAME_H
