
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLXDecompiler class definition. Converts MaterialX Document to SLX.

#include <MaterialXCore/Document.h>
#include <MaterialXSLX/Export.h>
#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXDecompiler
/// @brief Converts a MaterialX Document to SLX source code.
class MX_SLX_API SLXDecompiler
{
public:
    /// @brief Constructor for SLXDecompiler.
    SLXDecompiler();

    /// @brief Destructor for SLXDecompiler.
    ~SLXDecompiler();

    /// @brief Decompile a MaterialX Document to SLX source code.
    /// @param doc The MaterialX DocumentPtr to decompile.
    /// @return The SLX source code as a string.
    string decompile(const DocumentPtr& doc);
};

MATERIALX_NAMESPACE_END
