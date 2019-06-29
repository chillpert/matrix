#include <SceneGraph.h>
#include <World.h>
#include <Application.h>

namespace MX
{
  SceneGraph::SceneGraph()
  {
    std::shared_ptr<Node> temp_root(new ContainerNode(default_root_name));
    temp_root->m_Parent = nullptr;
    m_Root = temp_root;
  }

  SceneGraph::~SceneGraph()
  {
    MX_INFO_LOG("MX: SceneGraph: Destructor");
  }

  void SceneGraph::initialize()
  {
    recursive_initialize(m_Root);
  }

  void SceneGraph::update()
  {

  }

  void SceneGraph::render()
  {
    recursive_render(m_Root);
  }

  static std::shared_ptr<Node> hidden_search_holder = nullptr;

  void recursive_search(const std::string &name, std::shared_ptr<Node> it)
  {
    if (it->m_Name == name)
      hidden_search_holder = it;

    if (!it->m_Children.empty())
    {
      for (auto it : it->m_Children)
        recursive_search(name, it);
    }
  }

  std::shared_ptr<Node> SceneGraph::search(const std::string &name, const NodeType &type, std::shared_ptr<Node> it)
  {
    hidden_search_holder = nullptr;

    if (it == nullptr)
      recursive_search(name, Application::get().m_World.m_ActiveScene->m_Sg.m_Root);
    else
      recursive_search(name, it);

    if (hidden_search_holder == nullptr)
      throw mx_entity_not_found(name + " (SceneGraph::search)");

    switch (type)
    {
      case type_node:
        return hidden_search_holder;
      case type_container:
        return std::static_pointer_cast<ContainerNode>(hidden_search_holder);
      case type_geometry:
        return std::static_pointer_cast<GeometryNode>(hidden_search_holder);
      case type_light:
        return std::static_pointer_cast<LightNode>(hidden_search_holder);
      case type_directionalLight:
        return std::static_pointer_cast<DirectionalLightNode>(hidden_search_holder);
      case type_pointLight:
        return std::static_pointer_cast<PointLightNode>(hidden_search_holder);
      case type_spotLight:
        return std::static_pointer_cast<SpotLightNode>(hidden_search_holder);
      default:
        throw mx_invalid_type(name + " (SceneGraph::search)");
    }
  }

  void SceneGraph::getAllObjects(std::vector<std::string> *vec, std::shared_ptr<Node> it)
  {
    vec->push_back(it->m_Name);

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        getAllObjects(vec, std::shared_ptr<Node>(itChild));
    }
  }

  void SceneGraph::getAllObjects(std::vector<const char*> &vec, std::shared_ptr<Node> it)
  {
    vec.push_back(it->m_Name.c_str());

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        getAllObjects(vec, std::shared_ptr<Node>(itChild));
    }
  }

  void SceneGraph::upload_lighting_unfiorms()
  {
    // lights
    for (u_short i = 0; i < m_directional_light_nodes.size(); ++i)
      if (m_directional_light_nodes.at(i)->m_visible)
        m_directional_light_nodes.at(i)->upload_uniforms(i);

    for (u_short i = 0; i < m_point_light_nodes.size(); ++i)
      if (m_point_light_nodes.at(i)->m_visible)
        m_point_light_nodes.at(i)->upload_uniforms(i);

    for (u_short i = 0; i < m_spot_light_nodes.size(); ++i)
      if (m_spot_light_nodes.at(i)->m_visible)
        m_spot_light_nodes.at(i)->upload_uniforms(i);
  }

  void SceneGraph::recursive_initialize(std::shared_ptr<Node> it)
  {
    if (it->m_Shader != nullptr && it->m_visible)
    {
      if (!dynamic_cast<LightNode*>(it.get()) && !dynamic_cast<DirectionalLightNode*>(it.get()) && !dynamic_cast<PointLightNode*>(it.get()) && !dynamic_cast<SpotLightNode*>(it.get()))
      {
        upload_lighting_unfiorms();
        it->upload_uniforms();
      }
    }

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
        recursive_render(itChild);
    }
  }

  void SceneGraph::recursive_render(std::shared_ptr<Node> it, glm::fmat4 mat)
  {
    if (is_paused)
      it->m_Trans.m_moving = 0;
    else
      it->m_Trans.m_moving = 1;

    it->setWorldTransform(mat);

    if (it->m_Shader != nullptr && it->m_visible)
    {
      if (!dynamic_cast<LightNode*>(it.get()) && !dynamic_cast<DirectionalLightNode*>(it.get()) && !dynamic_cast<PointLightNode*>(it.get()) && !dynamic_cast<SpotLightNode*>(it.get()))
      {
        upload_lighting_unfiorms();
        it->upload_uniforms();
      }
    }

    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
      {
        recursive_render(itChild, it->getWorldTransform());
      }
    }
  }
}