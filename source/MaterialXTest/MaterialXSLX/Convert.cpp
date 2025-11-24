//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXTest/External/Catch/catch.hpp>

#include <MaterialXFormat/Environ.h>
#include <MaterialXFormat/Util.h>
#include <MaterialXFormat/XmlIo.h>
#include <MaterialXSLX/SLXDecompiler.h>

#include <iostream>

namespace mx = MaterialX;

TEST_CASE("SLX Decompile", "[slx]")
{
    mx::FileSearchPath searchPath = mx::getDefaultDataSearchPath();
    mx::DocumentPtr libraries = mx::createDocument();
    mx::loadLibraries({ "libraries" }, searchPath, libraries);

    mx::FilePath examplesPath = searchPath.find("resources/Materials/Examples/StandardSurface");
    searchPath.append(examplesPath);

    // Read and decompile each example document.
    for (const mx::FilePath& filename : examplesPath.getFilesInDirectory(mx::MTLX_EXTENSION))
    {
        mx::DocumentPtr doc = mx::createDocument();
        mx::readFromXmlFile(doc, filename, searchPath);
        doc->setDataLibrary(libraries);

        // Serialize to SLX
        mx::SLXDecompiler decompiler;
        std::string slxString = decompiler.decompile(doc);
        // Output test INFO
        std::cerr << "--------------------------\n> Decompiled SLX for " << filename.asString() << "\n" << slxString;
        REQUIRE(!slxString.empty());
    }
}
