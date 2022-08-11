/******************************************************************************
**
** File      Button.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>

namespace zuma
{

class Button
{
public:
    Button() = default;
    ~Button() = default;

    void setText(const std::string &text);
    void setBackgroundColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPos(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setTextSize(int size);
    void setTextStyle(sf::Text::Style style);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    void hovered();
    void unhovered();
    bool isHover(sf::Vector2i mousePos) const;

    void Draw(sf::RenderWindow *window) const;

private:

    sf::RectangleShape m_rect;
    sf::Text m_text;
    sf::Font m_font;
};

}