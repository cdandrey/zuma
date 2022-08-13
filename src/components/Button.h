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
    Button(sf::Vector2f size,sf::Vector2f position,const std::string &text);
    ~Button() = default;

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