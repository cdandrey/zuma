/******************************************************************************
**
** File      Score.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Score.h"

namespace zuma
{

Score::Score(sf::Vector2u size)
{
    const float width = size.x / 2.0f;
    const float height = size.y / 2.0f;
    const float padding {10.0f};

    m_rectBox.setSize({width, height});
    m_rectBox.setPosition({width / 2.0f, height / 2.0f});
    m_rectBox.setFillColor(sf::Color::White);
    m_rectBox.setOutlineThickness(2);
    m_rectBox.setOutlineColor(sf::Color::Black);

    m_buttonOk.setSize({width,60.0f});
    m_buttonOk.setPos({width,height + height / 2.0f - 30.0f});
    m_buttonOk.setText("OK");
    m_buttonOk.setTextSize(32);
    m_buttonOk.setTextColor(sf::Color::Black);
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
