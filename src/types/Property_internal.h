
/******************************************************************************
**
** File      Property_internal.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace zuma {

using PropertyKey = std::string_view;
using PropertyValue = std::any;
using PropertyMap = std::unordered_map<PropertyKey, PropertyValue>;

template<const PropertyKey& key>
struct Property
{
};

#define SPECIFY_PROPERTY_TYPE(Key, Type, UsingName)                                                                                                            \
	template<>                                                                                                                                                 \
	struct Property<Key>                                                                                                                                       \
	{                                                                                                                                                          \
		using type = Type;                                                                                                                                     \
		static constexpr PropertyKey key = Key;                                                                                                                \
		static Result<type> cast(PropertyValue value)                                                                                                          \
		{                                                                                                                                                      \
			try {                                                                                                                                              \
				return std::any_cast<type>(value);                                                                                                             \
			} catch (std::bad_any_cast & e) {                                                                                                                  \
				return makeUnexpected(ExceptionErrorType::BadCast, e.what());                                                                                  \
			} catch (...) {                                                                                                                                    \
				return makeUnexpected(ExceptionErrorType::Unknown, {"Unknown error of type cast of property " + std::string {Key}});                           \
			}                                                                                                                                                  \
		}                                                                                                                                                      \
	};                                                                                                                                                         \
	using UsingName = Property<Key>;

}  // namespace zuma