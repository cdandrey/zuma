/******************************************************************************
**
** File      Gun.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Gun.h"

namespace zuma
{

Gun::Gun(sf::Vector2f position) 
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {DirectionProperty::key, DirectionProperty::type {}},
                      std::pair {RotatePositionProperty::key, RotatePositionProperty::type {}}}
{
    m_texture.loadFromFile("resources/img/gun.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);
    setProperty(PositionProperty::key,position);
}

void Gun::setColor(sf::Color color)
{
    m_sprite.setColor(color);
}

void Gun::draw(sf::RenderWindow *window)
{
    const auto onSetRotate = [this](float angel) {
        m_sprite.setRotation(angel);
    };

    getProperty(DirectionProperty::key).and_then(DirectionProperty::cast).map(onSetRotate);
    window->draw(m_sprite);
}

}