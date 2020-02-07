//
// TM & (c) 2019 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#include <MaterialXRuntime/RtNodeGraph.h>
#include <MaterialXRuntime/RtPrim.h>
#include <MaterialXRuntime/RtNode.h>

#include <MaterialXRuntime/Private/PvtPrim.h>

namespace MaterialX
{

namespace
{
    static const RtToken SOCKET("socket");
    static const RtToken NODEGRAPH1("nodegraph1");
}

DEFINE_TYPED_SCHEMA(RtNodeGraph, "nodegraph");

RtPrim RtNodeGraph::createPrim(const RtToken& typeName, const RtToken& name, RtPrim parent)
{
    if (typeName != _typeName)
    {
        throw ExceptionRuntimeError("Type names mismatch when creating prim '" + name.str() + "'");
    }

    const RtToken primName = name == EMPTY_TOKEN ? NODEGRAPH1 : name;
    PvtDataHandle primH = PvtPrim::createNew(primName, PvtObject::ptr<PvtPrim>(parent));

    PvtPrim* prim = primH->asA<PvtPrim>();
    prim->setTypeName(_typeName);

    // Add a child prim to hold the internal sockets.
    PvtDataHandle socketH = PvtPrim::createNew(SOCKET, prim);
    prim->addChildPrim(socketH->asA<PvtPrim>());

    return primH;
}

RtInput RtNodeGraph::createInput(const RtToken& name, const RtToken& type, uint32_t flags)
{
    PvtPrim* socket = prim()->getChild(SOCKET);
    socket->createOutput(name, type, flags | RtAttrFlag::SOCKET);
    return prim()->createInput(name, type, flags)->hnd();
}

void RtNodeGraph::removeInput(const RtToken& name)
{
    PvtInput* input = prim()->getInput(name);
    if (!(input && input->isA<PvtInput>()))
    {
        throw ExceptionRuntimeError("No input found with name '" + name.str() + "'");
    }
    PvtPrim* socket = prim()->getChild(SOCKET);
    socket->removeAttribute(name);
    prim()->removeAttribute(name);
}

RtOutput RtNodeGraph::createOutput(const RtToken& name, const RtToken& type, uint32_t flags)
{
    PvtPrim* socket = prim()->getChild(SOCKET);
    socket->createInput(name, type, flags | RtAttrFlag::SOCKET);
    return prim()->createOutput(name, type, flags)->hnd();
}

void RtNodeGraph::removeOutput(const RtToken& name)
{
    PvtOutput* output = prim()->getOutput(name);
    if (!(output && output->isA<PvtOutput>()))
    {
        throw ExceptionRuntimeError("No output found with name '" + name.str() + "'");
    }
    PvtPrim* socket = prim()->getChild(SOCKET);
    socket->removeAttribute(name);
    prim()->removeAttribute(name);
}

RtInput RtNodeGraph::getInput(const RtToken& name) const
{
    PvtInput* input = prim()->getInput(name);
    return input ? input->hnd() : RtInput();
}

RtAttrIterator RtNodeGraph::getInputs() const
{
    RtObjTypePredicate<RtInput> filter;
    return RtAttrIterator(getPrim(), filter);
}

RtOutput RtNodeGraph::getOutput(const RtToken& name) const
{
    PvtOutput* output = prim()->getOutput(name);
    return output ? output->hnd() : RtOutput();
}

RtAttrIterator RtNodeGraph::getOutputs() const
{
    RtObjTypePredicate<RtOutput> filter;
    return RtAttrIterator(getPrim(), filter);
}

RtOutput RtNodeGraph::getInputSocket(const RtToken& name) const
{
    PvtPrim* socket = prim()->getChild(SOCKET);
    // Input socket is an output in practice.
    PvtOutput* output = socket->getOutput(name);
    return output ? output->hnd() : RtOutput();
}

RtInput RtNodeGraph::getOutputSocket(const RtToken& name) const
{
    PvtPrim* socket = prim()->getChild(SOCKET);
    // Output socket is an input in practice.
    PvtInput* input = socket->getInput(name);
    return input ? input->hnd() : RtInput();
}

RtPrim RtNodeGraph::getNode(const RtToken& name) const
{
    PvtPrim* p = prim()->getChild(name);
    return p && p->getTypeName() == RtNode::typeName() ? p->hnd() : RtPrim();
}

RtPrimIterator RtNodeGraph::getNodes() const
{
    RtSchemaPredicate<RtNode> predicate;
    return RtPrimIterator(hnd(), predicate);
}

string RtNodeGraph::asStringDot() const
{
    string dot = "digraph {\n";

    // Add input/output interface boxes.
    dot += "    \"inputs\" ";
    dot += "[shape=box];\n";
    dot += "    \"outputs\" ";
    dot += "[shape=box];\n";


    RtObjTypePredicate<RtInput> inputFilter;

    // Add all nodes.
    for (const RtPrim prim : getNodes())
    {
        dot += "    \"" + prim.getName().str() + "\" ";
        dot += "[shape=ellipse];\n";
    }

    // Add connections inbetween nodes
    // and between nodes and input interface.
    for (const RtPrim node : getNodes())
    {
        const string dstName = node.getName().str();
        for (const RtObject inputObj : node.getAttributes(inputFilter))
        {
            const RtInput& input = static_cast<const RtInput&>(inputObj);
            if (input.isConnected())
            {
                const RtOutput src = input.getConnection();
                const string srcName = src.isSocket() ? "inputs" : src.getParent().getName().str();
                dot += "    \"" + srcName;
                dot += "\" -> \"" + dstName;
                dot += "\" [label=\"" + input.getName().str() + "\"];\n";
            }
        }
    }

    PvtPrim* sockets = prim()->getChild(SOCKET);

    // Add connections between nodes and output sockets.
    for (RtObject socketObj : sockets->getAttributes(inputFilter))
    {
        const RtInput& socket = static_cast<const RtInput&>(socketObj);
        if (socket.isConnected())
        {
            const RtOutput src = socket.getConnection();
            const string srcName = src.isSocket() ? "inputs" : src.getParent().getName().str();
            dot += "    \"" + srcName;
            dot += "\" -> \"outputs";
            dot += "\" [label=\"" + socket.getName().str() + "\"];\n";
        }
    }

    dot += "}\n";

    return dot;
}

}