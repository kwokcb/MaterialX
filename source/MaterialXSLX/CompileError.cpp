
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/CompileError.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXCompileError.
/// @param message The error message.
SLXCompileError::SLXCompileError(const string& message)
    : std::runtime_error(message) {}

MATERIALX_NAMESPACE_END
