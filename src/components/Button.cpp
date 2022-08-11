/******************************************************************************
**
** File      Button.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Button.h"
#include <iostream>

namespace zuma
{

void Button::setText(const std::string &text)
{
    m_font.loadFromFile("resources/font/Comfortaa-Bold.ttf");
    m_text.setFont(m_font);
    m_text.setString(text);
    auto textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
}

void Button::setPos(sf::Vector2f pos)
{
    m_rect.setPosition(pos);
    m_text.setPosition(pos);
}

void Button::setSize(sf::Vector2f size)
{
    m_rect.setSize(size);
    m_rect.setOrigin(size.x / 2.0f,size.y / 2.0f);
}

void Button::setBackgroundColor(sf::Color color)
{
    m_rect.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

void Button::setTextSize(int size)
{
    m_text.setCharacterSize(size);
}

void Button::setTextStyle(sf::Text::Style style)
{
    m_text.setStyle(style);
}

sf::Vector2f Button::getSize() const
{
    return m_rect.getSize();
}

sf::Vector2f Button::getPosition() const
{
    return m_rect.getPosition();
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
    m_rect.setFillColor(sf::Color::White);
    m_text.setFillColor(sf::Color::Black);
}

void Button::hovered()
{
    m_rect.setFillColor(sf::Color::Black);
    m_text.setFillColor(sf::Color::White);
}

void Button::Draw(sf::RenderWindow *window) const
{
    window->draw(m_rect);
    window->draw(m_text);
}

}