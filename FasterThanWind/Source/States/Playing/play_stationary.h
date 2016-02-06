#ifndef PLAY_STATIONARY_H
#define PLAY_STATIONARY_H

#include "state.h"
#include "game.h"

#include "../Objects/Ship/ship.h"

namespace state
{

class Play_Stationary : public State
{
    public:
        Play_Stationary(Game* game, const Ship& ship);

        void        input           ( const float dt )      override;
        void        update          ( const float dt )      override;
        void        draw            ( const float dt )      override;

    private:
        Ship mShip;
};

} //Name space state

#endif // PLAY_STATIONARY_H
