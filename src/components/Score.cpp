/******************************************************************************
**
** File      Score.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Score.h"
#include "../types/Config.h"

namespace zuma
{

Score::Score(sf::Vector2u windowSize)
    : m_buttonOk{config::score::button::size(windowSize),config::score::button::position(windowSize),"OK"}
{
    m_rectBox.setSize(config::score::box::size(windowSize));
    m_rectBox.setOrigin(config::origin(m_rectBox.getSize()));
    m_rectBox.setPosition(config::score::box::position(windowSize));
    m_rectBox.setFillColor(config::score::box::cFillColor);
    m_rectBox.setOutlineThickness(config::score::box::cBorderThickness);
    m_rectBox.setOutlineColor(config::score::box::cBorderColor);
}

void Score::Draw(sf::RenderWindow *window) const
{
    window->draw(m_rectBox);
    m_buttonOk.Draw(window);
}

bool Score::ButtonOkMouseClick(sf::Vector2i mousePos)
{
    return m_buttonOk.isHover(mousePos);
}

void Score::ButtonOkMouseHover(sf::Vector2i mousePos)
{
    m_buttonOk.unhovered();

    if (m_buttonOk.isHover(mousePos)) {
        m_buttonOk.hovered();
    };
}

}   // namespace zuma
