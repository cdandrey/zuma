/******************************************************************************
**
** File      Button.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Button.h"
#include "../../configs/Config.h"

namespace zuma
{

Button::Button(sf::Vector2f size,sf::Vector2f position,const std::string &text)
{
    m_rect.setSize(size);
    m_rect.setOrigin(config::origin(size));
    m_rect.setPosition(position);
    m_rect.setFillColor(config::button::cFillColor);
    m_rect.setOutlineColor(config::button::cBorderColor);
    m_rect.setOutlineThickness(config::button::cBorderThickness);

    m_font.loadFromFile(config::button::cFontPath);
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setPosition(position);
    const auto textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setFillColor(config::button::cTextColor);
    m_text.setCharacterSize(config::button::cTextSize);
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
    m_rect.setFillColor(config::button::cFillColor);
    m_rect.setOutlineColor(config::button::cBorderColor);
    m_text.setFillColor(config::button::cTextColor);
}

void Button::hovered()
{
    m_rect.setFillColor(config::button::cHoverFillColor);
    m_rect.setOutlineColor(config::button::cHoverBorderColor);
    m_text.setFillColor(config::button::cHoverTextColor);
}

void Button::Draw(sf::RenderWindow *window) const
{
    window->draw(m_rect);
    window->draw(m_text);
}

}   // namespace zuma