/******************************************************************************
**
** File      SceneGameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "objects/ObjectGun.h"
#include "objects/ObjectBall.h"
#include "../utils/Randomizer.h"

namespace zuma
{

class SceneGameplay
{
public:

    explicit SceneGameplay(sf::Vector2u windowSize);
    ~SceneGameplay() = default;
    
    bool gameOver() const;
    void gunRotate(sf::Vector2f position);
    void gunShot(sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow *window);

private:
    
    using itBall = std::list<ObjectBall>::iterator;

    sf::Vector2u m_size;
    ObjectGun m_gun;
    ObjectBall m_shotBall;
    std::list<ObjectBall> m_balls;
    ObjectBall m_fakeBallOnStartPosition;

    sf::Clock m_clock;
    sf::Time m_elapsedTime;

    RandomizeColor m_randColor;

    enum class StateColision {
        Inserting,
        Erasing,
        Undefine
    };

    void calculatNextScene();
    void spawnBalls();
    void gunLoad();
    void shotBallOut();
    auto checkInsertingBall(itBall itColisionBall,const ObjectBall &colisionBall);
    auto checkCollisionBall();

    void setBallsProperty(itBall begin, itBall end, PropertyKey key, PropertyValue value);
    void shotBallFree();
};

}   // namespace zuma