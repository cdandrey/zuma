/******************************************************************************
**
** File      SceneGameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "objects/ObjectGun.h"
#include "objects/ObjectBall.h"

#include <forward_list>

namespace zuma
{

class SceneGameplay
{
public:

    explicit SceneGameplay(sf::Vector2u windowSize);
    ~SceneGameplay() = default;
    
    bool gameOver() const;
    void rotateGun(sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow *window);

private:
    sf::Vector2u m_size;
    ObjectBall m_fakeBallOnStartPosition;
    ObjectGun m_gun;
    std::list<ObjectBall> m_balls;

    void nextSceneCalculation();
};

}   // namespace zuma