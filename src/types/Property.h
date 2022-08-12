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

SPECIFY_PROPERTY_TYPE(PropertyKeyPosition, sf::Vector2f, PositionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocity, sf::Vector2f, VelocityProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyDirection, float, DirectionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyRotatePosition, sf::Vector2f, RotatePositionProperty)

}  // namespace zuma