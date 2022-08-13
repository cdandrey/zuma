/******************************************************************************
**
** File      ObjectGun.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectGun.h"

namespace zuma
{

ObjectGun::ObjectGun(sf::Vector2f position) 
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {DirectionProperty::key, DirectionProperty::type {}},
                      std::pair {RotatePositionProperty::key, RotatePositionProperty::type {}}}
{
    m_texture.loadFromFile("resources/img/gun.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);
    setProperty(PositionProperty::key,position);
}

void ObjectGun::setColor(sf::Color color)
{
    m_sprite.setColor(color);
}

void ObjectGun::update()
{
    const auto onSetRotate = [this](float angel) {
        m_sprite.setRotation(angel);
    };

    getProperty(DirectionProperty::key).and_then(DirectionProperty::cast).map(onSetRotate);
}

void ObjectGun::draw(sf::RenderWindow *window)
{
    window->draw(m_sprite);
}

}