/******************************************************************************
**
** File      AdapterRotable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "AdapterRotable.h"

#include <variant>

namespace zuma {

AbstractAdapterRotable::AbstractAdapterRotable(AbstractObject *object)
    : AbstractAdapter{ object }
{
}

AdapterRotable::AdapterRotable(AbstractObject* object)
    : AbstractAdapterRotable{ object }
{
}

Result<PositionProperty::type> AdapterRotable::getPosition() const
{
    const auto onGetPosition = [](AbstractObject *object) -> Result<PropertyValue> {

        return object->getProperty(PositionProperty::key);
    };

    return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

Result<RotatePositionProperty::type> AdapterRotable::getRotatePosition() const
{
    const auto onGetRotatePosition = [](AbstractObject *object) -> Result<PropertyValue> {
        return object->getProperty(RotatePositionProperty::key);
    };

    return getObject().and_then(onGetRotatePosition).and_then(RotatePositionProperty::cast);
}

Result<void> AdapterRotable::setDirection(const DirectionProperty::type& value)
{
    const auto onSetDirection = [&value](AbstractObject *object) -> Result<void> {
        return object->setProperty(DirectionProperty::key, value);
    };

    return getObject().and_then(onSetDirection);
}

}  // namespace zuma