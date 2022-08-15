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
#include "commands/CommandMovable.h"
#include "../configs/Config.h"

#include <iostream>

namespace zuma
{

SceneGameplay::SceneGameplay(sf::Vector2u windowSize)
    : m_size{windowSize}
    , m_gun{m_size}
    , m_shotBall{{},sf::Color::White}
    , m_fakeBallOnStartPosition{m_size,{}}
{
}

void SceneGameplay::update()
{
    m_elapsedTime = m_clock.restart();

    {
        auto adapter = std::make_shared<AdapterRotable>(&m_gun);
        auto cmd = std::make_shared<CommandRotable>(adapter);
        cmd->execute(m_elapsedTime.asSeconds());
        m_gun.updateGraphics();
    }

    for (auto &ball : m_balls) {
        const auto adapter = std::make_shared<AdapterMovable>(&ball);
        const auto cmd = std::make_shared<CommandCircleMovable>(adapter);
        cmd->execute(m_elapsedTime.asSeconds());
        ball.updateGraphics();
    }

    {
        auto adapter = std::make_shared<AdapterMovable>(&m_shotBall);
        auto cmd = std::make_shared<CommandMovable>(adapter);
        cmd->execute(m_elapsedTime.asSeconds());
        m_shotBall.updateGraphics();
    }
}

void SceneGameplay::draw(sf::RenderWindow *window)
{
    m_gun.draw(window);
    for (auto &ball : m_balls) {
        ball.draw(window);
    }
    m_shotBall.draw(window);
    
    calculatNextScene();
}

void SceneGameplay::gunRotate(sf::Vector2f position)
{
    m_gun.setProperty(RotatePositionProperty::key,position);
}

void SceneGameplay::gunShot(sf::Vector2f position) 
{
    const auto onShot = [this,position](sf::Color color) {
        if (color != sf::Color::White) {
            m_gun.setProperty(ColorProperty::key,sf::Color::White);
            m_shotBall.setProperty(VelocityProperty::key,600.0f);
            m_shotBall.setProperty(RadiusProperty::key,config::object_ball::radius(m_size));
            const auto gunPosition = m_gun.getProperty(PositionProperty::key).and_then(PositionProperty::cast);
            const auto y = position.y - gunPosition.value().y;
            const auto x = position.x - gunPosition.value().x;
            const auto a = std::atan2f(y,x);
            m_shotBall.setProperty(DirectionProperty::key,a);

            const auto gunSizeX = config::object_gun::cTextureSize.x * config::scaleFactor(m_size).x;
            const auto gunSizeY = config::object_gun::cTextureSize.y * config::scaleFactor(m_size).y;
            const auto gunSizeR = std::sqrtf(gunSizeX * gunSizeX / 2.0f + gunSizeY * gunSizeY / 2.0f);

            const auto posX = gunPosition.value().x + std::cosf(a) * gunSizeR;
            const auto posY = gunPosition.value().y + std::sinf(a) * gunSizeR;

            m_shotBall.setProperty(PositionProperty::key, sf::Vector2f{posX, posY});
        }
    };

    m_gun.getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onShot);
}

bool SceneGameplay::gameOver() const
{
    return (m_balls.size() > 1) && m_fakeBallOnStartPosition.hasCollision(&m_balls.front());
}

void SceneGameplay::setBallsProperty(itBall begin, itBall end, PropertyKey key, PropertyValue value)
{
    for (auto it = begin; it != end; ++it) {
        it->setProperty(key,value);
    }
}

auto SceneGameplay::checkCollisionBall()
{
    for (auto it = m_balls.begin(); it != m_balls.end(); ++it) {
        if (m_shotBall.hasCollision(&(*it))) {
            m_shotBall.setProperty(VelocityProperty::key,0.0f);
            setBallsProperty(m_balls.begin(),std::next(it,1),CircleVelocityProperty::key,config::gameplay::cBaseAccelCircleVelocity);
            setBallsProperty(std::next(it,1),m_balls.end(),CircleVelocityProperty::key,0.0f);
            return std::tuple{it,*it,StateColision::Inserting};
        }
    }

    return std::tuple{m_balls.begin(),ObjectBall{m_size,{}},StateColision::Undefine};
}

