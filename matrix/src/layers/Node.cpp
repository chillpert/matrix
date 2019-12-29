#include "Node.h"

#include "Application.h"

namespace MX
{
  Node::Node(const std::string &node_name, std::shared_ptr<MX_SHADER> shader)
    : m_Name(node_name), m_Shader(shader), m_visible(true), m_type(NodeType::type_node) { }

  Node::Node(const std::string &node_name, const NodeType& type, std::shared_ptr<MX_SHADER> shader)
    : m_Name(node_name), m_Shader(shader), m_visible(true), m_type(type) { }

  void Node::upload_uniforms()
  {
    m_Shader->use();
    m_Shader->setfMat4("model", m_Trans.m_world);
    m_Shader->setfMat4("view", MX_CAMERA.getViewMatrix());
    m_Shader->setfMat4("projection", MX_CAMERA.getProjectionMatrix());
    m_Shader->setfVec3("viewPosition", MX_CAMERA.m_Position);
  }

  void Node::addChild(std::shared_ptr<Node> node)
  {
    m_Children.push_back(node);

    // the following line causes the segmentation fault
    node->setParent(this);
    //node->m_Parent = this;

    MX_INFO_LOG("MX: Node: " + node->m_Name + " added to parent: " + this->m_Name);
  }

  void Node::setParent(Node *node)
  {
    if (m_Parent == nullptr)
      m_Parent = node;
    else
    {
      Node *old_parent = m_Parent;

      node->m_Children.push_back(std::shared_ptr<Node>(this));
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

  std::string Node::to_string() const
  {
    std::stringstream ss;
    ss << "\nNode\n@Name{" << m_Name << "} ";
    
    if (m_Shader != nullptr)
      ss << "\n@Shader{" << m_Shader->m_Name << "} ";

    if (m_Parent != nullptr)
      ss << "\n@Parent{" << m_Parent->m_Name << "} ";

    if (!m_Children.empty())
    {
      ss << "\n@Children{";
      for (const std::shared_ptr<Node> it : m_Children)
        ss << "{" << it->m_Name << "}";
      ss << "} ";
    }

    ss << "\n@Transform{T{"  << glm::to_string(m_Trans.m_translation) << 
                    "} R{" << glm::to_string(m_Trans.m_rotation) << 
                    "} S{" << glm::to_string(m_Trans.m_scale) << "}} ";

    ss << "\n@Visible{" << std::to_string(m_visible) << "} ";

    std::string type = "type_node";
    switch (m_type)
    {
      case type_node:
      {
        type = "type_node";
        break;
      }
      case type_geometry:
      {
        type = "type_geometry";
        break;
      }
      case type_container:
      {
        type = "type_container";
        break;
      }
      case type_light:
      {
        type = "type_light";
        break;
      }
      case type_directionalLight:
      {
        type = "type_directionalLight";
        break;
      }
      case type_spotLight:
      {
        type = "type_spotLight";
        break;
      }
      case type_pointLight:
      {
        type = "type_pointLight";
        break;
      }
    }

    ss << "\n@Type{" << type << "}\n";

    return ss.str();
  }

  std::ostream& operator<<(std::ostream& os, std::shared_ptr<Node> node)
  {
    os << node->to_string();
    return os;
  }
}