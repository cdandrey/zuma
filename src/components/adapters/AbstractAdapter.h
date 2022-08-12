/******************************************************************************
**
** File      AbstractAdapter.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../objects/AbstractObject.h"

namespace zuma {

class AbstractAdapter
{
public:
    explicit AbstractAdapter(const AbstractObjectPtr& object);
    virtual ~AbstractAdapter() = 0;

protected:
    Result<AbstractObjectPtr> getObject() const;

private:
    AbstractObjectPtr m_object;
};

}  // namespace zuma