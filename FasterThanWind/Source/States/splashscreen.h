#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H


#include <SFML/Graphics.hpp>

#include "state.h"
#include "game.h"

#include "entity.h"

namespace state
{

class SplashScreen : public State
{
    public:
        explicit    SplashScreen  ( Game* game );

        void        input           ( const float dt )      override {} //no input for splash screen!
        void        update          ( const float dt )      override;
        void        draw            ( const float dt )      override;

    private:
        void        ssInitial       ();
        void        ssDuring        (const float dt);
        void        ssOut           ();

    private:
        enum SplashState
        {
                SPSH_ST_INITIAL
            ,   SPSH_ST_DURING
            ,   SPSH_ST_OUT
        };


        sf::Texture                 logoTexture;
        Entity                      logoSprite;


        sf::RectangleShape          blackness;


        SplashState                 mSplashState;

        std::shared_ptr<sf::Music> windWakerSong;
};

}//Namespace state

#endif // SPLASHSCREEN_H
