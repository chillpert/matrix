#ifndef NODE_HPP
#define NODE_HPP

#include "matrix/src/layers/Transform.h"

#include "matrix/src/platform/api/Shader.h"
#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Texture.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
  #include "matrix/src/platform/api/Texture_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
  #include "matrix/src/platform/api/Texture_DirectX.h"
#endif

namespace MX
{
  class Node
  {
  public:
    Node(const std::string &node_name, std::shared_ptr<MX_MODEL> model = nullptr, std::shared_ptr<MX_SHADER> shader = nullptr, std::shared_ptr<MX_TEXTURE> texture = nullptr);
    ~Node() = default;

    Node(const Node&) = default;
    Node &operator=(const Node&) = default;
    
    void addChild(Node* node);
    Node* &getChild(const std::string &name);
    std::list<Node*> &getChildren() { return m_Children; }

    void setParent(Node* node);
    Node* &getParent() { return m_Parent; }

    void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));

    MX_API void setModel(std::shared_ptr<MX_MODEL> model);
    MX_API void setShader(std::shared_ptr<MX_SHADER> shader);
    MX_API void setTexture(std::shared_ptr<MX_TEXTURE> texture);

    MX_API void setTransform(const Trans &t, float factor, bool isAnimated);

    glm::fmat4 &getLocalTransform() { return m_Trans.m_Local; }
    glm::fmat4 &getWorldTransform() { return m_Trans.m_World; }

    void toString();

  private:
    Node *m_Parent;
    std::list<Node*> m_Children;

    Transform m_Trans;

  public:
    std::string m_Name;
    std::shared_ptr<Model> m_Model;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Texture> m_Texture;
  };
}

#endif // NODE_HPP