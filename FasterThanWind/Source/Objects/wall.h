#ifndef WALL_H
#define WALL_H

#include "entity.h"
#include "animation.h"

#include <memory>

enum WallType
{
        WT_DOOR
    ,   WT_WALL
};

class Wall : public Entity
{
    public:
        Wall(   TextureManager& manager, const sf::Vector2f position, const int rotation,
                const WallType type, const int id, const int otherId );

        void        logic           (const float dt);
        void        setOtherDoor    (Wall& _wall);
        WallType    getType         () const;
        int         getId           () const;
        int         getOtherId      () const;

    private:
        void            setTexture      (TextureManager& manager);
        void            setUpAnimation  ();

    private:
        WallType        mWallType;

        //For matching doors up with each other
        Wall*           otherDoor;
        int             mId;
        int             mOtherDoorId;

        int       WALL_WIDTH;
        int       WALL_HEIGHT;

        Animation doorOpen;
};

#endif // WALL_H
