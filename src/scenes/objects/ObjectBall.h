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

    void updateGraphics();
    void draw(sf::RenderWindow *window);
    bool hasCollision(const ObjectBall *ball) const;

private:
    sf::CircleShape m_circle;
};

}