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
                      std::pair {OriginProperty::key, sf::Vector2f(windowSize) / 2.0f},
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

bool ObjectBall::hasCollision(sf::Vector2f position) const
{
    const auto onGetRadius = [this,position] (sf::Vector2f thisPosition) -> Result<bool> {
        const auto onCheckCollison = [position,thisPosition] (float thisRadius) -> Result<bool> {
            const auto dx = (thisPosition.x - position.x);
            const auto dy = (thisPosition.y - position.y);
            return  2.0f * thisRadius > std::sqrtf(dx*dx + dy*dy);
        };
        return getProperty(RadiusProperty::key).and_then(RadiusProperty::cast).and_then(onCheckCollison);
    };
    return getProperty(PositionProperty::key).and_then(PositionProperty::cast).and_then(onGetRadius).value();
}

bool ObjectBall::hasCollision(const ObjectBall *ball) const
{
    const auto onHasCollision = [this] (sf::Vector2f position) -> Result<bool> {
        return hasCollision(position);
    };
    return ball->getProperty(PositionProperty::key).and_then(PositionProperty::cast)
                                                   .and_then(onHasCollision).value();
}

void ObjectBall::draw(sf::RenderWindow *window)
{
    window->draw(m_circle);
}



}