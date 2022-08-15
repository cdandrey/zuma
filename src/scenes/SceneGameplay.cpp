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
    const auto velosityShoBall = m_shotBall.getProperty(VelocityProperty::key).and_then(VelocityProperty::cast);

    if (velosityShoBall.value() > 0.0f) {
        return Mode::CheckCollision;
    }

    return Mode::WaitShot;
}

auto SceneGameplay::checkCollision()
{
    if (shotBallOut()) {
        return std::tuple{m_balls.begin(),ObjectBall{m_size,{}},Mode::Start};
    }

    for (auto it = m_balls.begin(); it != m_balls.end(); ++it) {
        if (m_shotBall.hasCollision(&(*it))) {
            m_shotBall.setProperty(VelocityProperty::key,0.0f);
            setBallsProperty(m_balls.begin(),m_balls.end(),CircleVelocityProperty::key,0.0f);
            return std::tuple{it,*std::prev(it,1),Mode::StartExpansion};
        }
    }

    return std::tuple{m_balls.begin(),ObjectBall{m_size,{}},Mode::CheckCollision};
}

auto SceneGameplay::startExpansion(IteratorBall first,IteratorBall last)
{
    setBallsProperty(first,last,CircleVelocityProperty::key,config::gameplay::cBaseAccelCircleVelocity);
    return Mode::StopExpansion;
}

auto SceneGameplay::stopExpansion(IteratorBall itCollisionBall,const ObjectBall &copyBeforeCollisionBall)
{
    if (!copyBeforeCollisionBall.hasCollision(&(*itCollisionBall))) {
        setBallsProperty(m_balls.begin(),std::next(itCollisionBall,1),CircleVelocityProperty::key,0.0f);
        return Mode::Insertion;
    }

    return Mode::StopExpansion;
}

auto SceneGameplay::insertion(IteratorBall itCollisionBall,const ObjectBall &copyBeforeCollisionBall)
{
    auto itInsertBall = m_balls.insert(itCollisionBall,copyBeforeCollisionBall);
    
    const auto onSetColor = [this,itInsertBall] (sf::Color color) {
        itInsertBall->setProperty(ColorProperty::key,color);
    };
    
    m_shotBall.getProperty(ColorProperty::key).and_then(ColorProperty::cast).map(onSetColor);

    ballFree(m_shotBall);
    
    return std::tuple{itInsertBall, Mode::SearchIdentic};
}

auto SceneGameplay::searchIdentic(IteratorBall itInsertBall)
{
    const auto onColor = [](IteratorBall it) -> sf::Color {
        return it->getProperty(ColorProperty::key).and_then(ColorProperty::cast).value();
    };

    const auto colorInsert = onColor(itInsertBall);

    IteratorBall itIdentFirst = itInsertBall;
    IteratorBall itIdentLast = itInsertBall;

    IteratorBall it = itInsertBall;
    while (++it != m_balls.end() && onColor(it) == colorInsert) {
        itIdentLast = it;
    }

    it = itInsertBall;
    while (it-- != m_balls.begin() && onColor(it) == colorInsert) {
        itIdentFirst = it;
    }
    
    if (it == m_balls.begin() && onColor(it) == colorInsert) {
        itIdentFirst = it;
    }

    if (itIdentFirst == itIdentLast) {
        return std::tuple{itIdentFirst,itIdentLast,Mode::Start};
    }

    if (itIdentLast != itInsertBall && itIdentLast != m_balls.end()){
        ++itIdentLast;
    }
    
    for (it = itIdentFirst; it != itIdentLast; ++it) {
        ballFree(*it);
    }

    return std::tuple{itIdentFirst,itIdentLast,Mode::EraseIdentic};
}

auto SceneGameplay::eraseIdentic(IteratorBall first, IteratorBall last)
{
    m_balls.erase(first,last);
    return Mode::StartComprasion;
}

auto SceneGameplay::startComprasion(IteratorBall last)
{
    if (last == m_balls.begin()) {
        return std::tuple{last, Mode::Start};
    }

    setBallsProperty(m_balls.begin(),last,CircleVelocityProperty::key,config::gameplay::cBaseReversCircleVelocity);
    return std::tuple{last,Mode::StopComprasion};
}

auto SceneGameplay::stopComprasion(IteratorBall itCollisionBall)
{
    if (itCollisionBall->hasCollision(&(*std::prev(itCollisionBall,1)))) {
        setBallsProperty(m_balls.begin(),itCollisionBall,CircleVelocityProperty::key,0.0f);
        return Mode::Start;
    }

    return Mode::StopComprasion;
}

void SceneGameplay::calculatNextScene() 
{
    static IteratorBall itCollisionBall;
    static IteratorBall itIdenticFirst;
    static IteratorBall itIdenticLast;
    static ObjectBall copyBeforeCollisionBall {m_size,{}};
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
        std::tie(itCollisionBall,copyBeforeCollisionBall,mode) = checkCollision();
        break;
    case Mode::StartExpansion:
        mode = startExpansion(m_balls.begin(),itCollisionBall);
        break;
    case Mode::StopExpansion:
        mode = stopExpansion(std::prev(itCollisionBall,1),copyBeforeCollisionBall);
        break;
    case Mode::Insertion:
        std::tie(itCollisionBall,mode) = insertion(itCollisionBall,copyBeforeCollisionBall);
        break;
    case Mode::SearchIdentic:
        std::tie(itIdenticFirst,itIdenticLast,mode) = searchIdentic(itCollisionBall);
        break;
    case Mode::EraseIdentic:
        mode = eraseIdentic(itIdenticFirst,itIdenticLast);
        break;
    case Mode::StartComprasion:
        std::tie(itCollisionBall, mode) = startComprasion(itIdenticLast);
        break;
    case Mode::StopComprasion:
        mode = stopComprasion(itCollisionBall);
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

std::string SceneGameplay::colorToStr(sf::Color color)
{
    if (color == sf::Color::Yellow)
        return "yellow";
    else if (color == sf::Color::Cyan)
        return "cyan";
    else if (color == sf::Color::Magenta)
        return "magenta";
    else if (color == sf::Color::Red)
        return "red";
    else if (color == sf::Color::Green)
        return "green";
    else if (color == sf::Color::Blue)
        return "blue";
    else if (color == sf::Color::Black)
        return "black";
    
    return "undefine";
}
}   // namespace zuma