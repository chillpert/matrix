#include "SceneGraph.h"
#include "World.h"
#include "Application.h"
#include "MousePicker.h"

namespace MX
{
  SceneGraph::SceneGraph()
  {
    m_Root = std::make_shared<ContainerNode>(Constants::default_root_name);
    m_Root->m_Parent = nullptr;
  }

  SceneGraph::~SceneGraph()
  {
    MX_INFO_LOG("MX: SceneGraph: Destructor");
  }

  void SceneGraph::initialize()
  {
    recursive_initialize(m_Root);
    upload_lighting_uniforms();
  }

  void SceneGraph::update()
  {
    upload_lighting_uniforms();
  }

  void SceneGraph::render()
  {
    recursive_render(m_Root);
  }

  void SceneGraph::recursive_search(const std::string &name, std::shared_ptr<Node> it)
  {
    if (it->m_Name == name)
      hidden_search_holder = it;

    if (!it->m_Children.empty())
    {
      for (auto it : it->m_Children)
        recursive_search(name, it);
    }
  }

  void SceneGraph::get_all_objects(std::vector<std::string> *vec, std::shared_ptr<Node> it)
  {
    vec->push_back(it->m_Name);

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        get_all_objects(vec, std::shared_ptr<Node>(itChild));
    }
  }

  void SceneGraph::get_all_objects(std::vector<const char*> &vec, std::shared_ptr<Node> it)
  {
    vec.push_back(it->m_Name.c_str());

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        get_all_objects(vec, std::shared_ptr<Node>(itChild));
    }
  }

  void SceneGraph::get_all_objects(std::vector<std::shared_ptr<Node>> &vec, std::shared_ptr<Node> it)
  {
    vec.push_back(it);

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        get_all_objects(vec, std::shared_ptr<Node>(itChild));
    }
  }

  void SceneGraph::push(const std::shared_ptr<Node> node)
  {
    if (node != nullptr)
    {
      node->setShader(MX_GET_SHADER(MX_MATRIX_SHADERS + Constants::default_shader_name));
      node->upload_uniforms();

      if (search<Node>(node->m_Name) == nullptr)
      {
        m_Root->addChild(node);
        return;
      }
      
      uint64_t counter = 0;
      bool accepted = false;
      std::string current_name = node->m_Name;
      std::string appendix = "";

      while (!accepted)
      {
        std::shared_ptr<Node> temp = search<Node>(current_name + appendix);
        
        if (temp != nullptr)
        {
          ++counter;
          appendix = "_" + std::to_string(counter);
        }
        else
          accepted = true;
      }

      node->m_Name += appendix;
      m_Root->addChild(node);
    }
  }

  void SceneGraph::upload_lighting_uniforms()
  {
    // lights
    for (unsigned short i = 0; i < m_directional_light_nodes.size(); ++i)
      if (m_directional_light_nodes.at(i)->m_visible)
        m_directional_light_nodes.at(i)->upload_uniforms(i);

    for (unsigned short i = 0; i < m_point_light_nodes.size(); ++i)
      if (m_point_light_nodes.at(i)->m_visible)
        m_point_light_nodes.at(i)->upload_uniforms(i);

    for (unsigned short i = 0; i < m_spot_light_nodes.size(); ++i)
      if (m_spot_light_nodes.at(i)->m_visible)
        m_spot_light_nodes.at(i)->upload_uniforms(i);
  }

  void SceneGraph::recursive_initialize(std::shared_ptr<Node> it)
  {
    if (it == nullptr)
      return;

    if (it->m_Shader != nullptr && it->m_visible)
      it->upload_uniforms();

    if (!it->m_Children.empty())
    {
      for (std::shared_ptr<Node> it_child : it->m_Children)
        recursive_initialize(it_child);
    }
  }

  void SceneGraph::recursive_render(std::shared_ptr<Node> it, glm::fmat4 mat)
  {
    it->m_Trans.update(mat);

    if (it->m_Shader != nullptr && it->m_visible)
      it->upload_uniforms();

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        recursive_render(itChild, it->m_Trans.m_world);
    }
  }
}