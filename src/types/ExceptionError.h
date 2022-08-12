/******************************************************************************
**
** File      ExceptionError.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <expected/expected.h>

namespace zuma {

enum class ExceptionErrorType
{
    BadCast,
    Missing,
    NotInitialized,
    Unknown
};

class ExceptionError : public std::exception
{
public:
    explicit ExceptionError(const ExceptionErrorType& type, const std::string& message = {});

    const char* what() const noexcept override;

    std::string message() const;
    ExceptionErrorType type() const;

private:
    ExceptionErrorType m_type = ExceptionErrorType::Unknown;
    std::string m_message = "";
};

tl::unexpected<ExceptionError> makeUnexpected(const ExceptionErrorType& type, const std::string& message = {});

template<class T>
using Result = tl::expected<T, ExceptionError>;

}  // namespace zuma