
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once
#include <stdexcept>

/// @file
/// SLX DecompileError exception definition

#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXDecompileError
/// @brief Exception class for SLX decompilation errors.
class SLXDecompileError : public std::runtime_error
{
public:
    /// @brief Constructor for SLXDecompileError.
    /// @param message The error message.
    explicit SLXDecompileError(const string& message);
};

MATERIALX_NAMESPACE_END
