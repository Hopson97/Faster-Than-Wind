#ifndef BUTTON_H
#define BUTTON_H

#include "entity.h"
namespace ui{
class Button : public Entity
{
    public:
                Button          (const sf::Texture& texture, const sf::Vector2f& pos);
                Button          (const sf::Texture& texture, const sf::Vector2f& pos, const std::string& buttonText);

        bool    clicked         (sf::RenderWindow& window);          //Returns true if button clicked

    private:
        bool    touchingMouse   (sf::RenderWindow& window);    //Returns true if touching mouse
};
}
#endif // BUTTON_H
