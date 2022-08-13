/******************************************************************************
**
** File      ObjectBall.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ObjectBall.h"

namespace zuma
{

ObjectBall::ObjectBall(sf::Vector2f position, sf::Color color) 
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {VelocityProperty::key, VelocityProperty::type {}},
                      std::pair {ColorProperty::key, ColorProperty::type{}}}
{
    setProperty(PositionProperty::key,position);
    setProperty(ColorProperty::key,color);
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