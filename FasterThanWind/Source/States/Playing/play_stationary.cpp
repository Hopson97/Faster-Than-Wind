#include "play_stationary.h"

namespace state {

Play_Stationary::Play_Stationary(Game* game, const Ship& ship)
:   State   (game)
,   mShip   (ship)
{
    mShip.setTexture( ship.getTexture() );
    mShip.setPosition({0.0f, 0.0f}, true);
}

void Play_Stationary::input( const float dt )
{

}

void Play_Stationary::update( const float dt )
{

}

void Play_Stationary::draw( const float dt )
{
    mShip.draw( _mGame().window() );
}

} //Name space state
