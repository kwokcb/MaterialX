//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX Token class definition

#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

class SLXToken;
using SLXTokenPtr = std::shared_ptr<SLXToken>;

/// @class SLXToken
/// @brief Represents a token in SLX source code.
class SLXToken
{
public:
    /// @brief Constructor for SLXToken.
    /// @param value The token value as a string.
    SLXToken(const string& value);

    static SLXTokenPtr create(const string& value)
    {
        return SLXTokenPtr(new SLXToken(value));
    }

    /// @brief Get the value of the token.
    /// @return The token value as a string.
    string getValue() const;

private:
    string _value; ///< Token value
};

MATERIALX_NAMESPACE_END
