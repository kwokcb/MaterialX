// SLXParser.h
// SLX source parser for SLXCompiler
#pragma once
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <MaterialXSLX/SLXAST.h>


MATERIALX_NAMESPACE_BEGIN

enum class SLXTokenType {
    Identifier, Keyword, IntLiteral, FloatLiteral, StringLiteral, Symbol, EndOfFile
    // Add more as needed
};

struct SLXToken {
    SLXTokenType type;
    std::string text;
    size_t position;
};

class SLXTokenReader {
public:
    SLXTokenReader(const std::vector<SLXToken>& tokens) : _tokens(tokens), _pos(0) {}
    const SLXToken& peek(size_t offset = 0) const {
        size_t idx = _pos + offset;
        if (idx < _tokens.size()) return _tokens[idx];
        static SLXToken eof{SLXTokenType::EndOfFile, "", 0};
        return eof;
    }
    const SLXToken& consume() { return _tokens[_pos++]; }
    bool match(SLXTokenType type, const std::string& value = "") {
        if (_pos < _tokens.size() && _tokens[_pos].type == type &&
            (value.empty() || _tokens[_pos].text == value)) {
            ++_pos;
            return true;
        }
        return false;
    }
    bool atEnd() const { return _pos >= _tokens.size(); }
private:
    std::vector<SLXToken> _tokens;
    size_t _pos;
};

class SLXParser {
public:
    SLXParser();
    ~SLXParser();

    std::vector<SLXStatementASTPtr> parse(const std::string& slxSource);

private:
    std::vector<SLXToken> tokenize(const std::string& source);
    SLXStatementASTPtr parseStatement(SLXTokenReader& reader);
    SLXExpressionASTPtr parseExpression(SLXTokenReader& reader);
    // Parsing helpers matching Python logic
    std::vector<std::string> parseAttributes(SLXTokenReader& reader);
    SLXStatementASTPtr parseVariableDeclaration(SLXTokenReader& reader);
    SLXStatementASTPtr parseFunctionDeclaration(SLXTokenReader& reader);
    SLXStatementASTPtr parseAssignment(SLXTokenReader& reader);
    SLXStatementASTPtr parseForLoop(SLXTokenReader& reader);
    SLXStatementASTPtr parseInline(SLXTokenReader& reader);
    SLXStatementASTPtr parseError(SLXTokenReader& reader);
    // Add more parsing helpers for arguments, attributes, modifiers, etc.
};

MATERIALX_NAMESPACE_END