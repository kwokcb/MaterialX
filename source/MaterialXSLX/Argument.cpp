
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//


#include <MaterialXSLX/Argument.h>

MATERIALX_NAMESPACE_BEGIN


/// @brief Constructor for SLXArgument.
/// @param expr The expression for the argument.
/// @param position The argument position.
/// @param identifier The argument identifier (optional).
SLXArgument::SLXArgument(SLXExpressionPtr expr, int position, const string& identifier, const string& type)
    : _expr(expr), _position(position), _identifier(identifier), _type(type) {}


int SLXArgument::getPosition() const { return _position; }
string SLXArgument::getName() const { return _identifier; }
string SLXArgument::getType() const { return _type; }
bool SLXArgument::isInitialized() const { return static_cast<bool>(_expr); }
bool SLXArgument::isPositional() const { return !_identifier.empty(); }
bool SLXArgument::isNamed() const { return !_identifier.empty(); }
SLXExpressionPtr SLXArgument::getExpression() const { return _expr; }

MATERIALX_NAMESPACE_END
