//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

/// @file
/// Utility functions for SLX <-> MaterialX conversion

#include <MaterialXCore/Util.h>
#include <MaterialXCore/Document.h>
#include <MaterialXSLX/SLXExpression.h>
#include <MaterialXSLX/Argument.h>

MATERIALX_NAMESPACE_BEGIN

class Scanner;
using ScannerPtr = std::shared_ptr<Scanner>;

class SLXParser;
using SLXParserPtr = std::shared_ptr<SLXParser>;


/// @brief Tokenize SLX source code into a vector of strings.
/// @param source The SLX source code as a string.
/// @return A vector of tokens as strings.
std::vector<std::string> tokenize(const std::string& source);

/// @class Scanner
/// @brief Scans SLX source code and produces tokens.
class Scanner
{
public:
    Scanner(const std::string& source);
    static ScannerPtr create(const std::string& source)
    {
        return ScannerPtr(new Scanner(source));
    }
    std::vector<std::string> scan();
private:
    std::string _source;
    size_t _index;
    int _line;
    // Add more members as needed
};

/// @class SLXParser
/// @brief Parses SLX tokens into statements (AST) and builds a MaterialX Document.


class SLXParser
{
public:
    /// @brief Construct a parser with a vector of tokens.
    SLXParser(const std::vector<std::string>& tokens);
    static SLXParserPtr create(const std::vector<std::string>& tokens)
    {
        return SLXParserPtr(new SLXParser(tokens));
    }

    /// @brief Parse the tokens and build a MaterialX Document.
    /// @param doc The MaterialX Document to populate.
    void parse(MaterialX::DocumentPtr doc);

private:
    std::vector<std::string> _tokens;
    size_t _pos;

    // Parsing helpers
    bool atEnd() const;
    std::string peek() const;
    std::string advance();

    // Parsing routines (mirroring Python methods)
    void parseProgram(MaterialX::DocumentPtr doc);
    void parseStatement(MaterialX::DocumentPtr doc);
    // Expression parsing
    SLXExpressionPtr parseExpression();
    // ... more as needed
};

MATERIALX_NAMESPACE_END
