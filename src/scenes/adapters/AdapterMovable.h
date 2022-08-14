/******************************************************************************
**
** File      AdapterMovable.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractAdapter.h"

namespace zuma {

class AbstractAdapterMovable : public AbstractAdapter
{
public:
    explicit AbstractAdapterMovable(AbstractObject *object);
    virtual ~AbstractAdapterMovable() = default;

    virtual Result<PositionProperty::type> getPosition() const = 0;
    virtual Result<OriginProperty::type> getOrigin() const = 0;
    virtual Result<VelocityProperty::type> getVelocity() const = 0;
    virtual Result<CircleVelocityProperty::type> getCircleVelocity() const = 0;
    virtual Result<void> setPosition(const PositionProperty::type& value) = 0;
};

using AbstractAdapterMovablePtr = std::shared_ptr<AbstractAdapterMovable>;

class AdapterMovable : public AbstractAdapterMovable
{
public:
    explicit AdapterMovable(AbstractObject *object);

    Result<PositionProperty::type> getPosition() const override;
    Result<OriginProperty::type> getOrigin() const override;
    Result<VelocityProperty::type> getVelocity() const override;
    Result<CircleVelocityProperty::type> getCircleVelocity() const override;
    Result<void> setPosition(const PositionProperty::type& value) override;
};

}  // namespace zuma