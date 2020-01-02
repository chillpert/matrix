#include "Node.h"

#include "Application.h"

namespace MX
{
  Node::Node(const std::string &node_name, std::shared_ptr<MX_SHADER> shader)
    : m_Name(node_name), m_Shader(shader), m_visible(true), m_type(NodeType::type_node) { }

  Node::Node(const std::string &node_name, const NodeType& type, std::shared_ptr<MX_SHADER> shader)
    : m_Name(node_name), m_Shader(shader), m_visible(true), m_type(type) { }

  Node::~Node()
  {
    MX_WARN("MX: Node: Destroyed Node: " + m_Name);
  }

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
    if (node != nullptr)
    {
      if (node->m_Parent != nullptr)
      {
        // if new child has a parent, remove new child from parent's children list
        std::list<std::shared_ptr<Node>>::iterator iter;
        for (iter = node->m_Parent->m_Children.begin(); iter != node->m_Parent->m_Children.end(); ++iter)
        {
          if ((*iter)->m_Name == node->m_Name)
          {
            node->m_Parent->m_Children.erase(iter);
            break;
          }
        }
      }

      node->m_Parent = this;
      m_Children.push_back(node);

      MX_INFO_LOG("MX: Node: " + node->m_Name + " added to parent: " + this->m_Name);
    }

  }

  void Node::setParent(Node *node)
  {
    // if this node is the root, return because the root must not have a parent
    if (m_Name == default_root_name)
    {
      MX_WARN("MX: Node: Root Node must not have a parent");
      return;
    }

    if (node != nullptr)
    {
      // delete this node from its parent's children list
      if (m_Parent != nullptr)
      {
        std::list<std::shared_ptr<Node>>::iterator iter;
        for (iter = m_Parent->m_Children.begin(); iter != m_Parent->m_Children.end(); ++iter)
        {
          if ((*iter)->m_Name == m_Name)
          {
            m_Parent->m_Children.erase(iter);
            break;
          }
        }
      }

      // add this node to new parent's children list
      node->m_Children.push_back(std::shared_ptr<Node>(this));

      // set node to this node's parent
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

  void Node::destroy()
  {
    if (m_Name == default_root_name)
      return;

    if (m_Parent != nullptr)
    {
      std::list<std::shared_ptr<Node>>::iterator iter;
      for (iter = m_Parent->m_Children.begin(); iter != m_Parent->m_Children.end(); ++iter)
      {
        if ((*iter)->m_Name == m_Name)
        {
          m_Parent->m_Children.erase(iter);
          break;
        }
      }
    }

    for (std::shared_ptr<Node> it : m_Children)
      it->m_Parent = nullptr;
  }

  std::string Node::to_string() const
  {
    std::stringstream ss;
    ss << "\n\nNode\n@Name{" << m_Name << "}";
    
    if (m_Parent != nullptr)
      ss << "\n@Parent{" << m_Parent->m_Name << "}";

    if (!m_Children.empty())
    {
      ss << "\n@Children{";
      for (const std::shared_ptr<Node> it : m_Children)
        ss << "{" << it->m_Name << "}";
      ss << "}";
    }

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

    ss << "\n@Type{" << type << "}";

    if (m_Shader != nullptr)
      ss << "\n@Shader{" << m_Shader->m_path << "}";

    ss << "\n@Transform{T{"  << glm::to_string(m_Trans.m_translation) << 
                    "}R{" << glm::to_string(m_Trans.m_rotation) << 
                    "}S{" << glm::to_string(m_Trans.m_scale) << "}}";

    ss << "\n@Visible{" << std::to_string(m_visible) << "}\n-";

    return ss.str();
  }

  std::ostream& operator<<(std::ostream& os, std::shared_ptr<Node> node)
  {
    os << node->to_string();
    return os;
  }
}