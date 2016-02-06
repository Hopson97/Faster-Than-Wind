#ifndef NEWGAMESHIPSELECTOR_H
#define NEWGAMESHIPSELECTOR_H

#include "../Objects/Ship/ship.h"
#include "state.h"

#include "game.h"
#include "shiploader.h"
#include "rangednum.h"

#include "UI/button.h"



#include <string>


namespace state
{

class NewGameShipSelector : public State
{
    public:
                NewGameShipSelector (Game* game, TextureManager& manager);

        void    input               (const float dt) override;
        void    update              (const float dt) override;
        void    draw                (const float dt) override;

    private:
        void    setUpButtons        ();
        void    addEntitysToVector  ();
        void    addShipsToVector    ();
        void    changeCurrentShip   (const int increment);
        void    resetShip           ();

    private:
        int                         LIST_BUTTON_Y;
        int                         mCurrentShipNumber;

        Ship                        mCurrentShip;
        ShipLoader                  mShipLoader;

        Entity                      shipYardLogo;

        ui::Button                  mPrevShipButton;
        Entity                      mListButtonText;
        ui::Button                  mNextShipButton;

        ui::Button                  mLayout1Button;
        ui::Button                  mLayout2Button;
        ui::Button                  mLayout3Button;

        ui::Button                  mConfirmSelectionButton;

        ui::Button                  mBackToMainMenuButton;

        std::vector<std::string>    mshipNameList;
        std::vector<Entity*>        mEntities;

        util::RangedNum<int>        mCurrentLayout;

        std::string                 shipString;
};

}//Namespace state

#endif // NEWGAMESHIPSELECTOR_H
