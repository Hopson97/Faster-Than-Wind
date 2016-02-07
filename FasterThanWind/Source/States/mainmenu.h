#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Engine/game.h"
#include "Engine/entity.h"
#include "Engine/UI/button.h"

#include <SFML/Audio.hpp>

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
        Entity      mBackground;
        Entity      mLogo;

        ui::Button  mNewGameButton;
        ui::Button  mContinueButton;

        sf::RectangleShape blackFade;
        bool    blackFading;

        sf::Sound   click;
};

}//Namespace state

#endif // MAINMENU_H
