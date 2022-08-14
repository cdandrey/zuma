/******************************************************************************
**
** File      AbstractObject.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../../types/ExceptionError.h"
#include "../../types/Property.h"

#include <memory>

namespace zuma {

class AbstractObject
{
public:
    template<typename... Args>
    explicit AbstractObject(Args &&...args);

    virtual ~AbstractObject() = 0;

    Result<PropertyValue> getProperty(PropertyKey key) const;
    Result<void> setProperty(PropertyKey key, const PropertyValue& value);

private:
    PropertyMap m_propertys;

    Result<void> hasProperty(PropertyKey key) const;
};

using AbstractObjectPtr = std::shared_ptr<AbstractObject>;

template<typename... Args>
AbstractObject::AbstractObject(Args &&...args)
    : m_propertys{ std::forward<Args>(args)... }
{
}

template<typename Prop, typename PropType = Prop::type>
static Result<PropType> PropertyGet(const AbstractObjectPtr& object)
{
    return object->getProperty(Prop::key).and_then(Prop::cast);
}

}  // namespace zuma