/******************************************************************************
**
** File      Gameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "Gun.h"

namespace zuma
{

class Gameplay
{
public:

    explicit Gameplay(sf::Vector2u size);
    ~Gameplay() = default;

    void Draw(sf::RenderWindow *window);

private:
    Gun m_gun;
};

}