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
    , m_shotBall{{},sf::Color::Transparent}
    , m_balls{{m_size,sf::Color::Transparent}}  // set fake first ball for correct reverse itaration
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
            m_shotBall.setProperty(VelocityProperty::key,config::gameplay::cBaseShotVelocity);
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
    return (m_balls.size() > 3) && m_balls.back().hasCollision(&(*std::next(m_balls.begin(),1)));  // next because first ball is fake
}

void SceneGameplay::setBallsProperty(IteratorBall first, IteratorBall last, PropertyKey key, PropertyValue value)
{
    for (auto it = first; it != last; ++it) {
        it->setProperty(key,value);
    }
}

auto SceneGameplay::start()
{
    setBallsProperty(m_balls.begin(),m_balls.end(),CircleVelocityProperty::key,config::gameplay::cBaseCircleVelocity);
    return Mode::WaitShot;
}

auto SceneGameplay::waitShot()
{
    const auto onShot = [] (float velocity) -> Result<Mode> {
        if (velocity > 0.0f) {
            return Mode::CheckCollision;
        }
        return Mode::WaitShot;
    };
    
    return m_shotBall.getProperty(VelocityProperty::key)
                     .and_then(VelocityProperty::cast)
                     .and_then(onShot).value();
}

auto SceneGameplay::checkCollision()
{
    if (shotBallOut()) {
        return std::tuple{IteratorBall{}, sf::Vector2f{}, Mode::Start};
    }

    // next begin because first ball is fake
    for (auto it = std::next(m_balls.begin(),1); it != m_balls.end(); ++it) {
        if (m_shotBall.hasCollision(&(*it))) {
            m_shotBall.setProperty(VelocityProperty::key,0.0f);
            setBallsProperty(m_balls.begin(),m_balls.end(),CircleVelocityProperty::key,0.0f);
            const auto onPosition = [] (IteratorBall it) -> sf::Vector2f {
                return it->getProperty(PositionProperty::key).and_then(PositionProperty::cast).value();
            };
            // take prev position of ball because insertion is do before ball of collision
            // and position insert ball equal prev ball of collision
            return std::tuple{it,onPosition(std::prev(it,1)),Mode::StartExpansion};
        }
    }

    return std::tuple{IteratorBall{}, sf::Vector2f{}, Mode::CheckCollision};
}

auto SceneGameplay::startExpansion(IteratorBall first,IteratorBall last)
{
    setBallsProperty(first,last,CircleVelocityProperty::key,config::gameplay::cBaseAccelCircleVelocity);
    return Mode::StopExpansion;
}

auto SceneGameplay::stopExpansion(IteratorBall itPrevCollisionBall,sf::Vector2f position)
{
    if (!itPrevCollisionBall->hasCollision(position)) {
        // take next iterator because range = [first,last) and for include to range itPrev set last of next it
        setBallsProperty(m_balls.begin(),std::next(itPrevCollisionBall,1),CircleVelocityProperty::key,0.0f);
        return Mode::Insertion;
    }

    return Mode::StopExpansion;
}

auto SceneGameplay::insertion(IteratorBall itCollisionBall, sf::Vector2f position)
{
    const auto onColor = [] (const ObjectBall &ball) -> sf::Color {
        return ball.getProperty(ColorProperty::key).and_then(ColorProperty::cast).value();
    };
    
    // insert equal prev itCollisionBall
    auto insert = m_balls.emplace(itCollisionBall,m_size,onColor(m_shotBall));
    insert->setProperty(PositionProperty::key,position);

    ballFree(m_shotBall);
    
    return std::tuple{insert, Mode::SearchIdentic};
}

auto SceneGameplay::searchIdentic(IteratorBall insert)
{
    const auto onColor = [](IteratorBall it) -> sf::Color {
        return it->getProperty(ColorProperty::key).and_then(ColorProperty::cast).value();
    };

    const auto colorInsert = onColor(insert);

    IteratorBall first = insert;
    IteratorBall last = insert;

    IteratorBall it = insert;
    while (++it != m_balls.end() && onColor(it) == colorInsert) {
        last = it;
    }

    it = insert;
    // insert never is begin iterator, because first element is fake
    // and not have check of collision
    while (--it != m_balls.begin() && onColor(it) == colorInsert) {
        first = it;
    }
    
    // if first == last not have identic by color balls
    if (first == last) {
        return std::tuple{IteratorBall{},IteratorBall{},Mode::Start};
    }

    // for include last iterator range [first,last) take next iterator after last
    if (last != m_balls.end()){
        ++last;
    }
    
    for (it = first; it != last; ++it) {
        ballFree(*it);
    }

    return std::tuple{first,last,Mode::EraseIdentic};
}

