/******************************************************************************
**
** File      Button.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Button.h"

namespace zuma
{

void Button::setSize(sf::Vector2f size)
{
    m_rect.setSize(size);
    m_rect.setOrigin(size / 2.0f);   // center of rect
}

void Button::setPosition(sf::Vector2f position)
{
    m_rect.setPosition(position);
    m_text.setPosition(position);
}

void Button::setText(const std::string &text)
{
    m_text.setString(text);
    const auto rect = m_text.getLocalBounds();
    m_text.setOrigin({rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f});
}

void Button::setStyle(const config::button::Style &style)
{
    m_style = style;

    m_rect.setFillColor(style.cFillColor);
    m_rect.setOutlineColor(style.cBorderColor);
    m_rect.setOutlineThickness(style.cBorderThickness);

    m_font.loadFromFile(style.cFontPath);
    m_text.setFont(m_font);
    m_text.setFillColor(style.cTextColor);
    m_text.setCharacterSize(style.cTextSize);

    // for update position origin
    setText(m_text.getString().toAnsiString());
}

bool Button::isHover(sf::Vector2i mousePos) const
{
    int left = static_cast<int>(m_rect.getPosition().x - m_rect.getSize().x / 2.0f);
    int right = static_cast<int>(m_rect.getPosition().x + m_rect.getSize().x / 2.0f);
    int top = static_cast<int>(m_rect.getPosition().y - m_rect.getSize().y / 2.0f);
    int bottom = static_cast<int>(m_rect.getPosition().y + m_rect.getSize().y / 2.0f);

    if (mousePos.x >= left && mousePos.x <= right &&
        mousePos.y >= top  && mousePos.y <= bottom)
    {
        return true;
    }

    return false;
}

void Button::unhovered()
{
    m_rect.setFillColor(m_style.cFillColor);
    m_rect.setOutlineColor(m_style.cBorderColor);
    m_text.setFillColor(m_style.cTextColor);
}

void Button::hovered()
{
    m_rect.setFillColor(m_style.cHoverFillColor);
    m_rect.setOutlineColor(m_style.cHoverBorderColor);
    m_text.setFillColor(m_style.cHoverTextColor);
}

void Button::draw(sf::RenderWindow *window) const
{
    window->draw(m_rect);
    window->draw(m_text);
}

}   // namespace zuma