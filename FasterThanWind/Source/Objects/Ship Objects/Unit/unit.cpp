#include "unit.h"

#include "constants.h"

Unit::Unit(const sf::Texture& texture, const UnitType _type, const sf::Vector2f& pos, const sf::Vector2f& shipPos)
:   Entity      (texture)
,   mUnitType   (_type)
,   mXPos       ( pos.x   )
,   mYPos       ( pos.y   )
,   MAX_LEVEL   ( 10 )
,   speedLvl    ( 1, MAX_LEVEL, 1)
,   repairLvl   ( 1, MAX_LEVEL, 1)
{
    _mSprite().setTextureRect(ship::UNIT_SIZE);

    setToShipPos(shipPos);

    setLevels();
    setUpAnimation();
}

/*****************************************************************************************************************************************************************
*   update()    update the unit
***************************************************************************************************************************************************************/
void Unit::update(const float dt)
{
    _mSprite().setTextureRect( walkingAnim.currentFrame(dt) );
}


/*****************************************************************************************************************************************************************
*   setToShipPos()  sets the position of the sprite relative to the ships position
*   param1  :   The position of the ship
***************************************************************************************************************************************************************/
void Unit::setToShipPos(const sf::Vector2f& shipPos)
{
    _mSprite().setPosition     ( (mXPos * ship::TILE_SIZE) + shipPos.x,
                                 (mYPos * ship::TILE_SIZE)  + shipPos.y );
}

/*****************************************************************************************************************************************************************
*   setUpAnimation() adds all needed frames to allow the unit to look alive
***************************************************************************************************************************************************************/
void Unit::setUpAnimation()
{
    const float WALK_FRAME_TIME = 0.2f;

    walkingAnim.addFrame({
                          sf::IntRect( 0 * ship::TILE_SIZE, 0, ship::TILE_SIZE, ship::TILE_SIZE),
                          WALK_FRAME_TIME
                         }
                        );

    walkingAnim.addFrame({
                          sf::IntRect( 1 * ship::TILE_SIZE, 0, ship::TILE_SIZE, ship::TILE_SIZE),
                          WALK_FRAME_TIME
                         }
                        );

    walkingAnim.addFrame({
                          sf::IntRect( 0 * ship::TILE_SIZE, 0, ship::TILE_SIZE, ship::TILE_SIZE),
                          WALK_FRAME_TIME
                         }
                        );

    walkingAnim.addFrame({
                          sf::IntRect( 2 * ship::TILE_SIZE, 0, ship::TILE_SIZE, ship::TILE_SIZE),
                          WALK_FRAME_TIME
                         }
                        );

}

