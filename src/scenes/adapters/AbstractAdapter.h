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
    explicit AbstractAdapter(AbstractObject* object);
    virtual ~AbstractAdapter() = 0;

protected:
    Result<AbstractObject*> getObject() const;

private:
    AbstractObject *m_object;
};

}  // namespace zuma