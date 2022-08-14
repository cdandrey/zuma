/******************************************************************************
**
** File      Property.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include "ExceptionError.h"
#include "Property_internal.h"

namespace zuma {

constexpr PropertyKey PropertyKeyPosition = "Position";
constexpr PropertyKey PropertyKeyVelocity = "Velocity";
constexpr PropertyKey PropertyKeyDirection = "Direction";
constexpr PropertyKey PropertyKeyRotatePosition = "RotatePosition";
constexpr PropertyKey PropertyKeyCircleVelocity = "CircleVelocity";
constexpr PropertyKey PropertyKeyOrigin = "Origin";
constexpr PropertyKey PropertyKeyColor = "Color";
constexpr PropertyKey PropertyKeyRadius = "Radius";

SPECIFY_PROPERTY_TYPE(PropertyKeyPosition, sf::Vector2f, PositionProperty)              // current point
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocity, float, VelocityProperty)                     // count pixels per tick
SPECIFY_PROPERTY_TYPE(PropertyKeyDirection, float, DirectionProperty)                   // angle relative to current position in radians
SPECIFY_PROPERTY_TYPE(PropertyKeyRotatePosition, sf::Vector2f, RotatePositionProperty)  // repositioning in the direction of a given point
SPECIFY_PROPERTY_TYPE(PropertyKeyCircleVelocity, float, CircleVelocityProperty)         // angel per tick
SPECIFY_PROPERTY_TYPE(PropertyKeyOrigin, sf::Vector2f, OriginProperty)                  // origin point
SPECIFY_PROPERTY_TYPE(PropertyKeyColor, sf::Color, ColorProperty)                       // current color
SPECIFY_PROPERTY_TYPE(PropertyKeyRadius,float,RadiusProperty)                           // radius of circle objects

}  // namespace zuma