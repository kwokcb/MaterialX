#ifndef MATERIALX_SHADINGNODE_IMPL_H
#define MATERIALX_SHADINGNODE_IMPL_H

#include <maya/MViewport2Renderer.h>

namespace MaterialXMaya
{

template <class BASE>
class MaterialXShadingNodeImpl : public BASE
{
  public:
    MHWRender::DrawAPI supportedDrawAPIs() const override
    {
        return MHWRender::kOpenGL | MHWRender::kOpenGLCoreProfile;
    }

    MString fragmentName() const override;

    void updateDG() override;

    void updateShader(
        MHWRender::MShaderInstance&,
        const MHWRender::MAttributeParameterMappingList&
    ) override;

    bool valueChangeRequiresFragmentRebuild(const MPlug*) const override;

  protected:
    ~MaterialXShadingNodeImpl() override;

    MaterialXShadingNodeImpl(const MObject&);

    MObject _object;
};

} // namespace MaterialXMaya

#endif /* MATERIALX_SHADINGNODE_IMPL_H */