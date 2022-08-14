/******************************************************************************
**
** File      Config.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>

namespace zuma
{

namespace config
{

static const sf::Vector2u cBaseWindowSize = {1920,1080};

static sf::Vector2f scaleFactor(sf::Vector2u windowSize)
{
    return {static_cast<float>(windowSize.x) / static_cast<float>(cBaseWindowSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(cBaseWindowSize.y)};
}

struct Button
{
    sf::Color fillColor;
    sf::Color borderColor;
    sf::Color hoverFillColor;
    sf::Color hoverBorderColor;
    sf::Color textColor;
    sf::Color hoverTextColor;
    int textSize;
    std::string fontPath;
};

static const Button button = {
            sf::Color::White,
            sf::Color::White,
            sf::Color::Black,
            sf::Color::Black,
            sf::Color::Black,
            sf::Color::White,
            32,
            "resources/font/Comfortaa-Bold.ttf"
        };

namespace menu
{

    static const float buttonPaddingLeft = 40.0f;
    static const float buttonPaddingTop = 10.0f;
    static const float buttonWidthCoef = 5.0f;
    static const float buttonHeightCoef = 10.0f;

    static sf::Vector2f buttonSize(sf::Vector2u windowSize) 
    {
        return {windowSize.x / buttonWidthCoef, windowSize.y / buttonHeightCoef};
    }

    static sf::Vector2f buttonPosition(int count,int order,sf::Vector2u windowSize)
    {
        const auto size = buttonSize(windowSize);
        return {size.x / 2.0f + buttonPaddingLeft,
                (buttonHeightCoef - (count - order))*size.y - (count - order)*buttonPaddingTop};
    }

}   // namespace menu

namespace score
{

    static const float boxSizeCoef = 2.0f;
    static const float buttonHeightCoef = 8.0f;

    static sf::Vector2f boxSize(sf::Vector2u windowSize) 
    {
        return {windowSize.x / boxSizeCoef, windowSize.y / boxSizeCoef};
    }

    static sf::Vector2f boxPosition(sf::Vector2u windowSize) 
    {
        return {windowSize.x / (2.0f * boxSizeCoef), windowSize.y / (2.0f * boxSizeCoef)};
    }

    static sf::Vector2f buttonSize(sf::Vector2u windowSize) 
    {
        return {boxSize(windowSize).x, boxSize(windowSize).y / buttonHeightCoef};
    }

    static sf::Vector2f buttonPosition(sf::Vector2u windowSize)
    {
        return {boxSize(windowSize).x, boxSize(windowSize).y * 1.5f - buttonSize(windowSize).y / 2.0f};
    }

    struct Box
    {
        sf::Color fillColor;
        sf::Color borderColor;
        float borderThickness;
    };

    static const Box box = {sf::Color::White,sf::Color::Black,2.0f};

}   // namespace score

namespace object_gun
{

    static const sf::Vector2u cTextureSize = {100, 60};
    static const std::string cTexturePath = "resources/img/gun.png";
    static const bool cTextureSmooth = true;

    static sf::Vector2f position(sf::Vector2u windowSize)
    {
        return {windowSize.x / 2.0f - cTextureSize.x / 2.0f, windowSize.y / 2.0f - cTextureSize.y / 2.0f};
    }

}   // namespace object_gun

namespace object_ball
{

    static const float cBaseRadius = 25.0f;

    static  float radius(sf::Vector2u windowSize) 
    {
        return cBaseRadius * scaleFactor(windowSize).y;
    }

    static sf::Vector2f origin(sf::Vector2u windowSize)
    {
        return {windowSize.x / 2.0f, windowSize.y / 2.0f};
    }

    static sf::Vector2f startPosition(sf::Vector2u windowSize)
    {
        return {windowSize.x / 2.0f, radius(windowSize) * 2.0f};
    }

}   // namespace object_ball
        
}   // namespace config

}   // namespace zuma