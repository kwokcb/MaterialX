//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//
#include <MaterialXSLX/Wrapper.h>

MATERIALX_NAMESPACE_BEGIN

// MXInputWrapper implementation
MXInputWrapper::MXInputWrapper(MaterialX::InputPtr input) : _input(input) {}
std::string MXInputWrapper::getName() const { return _input ? _input->getName() : ""; }
std::string MXInputWrapper::getType() const { return _input ? _input->getType() : ""; }
bool MXInputWrapper::hasValue() const { return _input ? _input->hasValue() : false; }
std::string MXInputWrapper::getValueString() const { return _input ? _input->getValueString() : ""; }
MaterialX::NodePtr MXInputWrapper::getConnectedNode() const { return _input ? _input->getConnectedNode() : nullptr; }
MaterialX::InputPtr MXInputWrapper::getInput() const { return _input; }

// MXOutputWrapper implementation
MXOutputWrapper::MXOutputWrapper(MaterialX::OutputPtr output) : _output(output) {}
std::string MXOutputWrapper::getName() const { return _output ? _output->getName() : ""; }
std::string MXOutputWrapper::getType() const { return _output ? _output->getType() : ""; }
MaterialX::NodePtr MXOutputWrapper::getConnectedNode() const { return _output ? _output->getConnectedNode() : nullptr; }
MaterialX::OutputPtr MXOutputWrapper::getOutput() const { return _output; }

// MXNodeWrapper implementation
MXNodeWrapper::MXNodeWrapper(MaterialX::NodePtr node) : _node(node) {}
std::string MXNodeWrapper::getName() const { return _node ? _node->getName() : ""; }
std::string MXNodeWrapper::getType() const { return _node ? _node->getType() : ""; }
std::string MXNodeWrapper::getCategory() const { return _node ? _node->getCategory() : ""; }
std::vector<MXInputWrapperPtr> MXNodeWrapper::getInputs() const {
    std::vector<MXInputWrapperPtr> result;
    if (_node) {
        for (const auto& input : _node->getInputs()) {
            result.push_back(std::make_shared<MXInputWrapper>(input));
        }
    }
    return result;
}
std::vector<MXOutputWrapperPtr> MXNodeWrapper::getOutputs() const {
    std::vector<MXOutputWrapperPtr> result;
    if (_node) {
        for (const auto& output : _node->getOutputs()) {
            result.push_back(std::make_shared<MXOutputWrapper>(output));
        }
    }
    return result;
}
MaterialX::NodePtr MXNodeWrapper::getNode() const { return _node; }

// MXDocumentWrapper implementation
MXDocumentWrapper::MXDocumentWrapper(MaterialX::DocumentPtr doc) : _doc(doc) {}
std::vector<MXNodeWrapperPtr> MXDocumentWrapper::getNodes() const {
    std::vector<MXNodeWrapperPtr> result;
    if (_doc) {
        for (const auto& node : _doc->getNodes()) {
            result.push_back(std::make_shared<MXNodeWrapper>(node));
        }
    }
    return result;
}
MaterialX::DocumentPtr MXDocumentWrapper::getDocument() const { return _doc; }

MATERIALX_NAMESPACE_END
