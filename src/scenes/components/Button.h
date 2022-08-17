/******************************************************************************
**
** File      Button.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../../configs/Config.h"
#include <SFML/Graphics.hpp>

namespace zuma
{

class Button
{
public:
    Button() = default;
    ~Button() = default;

    void hovered();
    void unhovered();
    bool isHover(sf::Vector2i mousePos) const;

    void draw(sf::RenderWindow *window) const;
    
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setText(const std::string &text);
    void setStyle(const config::button::Style &style);

private:

    sf::RectangleShape m_rect;
    sf::Text m_text;
    sf::Font m_font;
    config::button::Style m_style;
};

}