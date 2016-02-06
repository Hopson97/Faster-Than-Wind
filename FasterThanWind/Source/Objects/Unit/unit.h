#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "entity.h"
#include "rangednum.h"
#include "animation.h"

enum UnitType
{
    UT_RECRUIT
};

class Unit : public Entity
{
    public:
        Unit        (const sf::Texture& texture, const UnitType _type, const sf::Vector2f& pos, const sf::Vector2f& shipPos);

        void            update          (const float dt);
        void            setToShipPos     (const sf::Vector2f& shipPos);

    private:
        void            setUpAnimation  ();

        std::string     typeToString    () const;
        void            setLevels       ();


     private://variables
        UnitType                    mUnitType;

        int                         mXPos,
                                    mYPos;

        Animation                   walkingAnim;

        int                         MAX_LEVEL;
        util::RangedNum<int>        speedLvl;
        util::RangedNum<int>        repairLvl;
};

#endif // UNIT_H
