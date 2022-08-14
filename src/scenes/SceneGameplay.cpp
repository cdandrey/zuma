/******************************************************************************
**
** File      SceneGameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include <iostream>
#include "SceneGameplay.h"
#include "adapters/AdapterRotable.h"
#include "adapters/AdapterMovable.h"
#include "commands/CommandRotable.h"
#include "commands/CommandCircleMovable.h"

namespace zuma
{

SceneGameplay::SceneGameplay(sf::Vector2u windowSize)
{
    m_gun = std::make_shared<ObjectGun>(windowSize);
    m_balls.emplace_after(m_balls.before_begin(),windowSize, sf::Color::Red);
}

void SceneGameplay::update()
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

void SceneGameplay::rotateGun(sf::Vector2f position)
{
    m_gun->setProperty(RotatePositionProperty::key,position);
}

void SceneGameplay::draw(sf::RenderWindow *window)
{
    m_gun->draw(window);
    for (auto &ball : m_balls) {
        ball.draw(window);
    }
    
}

}