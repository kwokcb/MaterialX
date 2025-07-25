//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#ifndef MATERIALX_OSLSHADERGENERATOR_H
#define MATERIALX_OSLSHADERGENERATOR_H

/// @file
/// OSL shading language generator

#include <MaterialXGenOsl/Export.h>

#include <MaterialXGenShader/ShaderGenerator.h>

MATERIALX_NAMESPACE_BEGIN

using OslShaderGeneratorPtr = shared_ptr<class OslShaderGenerator>;

/// @class OslShaderGenerator
/// Base class for OSL (Open Shading Language) shader generators.
/// A generator for a specific OSL target should be derived from this class.
class MX_GENOSL_API OslShaderGenerator : public ShaderGenerator
{
  public:
    /// Constructor.
    OslShaderGenerator(TypeSystemPtr typeSystem);

    /// Creator function.
    /// If a TypeSystem is not provided it will be created internally.
    /// Optionally pass in an externally created TypeSystem here, 
    /// if you want to keep type descriptions alive after the lifetime
    /// of the shader generator. 
    static ShaderGeneratorPtr create(TypeSystemPtr typeSystem = nullptr)
    {
        return std::make_shared<OslShaderGenerator>(typeSystem ? typeSystem : TypeSystem::create());
    }

    /// Return a unique identifier for the target this generator is for
    const string& getTarget() const override { return TARGET; }

    /// Generate a shader starting from the given element, translating
    /// the element and all dependencies upstream into shader code.
    ShaderPtr generate(const string& name, ElementPtr element, GenContext& context) const override;

    /// Add all function calls for a node, and all upstream nodes.
    void emitAllDependentFunctionCalls(const ShaderNode& node, GenContext& context, ShaderStage& stage) const;

    /// Unique identifier for this generator target
    static const string TARGET;

    /// Register metadata that should be exported to the generated shaders.
    void registerShaderMetadata(const DocumentPtr& doc, GenContext& context) const override;

  protected:
    /// Create and initialize a new OSL shader for shader generation.
    virtual ShaderPtr createShader(const string& name, ElementPtr element, GenContext& context) const;

    /// Emit include headers needed by the generated shader code.
    virtual void emitLibraryIncludes(ShaderStage& stage, GenContext& context) const;

    /// Emit a block of shader inputs.
    virtual void emitShaderInputs(const VariableBlock& inputs, ShaderStage& stage) const;

    /// Emit a block of shader outputs.
    virtual void emitShaderOutputs(const VariableBlock& inputs, ShaderStage& stage) const;

    /// Emit metadata for a shader parameter.
    virtual void emitMetadata(const ShaderPort* port, ShaderStage& stage) const;
};

namespace OSL
{

/// Identifiers for OSL variable blocks
extern MX_GENOSL_API const string UNIFORMS;
extern MX_GENOSL_API const string INPUTS;
extern MX_GENOSL_API const string OUTPUTS;

} // namespace OSL

MATERIALX_NAMESPACE_END

#endif
