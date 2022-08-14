/******************************************************************************
**
** File      ObjectBall.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectBall.h"
#include "../../types/Config.h"

namespace zuma
{

ObjectBall::ObjectBall(sf::Vector2u windowSize, sf::Color color) 
    : AbstractObject {std::pair {OriginProperty::key, config::object_ball::origin(windowSize)},
                      std::pair {PositionProperty::key, config::object_ball::startPosition(windowSize)},
                      std::pair {VelocityProperty::key, VelocityProperty::type {}},
                      std::pair {CircleVelocityProperty::key, CircleVelocityProperty::type {}},
                      std::pair {ColorProperty::key, color}}
{
    m_circle.setRadius(config::object_ball::radius(windowSize));
    update();
}

void ObjectBall::update()
{
    const auto onSetPosition = [this](sf::Vector2f position) {
        m_circle.setPosition(position);
    };

    getProperty(PositionProperty::key).and_then(PositionProperty::cast).map(onSetPosition);

    const auto onSetColor = [this](sf::Color color) {
        m_circle.setFillColor(color);
    };

    getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onSetColor);


}

void ObjectBall::draw(sf::RenderWindow *window)
{
    window->draw(m_circle);
}

}