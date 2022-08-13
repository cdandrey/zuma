/******************************************************************************
**
** File      AbstractAdapter.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "AbstractAdapter.h"

namespace zuma {

AbstractAdapter::AbstractAdapter(AbstractObject* object)
    : m_object{ object }
{
}

AbstractAdapter::~AbstractAdapter()
{
}

Result<AbstractObject*> AbstractAdapter::getObject() const
{
    if (m_object != nullptr)
    {
        return m_object;
    }

    return makeUnexpected(ExceptionErrorType::NotInitialized, std::string{ "Object of adapter is not initialized" });
}

}  // namespace zuma
