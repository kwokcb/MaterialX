//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//
/// @file
/// SLX Statement base class definition

#pragma once

#include <MaterialXCore/Document.h>
#include <MaterialXSLX/SLXExpression.h>
#include <memory>
#include <string>
#include <sstream>

MATERIALX_NAMESPACE_BEGIN

class SLXStatement;
using SLXStatementPtr = std::shared_ptr<SLXStatement>;

/// @class SLXStatement
/// @brief Base class for all SLX statements (AST nodes).

class SLXStatement
{
public:
    virtual ~SLXStatement() = default;
    virtual std::string getKind() const = 0;
    virtual void emitSLX(std::ostringstream& slx, int indent = 0) const = 0;
};

class SLXAssignmentStatement;
using SLXAssignmentStatementPtr = std::shared_ptr<SLXAssignmentStatement>;

class SLXAssignmentStatement : public SLXStatement
{
public:
    SLXAssignmentStatement(const std::string& type, const std::string& name, SLXExpressionPtr expr)
        : _type(type), _name(name), _expr(expr) {}
    static SLXAssignmentStatementPtr create(const std::string& type, const std::string& name, SLXExpressionPtr expr)
    {
        return std::make_shared<SLXAssignmentStatement>(type, name, expr);
    }
    std::string getKind() const override { return "assignment"; }
    void emitSLX(std::ostringstream& slx, int indent = 0) const override
    {
        std::string pad(indent, ' ');
        slx << pad << _type << " " << _name << " = ";
        if (_expr) _expr->emitSLX(slx);
        slx << ";\n";
    }
private:
    std::string _type;
    std::string _name;
    SLXExpressionPtr _expr;
};

class SLXExpressionStatement;
using SLXExpressionStatementPtr = std::shared_ptr<SLXExpressionStatement>;

class SLXExpressionStatement : public SLXStatement
{
public:
    SLXExpressionStatement(SLXExpressionPtr expr) : _expr(expr) {}
    static SLXExpressionStatementPtr create(SLXExpressionPtr expr)
    {
        return std::make_shared<SLXExpressionStatement>(expr);
    }
    std::string getKind() const override { return "expression"; }
    void emitSLX(std::ostringstream& slx, int indent = 0) const override
    {
        std::string pad(indent, ' ');
        slx << pad;
        if (_expr) _expr->emitSLX(slx);
        slx << ";\n";
    }
private:
    SLXExpressionPtr _expr;
};

MATERIALX_NAMESPACE_END
