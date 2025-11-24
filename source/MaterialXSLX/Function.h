
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX Function class definition

#include <MaterialXCore/Library.h>
#include <MaterialXSLX/Argument.h>
#include <MaterialXSLX/DataType.h>
#include <MaterialXSLX/Export.h>

MATERIALX_NAMESPACE_BEGIN

/// @class SLXFunction
/// @brief Represents a function in SLX.
class MX_SLX_API SLXFunction
{
public:
    /// @brief Constructor for SLXFunction.
    /// @param name The function name.
    /// @param returnType The return type of the function.
    /// @param args The argument list for the function.
    SLXFunction(const string& name, SLXDataType returnType, const vector<SLXArgument>& args);

    /// @brief Get the function name.
    /// @return The function name.
    string getName() const;

    /// @brief Get the return type of the function.
    /// @return The return type.
    SLXDataType getReturnType() const;

    /// @brief Get the argument list for the function.
    /// @return The argument list.
    const vector<SLXArgument>& getArguments() const;

private:
    string _name; ///< Function name
    SLXDataType _returnType; ///< Return type
    vector<SLXArgument> _arguments; ///< Argument list
};

MATERIALX_NAMESPACE_END
