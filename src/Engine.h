/******************************************************************************
**
** File      Engine.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <SFML/System.hpp>

namespace zuma
{

class Engine 
{
public:

    void exec();

private:
   sf::Clock m_clock;
   sf::Time m_elapsed; 
};

}