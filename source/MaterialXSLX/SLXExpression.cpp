//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/SLXExpression.h>

MATERIALX_NAMESPACE_BEGIN

// Only implement missing static factory methods to resolve linker errors

SLXFunctionCallExpressionPtr SLXFunctionCallExpression::create(const std::string& name, const std::vector<SLXFunctionCallExpression::Argument>& args, const std::string& type)
{
    return std::make_shared<SLXFunctionCallExpression>(name, args, type);
}

SLXLiteralExpressionPtr SLXLiteralExpression::create(const std::string& value, const std::string& type)
{
    return std::make_shared<SLXLiteralExpression>(value, type);
}

SLXIdentifierExpressionPtr SLXIdentifierExpression::create(const std::string& name, const std::string& type)
{
    return std::make_shared<SLXIdentifierExpression>(name, type);
}

MATERIALX_NAMESPACE_END
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//
#include <MaterialXSLX/SLXExpression.h>
#include <sstream>

MATERIALX_NAMESPACE_BEGIN


/// @brief Construct a function call expression.

SLXFunctionCallExpression::SLXFunctionCallExpression(const std::string& name, const std::vector<Argument>& args, const std::string& type)
    : _name(name), _arguments(args), _type(type) {}

/// @brief Get the type of the function call expression.
std::string SLXFunctionCallExpression::getType() const { return _type; }

/// @brief Get the function name.
std::string SLXFunctionCallExpression::getName() const { return _name; }

/// @brief Get the arguments of the function call.
const std::vector<SLXFunctionCallExpression::Argument>& SLXFunctionCallExpression::getArguments() const { return _arguments; }

/// @brief Emit SLX code for this function call.
void SLXFunctionCallExpression::emitSLX(std::ostringstream& slx) const {
    slx << _name << "(";
    for (size_t i = 0; i < _arguments.size(); ++i) {
        if (i > 0) slx << ", ";
        const auto& arg = _arguments[i];
        if (!arg.name.empty()) {
            slx << arg.name << "=";
        }
        if (arg.expr) arg.expr->emitSLX(slx);
    }
    slx << ")";
}

/// @brief Construct an identifier expression.
SLXIdentifierExpression::SLXIdentifierExpression(const std::string& name, const std::string& type)
    : _name(name), _type(type) {}

/// @brief Get the type of the identifier expression.
std::string SLXIdentifierExpression::getType() const { return _type; }

/// @brief Get the identifier name.
std::string SLXIdentifierExpression::getName() const { return _name; }

/// @brief Emit SLX code for this identifier.
void SLXIdentifierExpression::emitSLX(std::ostringstream& slx) const {
    slx << _name;
}

/// @brief Construct a literal expression.
SLXLiteralExpression::SLXLiteralExpression(const std::string& value, const std::string& type)
    : _value(value), _type(type) {}

/// @brief Get the type of the literal expression.
std::string SLXLiteralExpression::getType() const { return _type; }

/// @brief Get the literal value.
std::string SLXLiteralExpression::getValue() const { return _value; }

/// @brief Emit SLX code for this literal.
void SLXLiteralExpression::emitSLX(std::ostringstream& slx) const {
    slx << _value;
}

MATERIALX_NAMESPACE_END