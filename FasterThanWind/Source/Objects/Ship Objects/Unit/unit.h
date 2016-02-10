#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "../../Engine/Entity/entity.h"
#include "rangednum.h"
#include "animation.h"
#include "level.h"

enum UnitType
{
    UT_RECRUIT
};

class Unit : public Entity
{
    public:
                                Unit            (const sf::Texture&  texture,   const UnitType      _type,
                                                 const sf::Vector2f& pos,       const sf::Vector2f& shipPos);

                void            update          (const float dt);
                void            setToShipPos    (const sf::Vector2f& shipPos);

    private: //Private methods
                void            setUpAnimation  ();

        const   std::string     typeToString    () const;
                void            setLevels       ();


     private://variables
        UnitType                    mUnitType;

        int                         mXPos,
                                    mYPos;

        Animation                   walkingAnim;

        Level                       repairLvl   { 1 };
        Level                       speedLvl    { 1 };
};

#endif // UNIT_H
