
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/State.h>

MATERIALX_NAMESPACE_BEGIN

namespace SLXState
{
    static vector<SLXFunction> functions;

    /// @brief Add a function to the global SLX state.
    /// @param function The SLXFunction to add.
    void addFunction(const SLXFunction& function)
    {
        functions.push_back(function);
    }

    /// @brief Get the list of functions in the global SLX state.
    /// @return A const reference to the vector of SLXFunction.
    const vector<SLXFunction>& getFunctions()
    {
        return functions;
    }
}

MATERIALX_NAMESPACE_END
