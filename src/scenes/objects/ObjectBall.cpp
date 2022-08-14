/******************************************************************************
**
** File      ObjectBall.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectBall.h"
#include "../../configs/Config.h"

namespace zuma
{

ObjectBall::ObjectBall(sf::Vector2u windowSize, sf::Color color) 
    : AbstractObject {std::pair {RadiusProperty::key, config::object_ball::radius(windowSize)},
                      std::pair {OriginProperty::key, config::object_ball::origin(windowSize)},
                      std::pair {PositionProperty::key, config::object_ball::startPosition(windowSize)},
                      std::pair {DirectionProperty::key, DirectionProperty::type {}},
                      std::pair {VelocityProperty::key, VelocityProperty::type {}},
                      std::pair {CircleVelocityProperty::key, CircleVelocityProperty::type {}},
                      std::pair {ColorProperty::key, color}}
{
    updateGraphics();
}

void ObjectBall::updateGraphics()
{
    const auto onSetRadius = [this](float radius) {
        m_circle.setRadius(radius);
    };

    getProperty(RadiusProperty::key).and_then(RadiusProperty::cast).map(onSetRadius);

    const auto onSetPosition = [this](sf::Vector2f position) {
        m_circle.setPosition(position);
    };

    getProperty(PositionProperty::key).and_then(PositionProperty::cast).map(onSetPosition);

    const auto onSetColor = [this](sf::Color color) {
        m_circle.setFillColor(color);
    };

    getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onSetColor);
}

bool ObjectBall::hasColission(const ObjectBall *ball) const
{
    const auto thisPosition = this->getProperty(PositionProperty::key).and_then(PositionProperty::cast);
    const auto position = ball->getProperty(PositionProperty::key).and_then(PositionProperty::cast);
    const auto thisRadius = this->getProperty(RadiusProperty::key).and_then(RadiusProperty::cast);
    const auto radius = ball->getProperty(RadiusProperty::key).and_then(RadiusProperty::cast);
    const auto dx = (thisPosition.value().x - position.value().x);
    const auto dy = (thisPosition.value().y - position.value().y);

    return  (thisRadius.value() + radius.value()) > std::sqrtf(dx*dx + dy*dy);
}

void ObjectBall::draw(sf::RenderWindow *window)
{
    window->draw(m_circle);
}



}