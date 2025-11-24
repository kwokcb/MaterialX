
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/DataType.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Convert SLXDataType to string.
/// @param type The SLXDataType value.
/// @return The string representation of the type.
string toString(SLXDataType type)
{
    switch (type)
    {
    case SLXDataType::BOOLEAN: return "boolean";
    case SLXDataType::INTEGER: return "integer";
    case SLXDataType::FLOAT: return "float";
    case SLXDataType::STRING: return "string";
    case SLXDataType::FILENAME: return "filename";
    case SLXDataType::VOID: return "void";
    default: return "unknown";
    }
}

MATERIALX_NAMESPACE_END
