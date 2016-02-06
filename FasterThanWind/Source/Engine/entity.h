#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "ResourceManagers/texturemanager.h"

class Entity
{
    public:
                explicit        Entity          (const sf::Texture& t);
                                Entity          (const sf::Texture& t, const std::string& text);
                                Entity          (const sf::Texture& t, const std::string& text, const sf::Vector2f& pos);
                                Entity          ();
        virtual void            draw            (sf::RenderWindow& window);

                void            setPos          (  const sf::Vector2f& pos  );
                void            setRot          (  const int rot            );
                void            setColour       (  const sf::Color& c       );
                void            setOrigin       (  const sf::Vector2f& org  );
                void            setToRandColour ();

                sf::Vector2f    getPos          () const;
                sf::Sprite      getSprite       () const;

                void            dance           (const float& dt);

                void            centerOrigin    (const sf::Vector2f& newPos);

                void            setUpText       (const std::string& text, const sf::Vector2f& pos);
                void            setTextSize     (const int characterSize);
                void            moveText        (const sf::Vector2f& offset);

    protected:
                sf::Sprite&     _mSprite        ();
                void            setTextureRect  (const sf::IntRect& rect);

    private:
        sf::Sprite              mSprite;

        sf::Color               newColour      ();
        void                    changeColour    (int& colour, bool& isAdding);



        bool        isRedAdded;
        bool        isGreenAdded;
        bool        isBlueAdded;

        double      danceCount;

        sf::Font mFont;
        sf::Text mText;
};

#endif // ENTITY_H
