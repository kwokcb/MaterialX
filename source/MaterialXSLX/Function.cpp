
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/Function.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXFunction.
/// @param name The function name.
/// @param returnType The return type of the function.
/// @param args The argument list for the function.
SLXFunction::SLXFunction(const string& name, SLXDataType returnType, const vector<SLXArgument>& args)
    : _name(name), _returnType(returnType), _arguments(args) {}

/// @brief Get the function name.
/// @return The function name.
string SLXFunction::getName() const { return _name; }

/// @brief Get the return type of the function.
/// @return The return type.
SLXDataType SLXFunction::getReturnType() const { return _returnType; }

/// @brief Get the argument list for the function.
/// @return The argument list.
const vector<SLXArgument>& SLXFunction::getArguments() const { return _arguments; }

MATERIALX_NAMESPACE_END
