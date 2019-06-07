#ifndef NODE_HPP
#define NODE_HPP

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/api/Shader.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
#endif

namespace MX
{
  class Node 
  {
  public:
    Node(const std::string &node_name, MX_MODEL *model, MX_SHADER *shader);
    Node(const std::string &node_name);
    ~Node();
    
    void addChild(Node* node); 
    Node* &getChild(const std::string &name);
    std::list<Node*> &getChildren() { return m_Children; }

    void setParent(Node* node);
    Node* &getParent() { return m_Parent; }

    void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));

    glm::fmat4 &getLocalTransform() { return m_LocalTransform; }
    glm::fmat4 &getWorldTransform() { return m_WorldTransform; }

    void toString();

  private:
    glm::fmat4 m_LocalTransform = glm::fmat4(1.0f);
    glm::fmat4 m_WorldTransform = glm::fmat4(1.0f);

    Node *m_Parent;
    std::list<Node*> m_Children;

  public:
    std::string m_Name;
    MX_MODEL *m_Model;
    MX_SHADER *m_Shader;
  };
}

#endif // NODE_HPP