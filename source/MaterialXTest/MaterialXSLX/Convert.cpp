//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXTest/External/Catch/catch.hpp>

#include <MaterialXFormat/Environ.h>
#include <MaterialXFormat/Util.h>
#include <MaterialXFormat/XmlIo.h>
#include <MaterialXSLX/SLXDecompiler.h>

#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

void printDiff(const std::string& actual, const std::string& expected)
{
    std::istringstream a(actual), e(expected);
    std::string aLine, eLine;
    int lineNum = 1;
    while (std::getline(a, aLine) && std::getline(e, eLine)) {
        if (aLine != eLine) {
            std::cerr << "Diff at line " << lineNum << ":\n";
            std::cerr << "  Actual:   " << aLine << "\n";
            std::cerr << "  Expected: " << eLine << "\n";
        }
        ++lineNum;
    }
    // Print remaining lines if any
    while (std::getline(a, aLine)) {
        std::cerr << "Extra actual line " << lineNum << ": " << aLine << "\n";
        ++lineNum;
    }
    while (std::getline(e, eLine)) {
        std::cerr << "Missing expected line " << lineNum << ": " << eLine << "\n";
        ++lineNum;
    }
}

namespace mx = MaterialX;

TEST_CASE("SLX Decompile", "[slx]")
{
    mx::FileSearchPath searchPath = mx::getDefaultDataSearchPath();
    mx::DocumentPtr libraries = mx::createDocument();
    mx::loadLibraries({ "libraries" }, searchPath, libraries);

    mx::FilePath examplesPath = searchPath.find("resources/Materials/Examples/StandardSurface");
    searchPath.append(examplesPath);

    // Serialize to SLX
    mx::SLXDecompiler decompiler;

    // Read and decompile each example document.
    for (const mx::FilePath& filename : examplesPath.getFilesInDirectory(mx::MTLX_EXTENSION))
    {
        mx::DocumentPtr doc = mx::createDocument();
        mx::readFromXmlFile(doc, filename, searchPath);
        doc->setDataLibrary(libraries);

        decompiler.setUseOutputArguments(false);
        std::string slxString = decompiler.decompile(doc);
        std::cerr << "--------------------------\n> Decompiled SLX for " << filename.asString() << "\n" << slxString;
        REQUIRE(!slxString.empty());

        decompiler.setUseOutputArguments(true);
        slxString = decompiler.decompile(doc);
        std::cerr << "--------------------------\n> Decompiled SLX w/ output args for " << filename.asString() << "\n" << slxString;
        REQUIRE(!slxString.empty());

    }
}

TEST_CASE("SLX Decompiler Reference Compare", "[slx]")
{
    mx::FileSearchPath searchPath = mx::getDefaultDataSearchPath();
    mx::FilePath slxFolder = searchPath.find("resources/slx");
    searchPath.append(slxFolder);

    // Decompile
    mx::SLXDecompiler decompiler;

    for (const mx::FilePath& filename : slxFolder.getFilesInDirectory(mx::MTLX_EXTENSION))
    {
        // Load MaterialX document
        std::cerr << "Read in file: " << filename.asString() << std::endl;
        mx::DocumentPtr doc = mx::createDocument();
        mx::readFromXmlFile(doc, filename, searchPath);

        std::string slxString = decompiler.decompile(doc);

        // Write file as _converted.slx for debugging
        mx::FilePath debugFileName = filename.getBaseName() + "_converted.mxsl";
        mx::FilePath debugFilePath = slxFolder / debugFileName;
        std::ofstream debugFile(debugFilePath);
        debugFile << slxString;
        debugFile.close();

        // Read reference SLX
        bool testReference = false;
        if (testReference)
        {
            mx::FilePath slxFileName = filename.getBaseName() + ".mxsl";
            mx::FilePath mxslPath = slxFolder / slxFileName;
            std::ifstream refFile(mxslPath);
            std::string refSLX((std::istreambuf_iterator<char>(refFile)), std::istreambuf_iterator<char>());

            // Compare and print diffs
            if (slxString != refSLX) {
                std::cerr << "\n==== Difference for " << filename.asString() << " ====" << std::endl;
                printDiff(slxString, refSLX);
            }
        }
    }
}
