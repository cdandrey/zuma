/******************************************************************************
**
** File      AdapterMovable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "AdapterMovable.h"

#include <variant>

namespace zuma {

AbstractAdapterMovable::AbstractAdapterMovable(AbstractObject *object)
    : AbstractAdapter{ object }
{
}

AdapterMovable::AdapterMovable(AbstractObject *object)
    : AbstractAdapterMovable{ object }
{
}

Result<PositionProperty::type> AdapterMovable::getPosition() const
{
    const auto onGetPosition = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(PositionProperty::key);
    };

    return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

Result<DirectionProperty::type> AdapterMovable::getDirection() const
{
    const auto onGetDirection = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(DirectionProperty::key);
    };

    return getObject().and_then(onGetDirection).and_then(DirectionProperty::cast);
}

Result<OriginProperty::type> AdapterMovable::getOrigin() const
{
    const auto onGetOrigin = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(OriginProperty::key);
    };

    return getObject().and_then(onGetOrigin).and_then(OriginProperty::cast);
}

Result<VelocityProperty::type> AdapterMovable::getVelocity() const
{
    const auto onGetVelocity = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(VelocityProperty::key);
    };

    return getObject().and_then(onGetVelocity).and_then(VelocityProperty::cast);
}

Result<CircleVelocityProperty::type> AdapterMovable::getCircleVelocity() const
{
    const auto onGetCircleVelocity = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(CircleVelocityProperty::key);
    };

    return getObject().and_then(onGetCircleVelocity).and_then(CircleVelocityProperty::cast);
}

Result<void> AdapterMovable::setPosition(const PositionProperty::type& value)
{
    const auto onSetPosition = [&value](AbstractObject *object) -> Result<void> {
        return object->setProperty(PositionProperty::key, value);
    };

    return getObject().and_then(onSetPosition);
}

}  // namespace zuma