auto SceneGameplay::eraseIdentic(IteratorBall first, IteratorBall last)
{
    last = m_balls.erase(first,last);
    return std::tuple(last, Mode::StartComprasion);
}

auto SceneGameplay::startComprasion(IteratorBall last)
{
    setBallsProperty(m_balls.begin(),last,CircleVelocityProperty::key,config::gameplay::cBaseReversCircleVelocity);

    const auto onPosition = [this] (IteratorBall it) -> sf::Vector2f {
        return it != m_balls.end() ? it->getProperty(PositionProperty::key).and_then(PositionProperty::cast).value()
                                   : config::object_ball::startPosition(m_size);
    };

    // prev because it is the last remaining iterator after deletion
    return std::tuple(std::prev(last,1),onPosition(last), Mode::StopComprasion);
}

auto SceneGameplay::stopComprasion(IteratorBall last, sf::Vector2f position)
{
    if (last->hasCollision(position)) {
        setBallsProperty(m_balls.begin(),last,CircleVelocityProperty::key,0.0f);
        return Mode::Start;
    }

    return Mode::StopComprasion;
}

void SceneGameplay::calculatNextScene() 
{
    static IteratorBall itCollisionBall;
    static IteratorBall first;
    static IteratorBall last;
    static sf::Vector2f position;
    static Mode mode {Mode::Start};

    switch (mode)
    {
    case Mode::Start:
        gunLoad();
        mode = start();
        break;
    case Mode::WaitShot:
        spawnBalls();
        mode = waitShot();
        break;
    case Mode::CheckCollision:
        spawnBalls();
        std::tie(itCollisionBall,position,mode) = checkCollision();
        break;
    case Mode::StartExpansion:
        mode = startExpansion(m_balls.begin(),itCollisionBall);
        break;
    case Mode::StopExpansion:
        mode = stopExpansion(std::prev(itCollisionBall,1),position);
        break;
    case Mode::Insertion:
        std::tie(itCollisionBall,mode) = insertion(itCollisionBall,position);
        break;
    case Mode::SearchIdentic:
        std::tie(first,last,mode) = searchIdentic(itCollisionBall);
        break;
    case Mode::EraseIdentic:
        std::tie(last, mode) = eraseIdentic(first,last);
        break;
    case Mode::StartComprasion:
        std::tie(last, position, mode) = startComprasion(last);
        break;
    case Mode::StopComprasion:
        mode = stopComprasion(last, position);
        break;
    default:
        break;
    }

}

void SceneGameplay::spawnBalls()
{
    if (!m_balls.back().hasCollision(config::object_ball::startPosition(m_size))) {
        m_balls.emplace_back(m_size,m_randColor.getRandomColor());
        m_balls.back().setProperty(CircleVelocityProperty::key,config::gameplay::cBaseCircleVelocity);
    }
}

void SceneGameplay::gunLoad()
{
    const auto color = m_randColor.getRandomColor();
    m_gun.setProperty(ColorProperty::key,color);
    m_shotBall.setProperty(ColorProperty::key,color);
}

bool SceneGameplay::shotBallOut()
{
    const auto onGetPosition = [this] (float radius) -> Result<bool> {
        const auto onOut = [this, radius] (sf::Vector2f position) -> Result<bool> {
            if (position.x >= m_size.x - radius || position.y >= m_size.y - radius || position.x <= radius || position.y <= radius) {
                ballFree(m_shotBall);
                return true;
            }
            return false;
        };
        return m_shotBall.getProperty(PositionProperty::key).and_then(PositionProperty::cast).and_then(onOut);
    };
    return m_shotBall.getProperty(RadiusProperty::key).and_then(RadiusProperty::cast).and_then(onGetPosition).value();
}

void SceneGameplay::ballFree(ObjectBall &ball)
{
    ball.setProperty(PositionProperty::key, sf::Vector2f{0.0f,0.0f});
    ball.setProperty(RadiusProperty::key,0.0f);
    ball.setProperty(DirectionProperty::key,0.0f);
    ball.setProperty(VelocityProperty::key,0.0f);
    ball.setProperty(ColorProperty::key,sf::Color::White);
    ball.setProperty(CircleVelocityProperty::key,0.0f);
}

}   // namespace zuma