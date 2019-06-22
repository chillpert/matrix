#ifndef OBJECTNODE_H
#define OBJECTNODE_H

#include <Node.h>

namespace MX
{
  class ObjectNode : public Node
  {
  public:
    MX_API ObjectNode() = delete;
    MX_API ObjectNode(const std::string &name);
    MX_API virtual ~ObjectNode() = default;

    MX_API ObjectNode(const ObjectNode&) = default;
    MX_API ObjectNode &operator=(const ObjectNode&) = default;

    MX_API virtual void upload_uniforms();

    MX_API virtual void setTextureProfile(std::shared_ptr<TextureProfile> texture);
    MX_API virtual void setDiffuseTexture(std::shared_ptr<Texture> diffuse);
    MX_API virtual void setNormalTexture(std::shared_ptr<Texture> normal);
    MX_API virtual void setBumpTexture(std::shared_ptr<Texture> bump);
    MX_API virtual void setHeightTexture(std::shared_ptr<Texture> height);

    MX_API virtual void setModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> m_Model = nullptr;
    std::shared_ptr<TextureProfile> m_textures = std::make_shared<TextureProfile>();
  };
}

#endif // OBJECTNODE_H