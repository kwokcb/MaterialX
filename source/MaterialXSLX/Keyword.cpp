
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/Keyword.h>

MATERIALX_NAMESPACE_BEGIN

namespace SLXKeyword
{
    /// @brief Set of SLX language keywords.
    const std::unordered_set<string> keywords = {
        "float", "int", "bool", "string", "filename", "void",
        // Add more SLX keywords as needed
    };
}

MATERIALX_NAMESPACE_END
