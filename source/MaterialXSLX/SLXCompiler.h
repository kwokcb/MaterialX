
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLXCompiler class definition. Converts SLX to MaterialX Document.

#include <MaterialXCore/Document.h>
#include <MaterialXSLX/Export.h>
#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXCompiler
/// @brief Converts SLX source code to a MaterialX Document.

class MX_SLX_API SLXCompiler
{
public:
    /// @brief Constructor for SLXCompiler.
    SLXCompiler();

    /// @brief Destructor for SLXCompiler.
    ~SLXCompiler();

    /// @brief Set the standard library Document to use during compilation.
    /// @param stdlibDoc The standard library MaterialX DocumentPtr.
    void setStandardLibrary(const DocumentPtr& stdlibDoc);

    /// @brief Compile SLX source code to a MaterialX Document.
    /// @param slxSource The SLX source code as a string.
    /// @return A MaterialX DocumentPtr representing the compiled document.
    DocumentPtr compile(const string& slxSource);

private:
    DocumentPtr _standardLibrary;
};

MATERIALX_NAMESPACE_END
