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
    
    using IteratorBall = std::list<ObjectBall>::iterator;

    sf::Vector2u m_size;
    ObjectGun m_gun;
    ObjectBall m_shotBall;
    std::list<ObjectBall> m_balls;

    sf::Clock m_clock;
    sf::Time m_elapsedTime;

    RandomizeColor m_randColor;

    enum class Mode {
        Start,
        WaitShot,
        CheckCollision,
        StartExpansion,
        StopExpansion,
        Insertion,
        SearchIdentic,
        EraseIdentic,
        StartComprasion,
        StopComprasion
    };

    auto start();
    auto waitShot();
    auto checkCollision();
    auto startExpansion(IteratorBall first, IteratorBall last);
    auto stopExpansion(IteratorBall itCollisionBall,sf::Vector2f insertPosition);
    auto insertion(IteratorBall itCollisionBall,sf::Vector2f insertPosition);
    auto searchIdentic(IteratorBall itInsertBall);
    auto eraseIdentic(IteratorBall first, IteratorBall last);
    auto startComprasion(IteratorBall last);
    auto stopComprasion(IteratorBall last, sf::Vector2f position);

    void calculatNextScene();
    void spawnBalls();
    void gunLoad();
    bool shotBallOut();

    void setBallsProperty(IteratorBall first, IteratorBall last, PropertyKey key, PropertyValue value);
    void ballFree(ObjectBall &ball);
};

}   // namespace zuma