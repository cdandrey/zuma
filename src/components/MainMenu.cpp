/******************************************************************************
**
** File      MainMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "MainMenu.h"

namespace zuma
{

MainMenu::MainMenu(sf::Vector2u size)
{
    const float width = size.x / 5.0f;
    const float height = size.y / 10.0f;
    const float padding {10.0f};

    const auto createButton = [width,height](Button &button,sf::Vector2f pos,const std::string &text) {
        button.setSize({width,height});
        button.setPos(pos);
        button.setText(text);
        button.setTextSize(32);
        button.setTextColor(sf::Color::Black);
    };

    createButton(m_buttonPlay,{width / 2.0f + 4*padding , 8*height - 2*padding},"Play");
    createButton(m_buttonExit,{width / 2.0f + 4*padding , 9*height - padding},"Exit");
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
