#include "matrix/src/layers/Node.h"

namespace MX
{
  Node::Node(const std::string &node_name, std::shared_ptr<MX_MODEL> model, std::shared_ptr<MX_SHADER> shader, std::shared_ptr<MX_TEXTURE> texture)
    : m_Name(node_name), m_Model(model), m_Shader(shader), m_Texture(texture) { }

  void Node::addChild(std::shared_ptr<Node> node)
  {
    node->setParent(std::shared_ptr<Node>(this));
    m_Children.emplace_back(node);
    MX_INFO_LOG("MX: Node: " + node->m_Name + " added to parent: " + this->m_Name);
  }

  void Node::setParent(std::shared_ptr<Node> node)
  {
    if (m_Parent == nullptr)
      m_Parent = node;
    else
    {
      std::list<std::shared_ptr<Node>>::iterator iter;
      std::shared_ptr<Node> old_parent = m_Parent;
      for (iter = old_parent->m_Children.begin(); iter != old_parent->m_Children.end(); ++iter)
      {
        if ((*iter)->m_Name == this->m_Name)
        {
          old_parent->m_Children.erase(iter);
          break;
        }
      }

      node->m_Children.push_back(std::shared_ptr<Node>(this));
      m_Parent = node;
    }
  }

  std::shared_ptr<Node> Node::getChild(const std::string &name)
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
    m_Trans.m_Local = mat * m_Trans.m_Local;
  }

  void Node::setWorldTransform(const glm::fmat4& mat)
  {
    m_Trans.m_World = mat * m_Trans.update();
  }

  void Node::setTransform(const Trans &t, float factor, bool isAnimated)
  {
    m_Trans.push(t, factor, isAnimated);
  }

  void Node::setModel(std::shared_ptr<MX_MODEL> model)
  {    
    m_Model = model;
  }

  void Node::setShader(std::shared_ptr<MX_SHADER> shader)
  {
    m_Shader = shader;
  }

  void Node::setTexture(std::shared_ptr<MX_TEXTURE> texture)
  {
    m_Texture = texture;
  }
}