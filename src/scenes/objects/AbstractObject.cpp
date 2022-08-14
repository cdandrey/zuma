/******************************************************************************
**
** File      AbstractObject.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "AbstractObject.h"

#include <typeinfo>

namespace zuma {

AbstractObject::~AbstractObject()
{
}

Result<PropertyValue> AbstractObject::getProperty(PropertyKey key) const
{
	return hasProperty(key).map([this, key]() -> PropertyValue {
		return m_propertys.at(key);
	});
}

Result<void> AbstractObject::setProperty(PropertyKey key, const PropertyValue &value)
{
	const auto onSuccess = [this, key, value]() {
		m_propertys[key] = value;
	};

	return hasProperty(key).map(onSuccess);
}

Result<void> AbstractObject::hasProperty(PropertyKey key) const
{
	if (m_propertys.find(key) != m_propertys.end()) {
		return {};
	}

	std::string msg {"Object " + std::string {typeid(*this).name()} + " does not have the property " + std::string {key}};
	return makeUnexpected(ExceptionErrorType::Missing, msg);
}

}  // namespace zuma