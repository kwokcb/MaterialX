//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//
/// @file
/// SLX Expression classes: base, function call, identifier, literal

#pragma once
#include <MaterialXCore/Document.h>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

MATERIALX_NAMESPACE_BEGIN



/// @class SLXExpression
/// @brief Base class for all SLX expressions (AST nodes).
class SLXExpression {
public:
    /// @brief Virtual destructor.
    virtual ~SLXExpression() = default;
    /// @brief Get the type of the expression.
    virtual std::string getType() const = 0;
    /// @brief Check if the expression is initialized.
    virtual bool isInitialized() const { return true; }
    /// @brief Emit SLX code for this expression.
    virtual void emitSLX(std::ostringstream& slx) const = 0;
};

using SLXExpressionPtr = std::shared_ptr<SLXExpression>;

class SLXFunctionCallExpression;
using SLXFunctionCallExpressionPtr = std::shared_ptr<SLXFunctionCallExpression>;

/// @class SLXFunctionCallExpression
/// @brief Represents a function or node call in SLX.
class SLXFunctionCallExpression : public SLXExpression {
public:
    /// @brief Construct a function call expression.
    SLXFunctionCallExpression(const std::string& name, const std::vector<SLXExpressionPtr>& args, const std::string& type = "");
    /// @brief Factory method to create a function call expression.
    static SLXFunctionCallExpressionPtr create(const std::string& name, const std::vector<SLXExpressionPtr>& args, const std::string& type = "");
    /// @brief Get the type of the expression.
    std::string getType() const override;
    /// @brief Get the arguments of the function call.
    const std::vector<SLXExpressionPtr>& getArguments() const;
    /// @brief Get the function name.
    std::string getName() const;
    /// @brief Emit SLX code for this function call.
    void emitSLX(std::ostringstream& slx) const override;
private:
    std::string _name;
    std::vector<SLXExpressionPtr> _arguments;
    std::string _type;
};

class SLXIdentifierExpression;
using SLXIdentifierExpressionPtr = std::shared_ptr<SLXIdentifierExpression>;

/// @class SLXIdentifierExpression
/// @brief Represents an identifier (variable) in SLX.
class SLXIdentifierExpression : public SLXExpression {
public:
    /// @brief Construct an identifier expression.
    SLXIdentifierExpression(const std::string& name, const std::string& type = "");
    /// @brief Factory method to create an identifier expression.
    static SLXIdentifierExpressionPtr create(const std::string& name, const std::string& type = "");
    /// @brief Get the type of the expression.
    std::string getType() const override;
    /// @brief Get the identifier name.
    std::string getName() const;
    /// @brief Emit SLX code for this identifier.
    void emitSLX(std::ostringstream& slx) const override;
private:
    std::string _name;
    std::string _type;
};

class SLXLiteralExpression;
using SLXLiteralExpressionPtr = std::shared_ptr<SLXLiteralExpression>;

/// @class SLXLiteralExpression
/// @brief Represents a literal value in SLX (int, float, string, etc.).
class SLXLiteralExpression : public SLXExpression {
public:
    /// @brief Construct a literal expression.
    SLXLiteralExpression(const std::string& value, const std::string& type);
    /// @brief Factory method to create a literal expression.
    static SLXLiteralExpressionPtr create(const std::string& value, const std::string& type);
    /// @brief Get the type of the expression.
    std::string getType() const override;
    /// @brief Get the literal value.
    std::string getValue() const;
    /// @brief Emit SLX code for this literal.
    void emitSLX(std::ostringstream& slx) const override;
private:
    std::string _value;
    std::string _type;
};

MATERIALX_NAMESPACE_END