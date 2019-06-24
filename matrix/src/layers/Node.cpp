#include <Node.h>

#include <Application.h>

namespace MX
{
  Node::Node(const std::string &node_name, std::shared_ptr<MX_SHADER> shader)
    : m_Name(node_name), m_Shader(shader), m_visible(true) { }

  void Node::upload_uniforms()
  {
    m_Shader->use();
    m_Shader->setfMat4("model", getWorldTransform());
    m_Shader->setfMat4("view", MX_CAMERA.getViewMatrix());
    m_Shader->setfMat4("projection", MX_CAMERA.getProjectionMatrix());
    m_Shader->setfVec3("viewPosition", MX_CAMERA.m_Position);
  }

  void Node::addChild(std::shared_ptr<Node> node)
  {
    node->setParent(std::shared_ptr<Node>(this));;
    m_Children.push_back(node);
    MX_INFO_LOG("MX: Node: " + node->m_Name + " added to parent: " + this->m_Name);
  }

  void Node::setParent(std::shared_ptr<Node> node)
  {
    if (m_Parent == nullptr)
      m_Parent = node;
    else
    {
      
      std::shared_ptr<Node> old_parent = m_Parent;

      node->m_Children.push_back(std::move(std::make_shared<Node>(Node(*this))));
      m_Parent = node;

      std::list<std::shared_ptr<Node>>::iterator iter;
      for (iter = old_parent->m_Children.begin(); iter != old_parent->m_Children.end(); ++iter)
      {
        if ((*iter)->m_Name == this->m_Name)
        {
          old_parent->m_Children.erase(iter);
          break;
        }
      }
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
    throw mx_entity_not_found(name);
  }

  void Node::setLocalTransform(const glm::fmat4& mat)
  {
    m_Trans.m_local = mat * m_Trans.m_local;
  }

  void Node::setWorldTransform(const glm::fmat4& mat)
  {
    m_Trans.m_world = mat * m_Trans.update();
  }

  void Node::setTransform(const Trans &t, float factor, bool is_animated)
  {
    m_Trans.push(t, factor, is_animated);
  }

  void Node::setShader(std::shared_ptr<Shader> shader)
  {
    if (shader != nullptr)
    {
      if (!shader->m_initialized)
        shader->initialize();

      m_Shader = shader;
    }
    else
      m_Shader = nullptr;
  }
}