/******************************************************************************
**
** File      ExceptionError.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "ExceptionError.h"

namespace zuma {

ExceptionError::ExceptionError(const ExceptionErrorType &type, const std::string &message)
    : m_type(type)
    , m_message(message)
{
}

const char *ExceptionError::what() const noexcept
{
	return m_message.c_str();
}

ExceptionErrorType ExceptionError::type() const
{
	return m_type;
}

std::string ExceptionError::message() const
{
	return m_message;
}

tl::unexpected<ExceptionError> makeUnexpected(const ExceptionErrorType &type, const std::string &message)
{
	return tl::make_unexpected(ExceptionError {type, message});
}

}  // namespace zuma