
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX Attribute class definition

#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXAttribute
/// @brief Represents an attribute for SLX functions and nodes.
class SLXAttribute
{
public:
    /// @brief Constructor for SLXAttribute.
    /// @param name The name of the attribute.
    /// @param value The value of the attribute.
    SLXAttribute(const string& name, const string& value);

    /// @brief Get the name of the attribute.
    /// @return The attribute name.
    string getName() const;

    /// @brief Get the value of the attribute.
    /// @return The attribute value.
    string getValue() const;

private:
    string _name; ///< Attribute name
    string _value; ///< Attribute value
};

MATERIALX_NAMESPACE_END
