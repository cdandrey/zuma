/******************************************************************************
**
** File      Gameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include <iostream>
#include "Gameplay.h"
#include "adapters/AdapterRotable.h"
#include "adapters/AdapterMovable.h"
#include "commands/CommandRotable.h"
#include "commands/CommandCircleMovable.h"

namespace zuma
{

Gameplay::Gameplay(sf::Vector2u size)
{
    m_gun = std::make_shared<ObjectGun>(sf::Vector2f{size.x / 2.0f, size.y / 2.0f});
    m_balls.emplace_after(m_balls.before_begin(),sf::Vector2f{size.x / 2.0f, size.y / 2.0f}, sf::Vector2f{size.x / 2.0f, 60.0f}, sf::Color::Red);
}

void Gameplay::update()
{
    auto adapter = std::make_shared<AdapterRotable>(m_gun.get());
    auto cmd = std::make_shared<CommandRotable>(adapter);
    cmd->execute();
    m_gun->update();

    for (auto &ball : m_balls) {
        ball.setProperty(CircleVelocityProperty::key,0.5f);
        const auto adapter = std::make_shared<AdapterMovable>(&ball);
        const auto cmd = std::make_shared<CommandCircleMovable>(adapter);
        cmd->execute();
        ball.update();
    }
}

void Gameplay::rotateGun(sf::Vector2f position)
{
    m_gun->setProperty(RotatePositionProperty::key,position);
}

void Gameplay::draw(sf::RenderWindow *window)
{
    m_gun->draw(window);
    for (auto &ball : m_balls) {
        ball.draw(window);
    }
    
}

}