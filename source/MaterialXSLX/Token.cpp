
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/Token.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXToken.
/// @param value The token value as a string.
SLXToken::SLXToken(const string& value)
    : _value(value) {}

/// @brief Get the value of the token.
/// @return The token value as a string.
string SLXToken::getValue() const { return _value; }

MATERIALX_NAMESPACE_END
