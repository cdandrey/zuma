/******************************************************************************
**
** File      Gameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "objects/ObjectGun.h"
#include "objects/ObjectBall.h"

#include <forward_list>

namespace zuma
{

class Gameplay
{
public:

    explicit Gameplay(sf::Vector2u size);
    ~Gameplay() = default;
    
    void rotateGun(sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow *window);

private:
    std::shared_ptr<ObjectGun> m_gun;
    std::forward_list<ObjectBall> m_balls;
};

}