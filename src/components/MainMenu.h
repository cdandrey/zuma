/******************************************************************************
**
** File      MainMenu.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "Button.h"

namespace zuma
{

class MainMenu
{
public:
    explicit MainMenu(sf::Vector2u size);
    ~MainMenu() = default;

    void Draw(sf::RenderWindow *window) const;

    bool ButtonPlayMouseClick(sf::Vector2i mousePos);
    bool ButtonExitMouseClick(sf::Vector2i mousePos);
    void ButtonPlayMouseHover(sf::Vector2i mousePos);
    void ButtonExitMouseHover(sf::Vector2i mousePos);

private:
    Button m_buttonPlay;
    Button m_buttonExit;
};

}