auto SceneGameplay::checkInsertingBall(itBall itColisionBall,const ObjectBall &colisionBall)
{
    if (!colisionBall.hasCollision(&(*itColisionBall))) {
        auto itInsert = m_balls.insert(itColisionBall,colisionBall);
        const auto colorInsert = m_shotBall.getProperty(ColorProperty::key).and_then(ColorProperty::cast);
        itInsert->setProperty(ColorProperty::key,colorInsert.value());
        setBallsProperty(m_balls.begin(),m_balls.end(),CircleVelocityProperty::key,config::gameplay::cBaseCircleVelocity);
        shotBallFree();
        return StateColision::Undefine;
    }
    
    return StateColision::Inserting;
}

void SceneGameplay::calculatNextScene() 
{
    static itBall itColisionBall = m_balls.begin();
    static ObjectBall colisionBall {m_size,{}};
    static StateColision stateCollision {StateColision::Undefine};

    switch (stateCollision)
    {
    case StateColision::Inserting:
        stateCollision = checkInsertingBall(itColisionBall,colisionBall);
        break;
    case StateColision::Erasing:
        break;
    case StateColision::Undefine:
        spawnBalls();
        gunLoad();
        shotBallOut();
        std::tie(itColisionBall, colisionBall,stateCollision) = checkCollisionBall();
        break;
    default:
        break;
    }

}

void SceneGameplay::spawnBalls()
{
    if (m_balls.empty() || !m_fakeBallOnStartPosition.hasCollision(&m_balls.back())) {
        m_balls.emplace_back(m_size,m_randColor.getRandomColor());
        m_balls.back().setProperty(CircleVelocityProperty::key,config::gameplay::cBaseCircleVelocity);
    }
}

void SceneGameplay::gunLoad()
{
    const auto onGetColorGun = [this] (float shotVelocity) {
        const auto onLoad = [this, shotVelocity] (sf::Color color) {
            if (shotVelocity == 0.0f && color == sf::Color::White) {
                const auto color = m_randColor.getRandomColor();
                m_gun.setProperty(ColorProperty::key,color);
                m_shotBall.setProperty(ColorProperty::key,color);
            }
        };
        m_gun.getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onLoad);
    };
    m_shotBall.getProperty(VelocityProperty::key).and_then(VelocityProperty::cast).map(onGetColorGun);
}

void SceneGameplay::shotBallOut()
{
    const auto onGetRadius = [this](float velocity) {
        if (velocity > 0.0f) {
            const auto onGetPosition = [this,velocity] (float radius) {
                const auto onOut = [this, velocity, radius] (sf::Vector2f position) {
                    if (position.x >= m_size.x - radius || position.y >= m_size.y - radius || position.x <= radius || position.y <= radius) {
                        shotBallFree();
                    }
                };
                m_shotBall.getProperty(PositionProperty::key).and_then(PositionProperty::cast).map(onOut);
            };
            m_shotBall.getProperty(RadiusProperty::key).and_then(RadiusProperty::cast).map(onGetPosition);
        }
    };

    m_shotBall.getProperty(VelocityProperty::key).and_then(VelocityProperty::cast).map(onGetRadius);
}

void SceneGameplay::shotBallFree()
{
    m_shotBall.setProperty(PositionProperty::key, sf::Vector2f{0.0f,0.0f});
    m_shotBall.setProperty(RadiusProperty::key,0.0f);
    m_shotBall.setProperty(DirectionProperty::key,0.0f);
    m_shotBall.setProperty(VelocityProperty::key,0.0f);
    m_shotBall.setProperty(ColorProperty::key,sf::Color::White);
}

}   // namespace zuma