

//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXSLX/SLXCompiler.h>
#include <MaterialXSLX/SLXUtil.h>
#include <MaterialXCore/Document.h>

MATERIALX_NAMESPACE_BEGIN

/// @brief Constructor for SLXCompiler.
SLXCompiler::SLXCompiler() {}

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
    // Example: Tokenize SLX source and build MaterialX Document
    auto tokens = tokenize(slxSource);
    DocumentPtr doc = createDocument();
    // Use the cached standard library if set
    if (_standardLibrary)
    {
        // TODO: Merge or reference the standard library as needed
    }
    // Parse tokens and populate the document
    SLXParser parser(tokens);
    parser.parse(doc);
    return doc;
}

MATERIALX_NAMESPACE_END
