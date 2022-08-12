#include "AdapterRotable.h"

#include <variant>

namespace zuma {

AbstractAdapterRotable::AbstractAdapterRotable(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
{
}

AdapterRotable::AdapterRotable(const AbstractObjectPtr& object)
    : AbstractAdapterRotable{ object }
{
}

Result<PositionProperty::type> AdapterRotable::getPosition() const
{
    const auto onGetPosition = [](const AbstractObjectPtr& object) -> Result<PropertyValue> {

        return object->getProperty(PositionProperty::key);
    };

    return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

Result<RotatePositionProperty::type> AdapterRotable::getRotatePosition() const
{
    const auto onGetRotatePosition = [](const AbstractObjectPtr& object) -> Result<PropertyValue> {
        return object->getProperty(RotatePositionProperty::key);
    };

    return getObject().and_then(onGetRotatePosition).and_then(RotatePositionProperty::cast);
}

Result<void> AdapterRotable::setDirection(const DirectionProperty::type& value)
{
    const auto onSetDirection = [&value](const AbstractObjectPtr& object) -> Result<void> {
        return object->setProperty(DirectionProperty::key, value);
    };

    return getObject().and_then(onSetDirection);
}

}  // namespace zuma