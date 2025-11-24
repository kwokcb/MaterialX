// SLXAST.h
// SLX AST node definitions for SLXCompiler
#pragma once
#include <string>
#include <vector>
#include <memory>



// MaterialX namespace macros
#include <MaterialXCore/Library.h>

MATERIALX_NAMESPACE_BEGIN


class SLXASTNode;
class SLXExpressionAST;
class SLXStatementAST;
using SLXASTNodePtr = std::shared_ptr<SLXASTNode>;
using SLXExpressionASTPtr = std::shared_ptr<SLXExpressionAST>;
using SLXStatementASTPtr = std::shared_ptr<SLXStatementAST>;

class SLXASTNode {
public:
    virtual ~SLXASTNode() = default;
};

class SLXExpressionAST : public SLXASTNode {
public:
    std::string type; // e.g. 'function_call', 'literal', 'variable', 'binary_op'
    std::string name; // function name or variable name
    std::string value; // literal value
    std::vector<SLXExpressionASTPtr> args; // function arguments or children
};

class SLXStatementAST : public SLXASTNode {
public:
    std::string type; // e.g. 'assignment', 'declaration', 'return', 'shader', 'function'
    std::string name; // variable or function name
    std::string value; // assigned value (for literals)
    std::string dataType; // variable type (e.g. float, color3)
    SLXExpressionASTPtr expr; // assigned expression or return value
    std::vector<SLXStatementASTPtr> children; // for blocks/functions
};

// Add more AST node types as needed (function, assignment, etc.)

MATERIALX_NAMESPACE_END
