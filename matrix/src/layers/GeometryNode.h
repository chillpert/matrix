#ifndef GeometryNode_H
#define GeometryNode_H

#include <Node.h>

namespace MX
{
  class GeometryNode;

  typedef GeometryNode* MX_GeometryNode;

  class GeometryNode : public Node
  {
  public:
    MX_API GeometryNode() = delete;
    MX_API GeometryNode(const std::string &name);
    MX_API virtual ~GeometryNode() = default;

    MX_API GeometryNode(const GeometryNode&) = default;
    MX_API GeometryNode &operator=(const GeometryNode&) = default;

    MX_API GeometryNode *getNode() { return this; }

    MX_API std::string getIdentifier() { return "Geometry"; }

    MX_API virtual void upload_uniforms();

    MX_API virtual void setTextureProfile(std::shared_ptr<TextureProfile> texture);
    MX_API virtual void setMaterialProfile(const MaterialProfile &material);
    MX_API virtual void setDiffuseTexture(std::shared_ptr<Texture> diffuse);
    MX_API virtual void setNormalTexture(std::shared_ptr<Texture> normal);
    MX_API virtual void setBumpTexture(std::shared_ptr<Texture> bump);
    MX_API virtual void setHeightTexture(std::shared_ptr<Texture> height);

    MX_API virtual void setModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> m_Model = nullptr;
    std::shared_ptr<TextureProfile> m_textures;
    MaterialProfile m_material;
  };
}

#endif // GeometryNode_H