#include "matrix/src/layers/Node.h"

namespace MX
{
  Node::Node(const std::string &node_name, MX_MODEL *model, MX_SHADER *shader)
    : m_Name(node_name), m_Shader(shader), m_Model(model) { }

  Node::Node(const std::string &node_name)
    : m_Name(node_name)
  {
    m_Shader = nullptr;
    m_Model = nullptr;
  }

  Node::~Node()
  {
    m_Model = nullptr;
  }

  void Node::addChild(Node* node)
  {
    node->setParent(this);
    m_Children.emplace_back(node);
    MX_INFO_LOG("MX: Node: " + node->m_Name + " added to parent: " + this->m_Name);
  }

  void Node::setParent(Node* node)
  {
    m_Parent = node;
  }

  // always catch this function
  Node* &Node::getChild(const std::string &name)
  {
    for (auto &it : m_Children)
    {
      if (it->m_Name == name)
        return it;
    }

    MX_FATAL("MX: Node: Get Child: " + name + " is not a child of " + m_Name);
    throw std::exception();
  }

  void Node::setLocalTransform(const glm::fmat4& mat)
  {
    m_LocalTransform = mat * m_LocalTransform;
  }

  void Node::setWorldTransform(const glm::fmat4& mat)
  {
    glm::fmat4 trans = glm::fmat4(1.0f);
    // apply transformation in here
    m_WorldTransform = mat * m_LocalTransform * trans;
  }

}