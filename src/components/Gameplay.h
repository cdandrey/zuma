/******************************************************************************
**
** File      Gameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "objects/Gun.h"

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
    std::shared_ptr<Gun> m_gun;
};

}