/******************************************************************************
**
** File      ObjectGun.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectGun.h"
#include "../../types/Config.h"

namespace zuma
{

ObjectGun::ObjectGun(sf::Vector2u windowSize) 
    : AbstractObject {std::pair {PositionProperty::key, config::object_gun::position(windowSize)},
                      std::pair {DirectionProperty::key, DirectionProperty::type {}},
                      std::pair {RotatePositionProperty::key, RotatePositionProperty::type {}}}
{
    m_texture.loadFromFile(config::object_gun::cTexturePath);
    m_texture.setSmooth(config::object_gun::cTextureSmooth);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(config::object_gun::position(windowSize));
    m_sprite.setScale(config::scaleFactor(windowSize));
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