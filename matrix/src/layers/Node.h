#ifndef NODE_HPP
#define NODE_HPP

#include <Transform.h>

#include <Shader.h>
#include <Model.h>
#include <Assimp_Model.h>
#include <Texture.h>
#include <Shader_OpenGL.h>
#include <Texture_OpenGL.h>

namespace MX
{
  class Node
  {
  public:
    Node() = delete;
    Node(const std::string &node_name, std::shared_ptr<Assimp_Model> model = nullptr, std::shared_ptr<MX_SHADER> shader = nullptr, std::shared_ptr<MX_TEXTURE> texture = nullptr);
    ~Node() = default;

    Node(const Node&) = default;
    Node &operator=(const Node&) = default;
    
    void addChild(std::shared_ptr<Node> node);
    std::shared_ptr<Node> getChild(const std::string &name);

    void setParent(std::shared_ptr<Node> node);

    void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));

    MX_API void setModel(std::shared_ptr<Assimp_Model> model);
    MX_API void setShader(std::shared_ptr<MX_SHADER> shader);
    MX_API void setTexture(std::shared_ptr<MX_TEXTURE> texture);
  
    MX_API void setTransform(const Trans &t, float factor, bool is_animated);

    glm::fmat4 &getLocalTransform() { return m_Trans.m_local; }
    glm::fmat4 &getWorldTransform() { return m_Trans.m_world; }

    void toString();

  public:
    std::string m_Name;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Texture> m_Texture;
    std::shared_ptr<Assimp_Model> m_Model;

    std::shared_ptr<Node> m_Parent;
    std::list<std::shared_ptr<Node>> m_Children;

    Transform m_Trans;
    bool m_visible;
  };
}

#endif // NODE_HPP