
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/DecompileError.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXDecompileError.
/// @param message The error message.
SLXDecompileError::SLXDecompileError(const string& message)
    : std::runtime_error(message) {}

MATERIALX_NAMESPACE_END
