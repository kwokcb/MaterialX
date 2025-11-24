
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX DataType definitions

#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @enum SLXDataType
/// @brief Enum for supported SLX data types.
enum class SLXDataType
{
    BOOLEAN,   ///< Boolean type
    INTEGER,   ///< Integer type
    FLOAT,     ///< Float type
    STRING,    ///< String type
    FILENAME,  ///< Filename type
    VOID,      ///< Void type
    // Add more types as needed
};

/// @brief Convert SLXDataType to string.
/// @param type The SLXDataType value.
/// @return The string representation of the type.
string toString(SLXDataType type);

MATERIALX_NAMESPACE_END
