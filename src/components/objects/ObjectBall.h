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
    ObjectBall(sf::Vector2u windowSize, sf::Color color);
    ~ObjectBall() = default;

    void update();
    void draw(sf::RenderWindow *window);

private:
    sf::CircleShape m_circle;
};

}