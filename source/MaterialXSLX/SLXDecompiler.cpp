
//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/SLXDecompiler.h>
#include <MaterialXSLX/Wrapper.h>
#include <MaterialXSLX/SLXStatement.h>
#include <MaterialXSLX/SLXExpression.h>
#include <MaterialXCore/Document.h>
#include <sstream>
//#include <set>
//#include <vector>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXDecompiler.
SLXDecompiler::SLXDecompiler() {}

/// @brief Destructor for SLXDecompiler.
SLXDecompiler::~SLXDecompiler() {}



// Helper: Map node category to SLX operator/function
static std::string mapCategoryToSLX(const std::string& category)
{
    static const std::unordered_map<std::string, std::string> arithmeticOps = {
        {"add", "+"}, {"subtract", "-"}, {"multiply", "*"}, {"divide", "/"}, {"modulo", "%"}, {"power", "^"}
    };
    static const std::unordered_map<std::string, std::string> comparisonOps = {
        {"ifequal", "=="}, {"ifgreater", ">"}, {"ifgreatereq", ">="}
    };
    static const std::unordered_map<std::string, std::string> logicOps = {
        {"and", "&"}, {"or", "|"}
    };
    static const std::unordered_map<std::string, std::string> unaryOps = {
        {"not", "!"}
    };
    if (arithmeticOps.count(category)) return arithmeticOps.at(category);
    if (comparisonOps.count(category)) return comparisonOps.at(category);
    if (logicOps.count(category)) return logicOps.at(category);
    if (unaryOps.count(category)) return unaryOps.at(category);
    return category; // fallback: use category as function name
}




// Helper: Convert node to SLXExpressionPtr (AST)
static SLXExpressionPtr nodeToSLXExpression(const MXNodeWrapperPtr& nodeWrapper)
{
    const std::string& category = nodeWrapper->getCategory();
    std::vector<SLXExpressionPtr> args;
    for (const auto& inputWrapper : nodeWrapper->getInputs())
    {
        MaterialX::NodePtr inputNode = inputWrapper->getConnectedNode();
        if (inputNode)
        {
            MXNodeWrapperPtr inputNodeWrapper = std::make_shared<MXNodeWrapper>(inputNode);
            args.push_back(nodeToSLXExpression(inputNodeWrapper));
        }
        else if (inputWrapper->hasValue())
        {
            args.push_back(SLXLiteralExpression::create(inputWrapper->getValueString(), inputWrapper->getType()));
        }
        else
        {
            args.push_back(SLXLiteralExpression::create("/*unconnected*/", inputWrapper->getType()));
        }
    }
    // Arithmetic, logic, comparison, unary
    if (category == "constant" && !args.empty())
        return args[0];
    if (category == "extract" && args.size() >= 2)
        return SLXFunctionCallExpression::create("extract", args, nodeWrapper->getType());
    if (category == "switch" && args.size() >= 2)
        return SLXFunctionCallExpression::create("switch", args, nodeWrapper->getType());
    if (category == "not" && !args.empty())
        return SLXFunctionCallExpression::create("not", args, nodeWrapper->getType());
    if (category == "combine2" || category == "combine3" || category == "combine4")
        return SLXFunctionCallExpression::create(nodeWrapper->getType(), args, nodeWrapper->getType());
    if (category == "add" || category == "subtract" || category == "multiply" || category == "divide" || category == "modulo" || category == "power")
        return SLXFunctionCallExpression::create(mapCategoryToSLX(category), args, nodeWrapper->getType());
    if (category == "ifequal" || category == "ifgreater" || category == "ifgreatereq")
        return SLXFunctionCallExpression::create(mapCategoryToSLX(category), args, nodeWrapper->getType());
    if (category == "and" || category == "or")
        return SLXFunctionCallExpression::create(mapCategoryToSLX(category), args, nodeWrapper->getType());
    // Fallback: function call
    return SLXFunctionCallExpression::create(category, args, nodeWrapper->getType());
}

/// @brief Helper to recursively decompile a node and its inputs.
/// @param node The node to decompile.
/// @param decompiledNodes Set of already decompiled nodes.
/// @param slx Output stream for SLX code.


// Helper: Convert node to SLXStatementPtr (AST)

static SLXStatementPtr nodeToSLXStatement(const MXNodeWrapperPtr& nodeWrapper)
{
    SLXExpressionPtr expr = nodeToSLXExpression(nodeWrapper);
    if (nodeWrapper->getType() == "void")
    {
        return SLXExpressionStatement::create(expr);
    }
    else
    {
        return SLXAssignmentStatement::create(nodeWrapper->getType(), nodeWrapper->getName(), expr);
    }
}

// Recursively build AST for all nodes
static void buildAST(const MXNodeWrapperPtr& nodeWrapper, std::set<MaterialX::NodePtr>& visited, std::vector<SLXStatementPtr>& statements)
{
    MaterialX::NodePtr node = nodeWrapper->getNode();
    if (!node || visited.count(node)) return;
    // Recursively build AST for input nodes
    for (const auto& inputWrapper : nodeWrapper->getInputs())
    {
        MaterialX::NodePtr inputNode = inputWrapper->getConnectedNode();
        if (inputNode)
        {
            MXNodeWrapperPtr inputNodeWrapper = std::make_shared<MXNodeWrapper>(inputNode);
            buildAST(inputNodeWrapper, visited, statements);
        }
    }
    // Build statement for this node
    SLXStatementPtr stmt = nodeToSLXStatement(nodeWrapper);
    if (stmt)
        statements.push_back(stmt);
    visited.insert(node);
}

/// @brief Decompile a MaterialX Document to SLX source code.
/// @param doc The MaterialX DocumentPtr to decompile.
/// @return The SLX source code as a string.


string SLXDecompiler::decompile(const DocumentPtr& doc)
{
    if (!doc)
        return "";
    MXDocumentWrapperPtr docWrapper = std::make_shared<MXDocumentWrapper>(doc);
    std::set<MaterialX::NodePtr> visited;
    std::vector<SLXStatementPtr> statements;
    for (const MXNodeWrapperPtr& nodeWrapper : docWrapper->getNodes())
        buildAST(nodeWrapper, visited, statements);
    // Traverse AST and emit SLX code
    std::ostringstream slx;
    for (const SLXStatementPtr& stmt : statements)
    {
        if (stmt) stmt->emitSLX(slx);
    }
    return slx.str();
}

MATERIALX_NAMESPACE_END
