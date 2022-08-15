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

static const     sf::Vector2u cBaseWindowSize = {1920,1080};
static const     sf::Vector2u cBaseWindowCenter = {cBaseWindowSize.x / 2, cBaseWindowSize.y / 2};
static constexpr float cRadiansToDegreeCoef = 180.0f / 3.14f;

static sf::Vector2f scaleFactor(sf::Vector2u windowSize)
{
    return {static_cast<float>(windowSize.x) / static_cast<float>(cBaseWindowSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(cBaseWindowSize.y)};
}

static sf::Vector2f origin(sf::Vector2f size) 
{
    return {size.x / 2.0f, size.y / 2.0f};
}

namespace button
{
    static const sf::Color   cFillColor        =  sf::Color::White;
    static const sf::Color   cBorderColor      =  sf::Color::Black;
    static const float       cBorderThickness  =  2.0f;
    static const sf::Color   cHoverFillColor   =  sf::Color::Black;
    static const sf::Color   cHoverBorderColor =  sf::Color::Black;
    static const sf::Color   cTextColor        =  sf::Color::Black;
    static const sf::Color   cHoverTextColor   =  sf::Color::White;
    static const int         cTextSize         =  32;
    static const std::string cFontPath         =  "resources/font/Comfortaa-Bold.ttf";

}   // namespace button

namespace menu
{

    namespace button
    {
        static const sf::Vector2f cBaseSize     = {400.0f,100.0f};
        static const sf::Vector2f cBasePosition = {300.0f,cBaseWindowSize.y - 150.0f};
        static const float        cPadding      = 10.0f;

        static sf::Vector2f size(sf::Vector2u windowSize) 
        {
            return {cBaseSize.x * scaleFactor(windowSize).x,
                    cBaseSize.y * scaleFactor(windowSize).y};
        }

        static sf::Vector2f position(int count,int idx,sf::Vector2u windowSize) 
        {
            const auto scale = scaleFactor(windowSize);
            return {scale.x * cBasePosition.x,
                    scale.y * (cBasePosition.y - (count - idx - 1)*(cBaseSize.y + cPadding))};
        }
    }   // namespace menu::button

}   // namespace menu

namespace score
{
    static const float cPadding = 10.0f;
    
    namespace box
    {
        static const sf::Vector2f cBaseSize        = {600.0f,400.0f};
        static const sf::Vector2f cBasePosition    = {static_cast<float>(cBaseWindowCenter.x),
                                                      static_cast<float>(cBaseWindowCenter.y)};
        static const sf::Color    cFillColor       = sf::Color::White;
        static const sf::Color    cBorderColor     = sf::Color::Black;
        static const float        cBorderThickness = 2.0f;
    
        static sf::Vector2f size(sf::Vector2u windowSize) 
        {
            const auto scale = scaleFactor(windowSize);
            return {scale.x * cBaseSize.x, scale.y * cBaseSize.y};
        }

        static sf::Vector2f position(sf::Vector2u windowSize) 
        {
            const auto scale = scaleFactor(windowSize);
            return {scale.x * cBasePosition.x, scale.y * cBasePosition.y};
        }

    }   // namespace score::box

    namespace button
    {
        static const sf::Vector2f cBaseSize = {box::cBaseSize.x, 40.0f};
        static const sf::Vector2f cBasePosition = {box::cBasePosition.x,
                                                   box::cBasePosition.y + box::cBaseSize.y / 2.0f + cBaseSize.y / 2.0f + cPadding};
    
        static sf::Vector2f size(sf::Vector2u windowSize) 
        {
            const auto scale = scaleFactor(windowSize);
            return {scale.x * cBaseSize.x, scale.y * cBaseSize.y};
        }

        static sf::Vector2f position(sf::Vector2u windowSize) 
        {
            const auto scale = scaleFactor(windowSize);
            return {scale.x * cBasePosition.x, scale.y * cBasePosition.y};
        }
    }   // namespace score::button

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
        
namespace utils 
{
    static const std::vector<sf::Color> cColors = {
            sf::Color::Yellow,
            sf::Color::Cyan,
            sf::Color::Magenta,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Black
        };
}   // namespace utils

namespace gameplay
{

static constexpr float cBaseCircleVelocity = 0.2f;
static constexpr float cBaseAccelCircleVelocity = 1.0f;
static constexpr float cBaseReversCircleVelocity = -5.0f;

}   // namespace gameplay

}   // namespace config

}   // namespace zuma