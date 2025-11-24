
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// SLX Argument class definition


#include <MaterialXCore/Library.h>
#include <MaterialXCore/Document.h>
#include <memory>
#include <string>
#include <MaterialXSLX/SLXExpression.h>

// Forward declaration for SLXExpressionPtr
class SLXExpression;
using SLXExpressionPtr = std::shared_ptr<SLXExpression>;

MATERIALX_NAMESPACE_BEGIN

class SLXArgument;
using std::shared_ptr;
using SLXArgumentPtr = shared_ptr<SLXArgument>;

class SLXArgument
{
public:
    /// @brief Constructor for SLXArgument.
    /// @param expr The expression for the argument.
    /// @param position The argument position.
    /// @param identifier The argument identifier (optional).
    SLXArgument(SLXExpressionPtr expr, int position, const std::string& identifier = "", const std::string& type = "");

    static SLXArgumentPtr create(SLXExpressionPtr expr, int position, const std::string& identifier = "", const std::string& type = "")
    {
        return std::make_shared<SLXArgument>(expr, position, identifier, type);
    }

    int getPosition() const;
    std::string getName() const;
    std::string getType() const;
    bool isInitialized() const;
    bool isPositional() const;
    bool isNamed() const;
    SLXExpressionPtr getExpression() const;

private:
    SLXExpressionPtr _expr;
    int _position;
    std::string _identifier;
    std::string _type;
};

MATERIALX_NAMESPACE_END
