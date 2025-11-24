
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once
#include <stdexcept>

/// @file
/// SLX CompileError exception definition

#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXCompileError
/// @brief Exception class for SLX compilation errors.
class SLXCompileError : public std::runtime_error
{
public:
    /// @brief Constructor for SLXCompileError.
    /// @param message The error message.
    explicit SLXCompileError(const string& message);
};

MATERIALX_NAMESPACE_END
