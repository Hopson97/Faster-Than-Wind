#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Engine/game.h"
#include "Engine/Entity/entity.h"
#include "Engine/UI/button.h"

#include <SFML/Audio.hpp>

#include "constants.h"

namespace state
{

class MainMenu : public State
{
    public:
        explicit    MainMenu( Game* game );
        void        input       (const float dt);
        void        update      (const float dt);
        void        draw        (const float dt);

    private:
        void        fadeIn      ();

    private:
        Entity      mBackground         { _mGame().getTextures().getTexture( RES_TXR_MENU_BACKGROUND ) };
        Entity      mLogo               { _mGame().getTextures().getTexture( RES_TXR_LOGO_FTW )        };

        ui::Button  mNewGameButton      { _mGame().getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL ),
                    /* position */      { (win::WIDTH / 2.0f) - _mGame().getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL).getSize().x / 2.0f, 50.0f - 45.0f },
                    /* text */            "New Game",
                    /* text size */       60 };

        ui::Button  mContinueButton     { _mGame().getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL ),
                        /* position */  { (win::WIDTH / 2.0f) - _mGame().getTextures().getTexture( RES_TXR_GBL_LONG_SCROLL).getSize().x / 2.0f, 140.0f - 45.0f },
                        /* text */        "Continue Game",
                        /* text size */   60 };

        bool        blackFading         { true };


        sf::RectangleShape blackFade;

        sf::Sound   click;
};

}//Namespace state

#endif // MAINMENU_H
