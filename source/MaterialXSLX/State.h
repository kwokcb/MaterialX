
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX global state management

#include <MaterialXCore/Library.h>
#include <MaterialXSLX/Function.h>

MATERIALX_NAMESPACE_BEGIN

namespace SLXState
{
    /// @brief Add a function to the global SLX state.
    /// @param function The SLXFunction to add.
    void addFunction(const SLXFunction& function);

    /// @brief Get the list of functions in the global SLX state.
    /// @return A const reference to the vector of SLXFunction.
    const vector<SLXFunction>& getFunctions();
}

MATERIALX_NAMESPACE_END
