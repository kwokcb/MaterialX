
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/Attribute.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXAttribute.
/// @param name The name of the attribute.
/// @param value The value of the attribute.
SLXAttribute::SLXAttribute(const string& name, const string& value)
    : _name(name), _value(value) {}

/// @brief Get the name of the attribute.
/// @return The attribute name.
string SLXAttribute::getName() const { return _name; }

/// @brief Get the value of the attribute.
/// @return The attribute value.
string SLXAttribute::getValue() const { return _value; }

MATERIALX_NAMESPACE_END
