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

static const     sf::Vector2u cBaseWindowSize      = {1920,1080};
static constexpr float        cRadiansToDegreeCoef = 180.0f / 3.14f;

static sf::Vector2f scaleFactor(sf::Vector2u windowSize)
{   
    return {static_cast<float>(windowSize.x) / static_cast<float>(cBaseWindowSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(cBaseWindowSize.y)};
}

static sf::Vector2f scaled(sf::Vector2u windowSize,sf::Vector2f value) 
{
    const auto scale = scaleFactor(windowSize);
    return {scale.x * value.x, scale.y * value.y};
}


namespace button
{
    struct Style 
    {
        sf::Color   cFillColor       ;
        sf::Color   cBorderColor     ;
        float       cBorderThickness ;
        sf::Color   cHoverFillColor  ;
        sf::Color   cHoverBorderColor;
        sf::Color   cTextColor       ;
        sf::Color   cHoverTextColor  ;
        int         cTextSize        ;
        std::string cFontPath        ;
    };

}   // namespace config::button

namespace table
{
    struct Style
    {
        sf::Color   cFillColor      ;
        sf::Color   cBorderColor    ;
        float       cBorderThickness;
        sf::Color   cTextColor      ;
        int         cTextSize       ;
        std::string cFontPath       ;
    };
}   // namespace config::table

namespace menu
{
    namespace button
    {
        static const sf::Vector2f cBaseSize     = {400.0f,100.0f};
        static const sf::Vector2f cBasePosition = {300.0f,cBaseWindowSize.y - 150.0f};
        static const float        cPadding      = 10.0f;

        static sf::Vector2f position(int count,int idx,sf::Vector2u windowSize) 
        {
            return {cBasePosition.x,
                    cBasePosition.y - (count - idx - 1)*(cBaseSize.y + cPadding)};
        }

        static const config::button::Style cStyle = {
            sf::Color::White                   , // cFillColor        
            sf::Color::Black                   , // cBorderColor      
            2.0f                               , // cBorderThickness  
            sf::Color::Black                   , // cHoverFillColor   
            sf::Color::Black                   , // cHoverBorderColor 
            sf::Color::Black                   , // cTextColor        
            sf::Color::White                   , // cHoverTextColor   
            32                                 , // cTextSize         
            "resources/font/Comfortaa-Bold.ttf"  // cFontPath         
        };

    }   // namespace menu::button

}   // namespace menu

namespace score
{
    static const sf::Vector2f cBaseSize        = {600.0f,400.0f};
    static const sf::Vector2f cBasePosition    = {cBaseWindowSize.x / 2.0f, cBaseWindowSize.y / 2.0f};
    
    static const config::table::Style cStyle = {
        sf::Color::White                    , //   cFillColor      
        sf::Color::Black                    , //   cBorderColor    
        2.0f                                , //   cBorderThickness
        sf::Color::Black                    , //   cTextColor      
        32                                  , //   cTextSize       
        "resources/font/Comfortaa-Bold.ttf"   //   cFontPath       
    };

    namespace button
    {
        static const sf::Vector2f cBaseSize = {config::score::cBaseSize.x, 40.0f};
        static const sf::Vector2f cBasePosition = {config::score::cBasePosition.x,
                                                   config::score::cBasePosition.y + 
                                                   config::score::cBaseSize.y / 2.0f + 
                                                   cBaseSize.y / 2.0f + 
                                                   cBaseSize.y / 4.0f /*padding*/};
    
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

    static float radius(sf::Vector2u windowSize) 
    {
         const auto scale = static_cast<float>(windowSize.x * windowSize.x + windowSize.y * windowSize.y) /
                            static_cast<float>(cBaseWindowSize.x*cBaseWindowSize.x + cBaseWindowSize.y * cBaseWindowSize.y);
        return cBaseRadius * scale;
    }

    static sf::Vector2f startPosition(sf::Vector2u windowSize)
    {
        return {windowSize.x / 2.0f, radius(windowSize) * 2.0f};
    }

}   // namespace object_ball
        
namespace gameplay
{

static constexpr float cBaseCircleVelocity = 0.1f;
static constexpr float cBaseAccelCircleVelocity = 1.0f;
static constexpr float cBaseReversCircleVelocity = -1.0f;
static constexpr float cBaseShotVelocity = 1000.0f;

}   // namespace gameplay

namespace gamestate
{
using DataScore = struct {
                    unsigned shots;
                    unsigned destroed;
                    float efficiency;
                };

}   // namespace gamestate

}   // namespace config

}   // namespace zuma