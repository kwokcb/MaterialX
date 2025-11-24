//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

/// @file
/// MaterialX wrapper classes for node, input, output, document abstraction

#include <MaterialXCore/Document.h>
#include <MaterialXCore/Node.h>
//#include <MaterialXCore/Input.h>
//#include <MaterialXCore/Output.h>
#include <MaterialXCore/Value.h>
#include <memory>
#include <string>
#include <vector>

MATERIALX_NAMESPACE_BEGIN

class MXNodeWrapper;
class MXInputWrapper;
class MXOutputWrapper;
class MXDocumentWrapper;

using MXNodeWrapperPtr = std::shared_ptr<MXNodeWrapper>;
using MXInputWrapperPtr = std::shared_ptr<MXInputWrapper>;
using MXOutputWrapperPtr = std::shared_ptr<MXOutputWrapper>;
using MXDocumentWrapperPtr = std::shared_ptr<MXDocumentWrapper>;

class MXInputWrapper {
public:
    MXInputWrapper(MaterialX::InputPtr input);
    std::string getName() const;
    std::string getType() const;
    bool hasValue() const;
    std::string getValueString() const;
    MaterialX::NodePtr getConnectedNode() const;
    MaterialX::InputPtr getInput() const;
private:
    MaterialX::InputPtr _input;
};

class MXOutputWrapper {
public:
    MXOutputWrapper(MaterialX::OutputPtr output);
    std::string getName() const;
    std::string getType() const;
    MaterialX::NodePtr getConnectedNode() const;
    MaterialX::OutputPtr getOutput() const;
private:
    MaterialX::OutputPtr _output;
};

class MXNodeWrapper {
public:
    MXNodeWrapper(MaterialX::NodePtr node);
    std::string getName() const;
    std::string getType() const;
    std::string getCategory() const;
    std::vector<MXInputWrapperPtr> getInputs() const;
    std::vector<MXOutputWrapperPtr> getOutputs() const;
    MaterialX::NodePtr getNode() const;
private:
    MaterialX::NodePtr _node;
};

class MXDocumentWrapper {
public:
    MXDocumentWrapper(MaterialX::DocumentPtr doc);
    std::vector<MXNodeWrapperPtr> getNodes() const;
    MaterialX::DocumentPtr getDocument() const;
private:
    MaterialX::DocumentPtr _doc;
};

MATERIALX_NAMESPACE_END
