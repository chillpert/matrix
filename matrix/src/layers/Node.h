#ifndef NODE_HPP
#define NODE_HPP

#include <Transform.h>

#include <Shader.h>
#include <Model.h>
#include <Texture.h>
#include <Shader_OpenGL.h>
#include <Texture_OpenGL.h>

namespace MX
{
  class Node
  {
  public:
    MX_API Node() = delete;
    MX_API Node(const std::string &node_name, std::shared_ptr<MX_SHADER> shader = nullptr);
    MX_API virtual ~Node() = default;

    MX_API Node(const Node&) = default;
    MX_API Node &operator=(const Node&) = default;

    MX_API virtual void upload_uniforms();
    
    MX_API virtual void addChild(std::shared_ptr<Node> node);
    MX_API virtual std::shared_ptr<Node> getChild(const std::string &name);

    MX_API virtual void setParent(std::shared_ptr<Node> node);

    MX_API void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    MX_API void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));

    MX_API virtual void setShader(std::shared_ptr<Shader> shader);

    MX_API void setTransform(const Trans &t, float factor, bool is_animated);

    MX_API glm::fmat4 &getLocalTransform() { return m_Trans.m_local; }
    MX_API glm::fmat4 &getWorldTransform() { return m_Trans.m_world; }

  public:
    std::string m_Name;

    std::shared_ptr<Shader> m_Shader;

    std::shared_ptr<Node> m_Parent;
    std::list<std::shared_ptr<Node>> m_Children;

    Transform m_Trans;
    bool m_visible;
  };
}

#endif // NODE_HPP