/******************************************************************************
**
** File      ObjectGun.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectGun.h"
#include "../../configs/Config.h"

namespace zuma
{

ObjectGun::ObjectGun(sf::Vector2u windowSize) 
    : AbstractObject {std::pair {PositionProperty::key, config::object_gun::position(windowSize)},
                      std::pair {DirectionProperty::key, DirectionProperty::type {}},
                      std::pair {RotatePositionProperty::key, RotatePositionProperty::type {}},
                      std::pair {ColorProperty::key,sf::Color::White}
                    }
{
    m_texture.loadFromFile(config::object_gun::cTexturePath);
    m_texture.setSmooth(config::object_gun::cTextureSmooth);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(config::object_gun::position(windowSize));
    m_sprite.setScale(config::scaleFactor(windowSize));
}

void ObjectGun::updateGraphics()
{
    const auto onSetRotate = [this](float angel) {
        m_sprite.setRotation(angel * config::cRadiansToDegreeCoef);
    };

    getProperty(DirectionProperty::key).and_then(DirectionProperty::cast).map(onSetRotate);

    const auto onSetColor = [this](sf::Color color) {
        m_sprite.setColor(color);
    };

    getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onSetColor);
}

void ObjectGun::draw(sf::RenderWindow *window)
{
    window->draw(m_sprite);
}

}