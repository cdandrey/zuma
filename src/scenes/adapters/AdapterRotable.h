/******************************************************************************
**
** File      AdapterRotable.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractAdapter.h"

namespace zuma {

class AbstractAdapterRotable : public AbstractAdapter
{
public:
    explicit AbstractAdapterRotable(AbstractObject* object);
    virtual ~AbstractAdapterRotable() = default;

    virtual Result<PositionProperty::type> getPosition() const = 0;
    virtual Result<RotatePositionProperty::type> getRotatePosition() const = 0;
    virtual Result<void> setDirection(const DirectionProperty::type& value) = 0;
};

using AbstractAdapterRotablePtr = std::shared_ptr<AbstractAdapterRotable>;

class AdapterRotable : public AbstractAdapterRotable
{
public:
    explicit AdapterRotable(AbstractObject* object);

    Result<PositionProperty::type> getPosition() const override;
    virtual Result<RotatePositionProperty::type> getRotatePosition() const override;
    Result<void> setDirection(const DirectionProperty::type& value) override;
};

}  // namespace zuma