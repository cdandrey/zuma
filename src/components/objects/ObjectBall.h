/******************************************************************************
**
** File      ObjectBall.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractObject.h"
#include <SFML/Graphics.hpp>

namespace zuma
{

class ObjectBall : public AbstractObject
{
public:
    ObjectBall(sf::Vector2f origin, sf::Vector2f position,sf::Color color);
    ~ObjectBall() = default;

    void update();
    void draw(sf::RenderWindow *window);

private:
    sf::CircleShape m_circle;
};

}