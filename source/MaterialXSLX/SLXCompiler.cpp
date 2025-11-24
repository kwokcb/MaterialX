//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//


#include <MaterialXSLX/SLXCompiler.h>
#include <MaterialXCore/Document.h>
#include <MaterialXCore/Types.h>
#include <MaterialXCore/Node.h>
#include <MaterialXCore/Material.h>
#include <MaterialXSLX/SLXParser.h>
#include <MaterialXSLX/SLXAST.h>
#include <sstream>
#include <map>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXCompiler.
SLXCompiler::SLXCompiler() : _standardLibrary(nullptr) {}

/// @brief Destructor for SLXCompiler.
SLXCompiler::~SLXCompiler() {}

/// @brief Set the standard library Document to use during compilation.
/// @param stdlibDoc The standard library MaterialX DocumentPtr.
void SLXCompiler::setStandardLibrary(const DocumentPtr& stdlibDoc)
{
    _standardLibrary = stdlibDoc;
}

/// @brief Compile SLX source code to a MaterialX Document.
/// @param slxSource The SLX source code as a string.
/// @return A MaterialX DocumentPtr representing the compiled document.
DocumentPtr SLXCompiler::compile(const string& slxSource)
{

    // Parse SLX source to AST using improved parser
    MaterialX::SLXParser parser;
    std::vector<MaterialX::SLXStatementASTPtr> ast = parser.parse(slxSource);

    DocumentPtr doc = createDocument();
    MaterialX::NodeGraphPtr nodeGraph = doc->addNodeGraph("main_graph");
    std::map<std::string, MaterialX::NodePtr> nodeMap;
    MaterialX::NodePtr materialNode = nullptr;

    // Walk AST and map SLX constructs to MaterialX
    for (const auto& stmt : ast)
    {
        if (!stmt) continue;
        if (stmt->type == "assignment" || stmt->type == "declaration")
        {
            // Handle function calls as node creation
            if (stmt->expr && stmt->expr->type == "function_call")
            {
                std::string nodeType = stmt->dataType.empty() ? stmt->expr->name : stmt->dataType;
                MaterialX::NodePtr node = nodeGraph->addNode(nodeType, stmt->name);
                nodeMap[stmt->name] = node;
                // Set inputs for arguments
                for (size_t i = 0; i < stmt->expr->args.size(); ++i)
                {
                    auto& arg = stmt->expr->args[i];
                    std::string inputName = "in" + std::to_string(i);
                    if (arg->type == "literal")
                    {
                        node->setInputValue(inputName, arg->value);
                    }
                    else if (arg->type == "variable")
                    {
                        // Connect input to another node's output
                        if (nodeMap.count(arg->name))
                        {
                            node->setConnectedNode(inputName, nodeMap[arg->name]);
                        }
                    }
                }
            }
            // Handle direct value assignment to node input
            else if (stmt->expr && stmt->expr->type == "literal")
            {
                if (!nodeMap.empty())
                {
                    auto& lastNode = nodeMap.rbegin()->second;
                    lastNode->setInputValue(stmt->name, stmt->expr->value);
                }
            }
        }
        else if (stmt->type == "return")
        {
            // Connect last node to material output
            if (!nodeMap.empty())
            {
                auto& lastNode = nodeMap.rbegin()->second;
                materialNode = doc->addMaterialNode("main_material", lastNode);
            }
        }
        // TODO: Add more statement types (for, if, function, etc.)
    }

    return doc;
}

MATERIALX_NAMESPACE_END
