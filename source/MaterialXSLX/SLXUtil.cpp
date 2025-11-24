#include <MaterialXSLX/SLXUtil.h>
#include <MaterialXSLX/SLXExpression.h>
#include <MaterialXSLX/SLXLiteralExpression.h>
#include <MaterialXSLX/SLXIdentifierExpression.h>
#include <MaterialXSLX/SLXFunctionCallExpression.h>
#include <MaterialXSLX/Argument.h>
#include <MaterialXCore/Document.h>
#include <sstream>
#include <regex>
#include <iostream>

MATERIALX_NAMESPACE_BEGIN

void SLXParser::parseStatement(MaterialX::DocumentPtr doc)
{
    // Example: parse a single expression and print its type
        SLXExpressionPtr expr = parseExpression(); // Updated to use SLXExpressionPtr
    if (expr) {
        std::cout << "Parsed expression of type: " << expr->getType() << std::endl;
        // TODO: integrate with MaterialX Document
    }
}

// Scanner implementation
Scanner::Scanner(const std::string& source)
    : _source(source), _index(0), _line(1)
{
}

std::vector<std::string> Scanner::scan()
{
    std::vector<std::string> tokens;
    std::regex re(R"([\w\.]+|[^\s\w])");
    auto words_begin = std::sregex_iterator(_source.begin(), _source.end(), re);
    auto words_end = std::sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it)
    {
        tokens.push_back(it->str());
    }
    return tokens;
}

// Tokenize utility
std::vector<std::string> tokenize(const std::string& source)
{
    ScannerPtr scanner = Scanner::create(source);
    return scanner->scan();
}

MATERIALX_NAMESPACE_END
