/******************************************************************************
**
** File      MainMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "MainMenu.h"
#include "../types/Config.h"

namespace zuma
{

MainMenu::MainMenu(sf::Vector2u windowSize)
    : m_buttonPlay{config::menu::buttonSize(windowSize),config::menu::buttonPosition(2,0,windowSize),"Play"}
    , m_buttonExit{config::menu::buttonSize(windowSize),config::menu::buttonPosition(2,1,windowSize),"Exit"}
{
}

void MainMenu::Draw(sf::RenderWindow *window) const
{
    m_buttonPlay.Draw(window);
    m_buttonExit.Draw(window);
}

bool MainMenu::ButtonPlayMouseClick(sf::Vector2i mousePos)
{
    return m_buttonPlay.isHover(mousePos);
}

bool MainMenu::ButtonExitMouseClick(sf::Vector2i mousePos)
{
    return m_buttonExit.isHover(mousePos);
}

void MainMenu::ButtonPlayMouseHover(sf::Vector2i mousePos)
{
    m_buttonPlay.unhovered();

    if (m_buttonPlay.isHover(mousePos)) {
        m_buttonPlay.hovered();
    };
}

void MainMenu::ButtonExitMouseHover(sf::Vector2i mousePos)
{
    m_buttonExit.unhovered();

    if (m_buttonExit.isHover(mousePos)) {
        m_buttonExit.hovered();
    };
}

}
