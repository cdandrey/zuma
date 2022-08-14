/******************************************************************************
**
** File      SceneGameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "SceneGameplay.h"
#include "adapters/AdapterRotable.h"
#include "adapters/AdapterMovable.h"
#include "commands/CommandRotable.h"
#include "commands/CommandCircleMovable.h"

namespace zuma
{

SceneGameplay::SceneGameplay(sf::Vector2u windowSize)
    : m_size{windowSize}
    , m_fakeBallOnStartPosition{m_size,sf::Color::White}
    , m_gun{m_size}
{
    //m_balls.emplace_after(m_balls.before_begin(),windowSize, sf::Color::Red);
}

void SceneGameplay::update()
{
    m_elapsedTime = m_clock.restart();

    auto adapter = std::make_shared<AdapterRotable>(&m_gun);
    auto cmd = std::make_shared<CommandRotable>(adapter);
    cmd->execute(m_elapsedTime.asSeconds());
    m_gun.update();

    for (auto &ball : m_balls) {
        ball.setProperty(CircleVelocityProperty::key,10.0f);
        const auto adapter = std::make_shared<AdapterMovable>(&ball);
        const auto cmd = std::make_shared<CommandCircleMovable>(adapter);
        cmd->execute(m_elapsedTime.asSeconds());
        ball.updateGraphics();
    }

    nextSceneCalculation();
}

void SceneGameplay::rotateGun(sf::Vector2f position)
{
    m_gun.setProperty(RotatePositionProperty::key,position);
}

void SceneGameplay::draw(sf::RenderWindow *window)
{
    m_gun.draw(window);
    for (auto &ball : m_balls) {
        ball.draw(window);
    }
    
}

bool SceneGameplay::gameOver() const
{
    return (m_balls.size() > 1) && m_fakeBallOnStartPosition.hasColission(&m_balls.front());
}

void SceneGameplay::nextSceneCalculation() 
{
    if (m_balls.empty() || !m_fakeBallOnStartPosition.hasColission(&m_balls.back())) {
        m_balls.emplace_back(m_size,sf::Color::Red);
    }
}

}   // namespace zuma