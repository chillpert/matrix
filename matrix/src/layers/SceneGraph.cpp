#include <SceneGraph.h>
#include <World.h>
#include <Application.h>

namespace MX
{
  SceneGraph::SceneGraph()
  {
    std::shared_ptr<Node> temp_root = std::make_shared<ContainerNode>(default_root_name);
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
    if (it->m_Shader != nullptr && it->m_visible)
    {
      if (!dynamic_cast<LightNode*>(it.get()) && !dynamic_cast<DirectionalLightNode*>(it.get()) && !dynamic_cast<PointLightNode*>(it.get()) && !dynamic_cast<SpotLightNode*>(it.get()))
      {
        upload_lighting_uniforms();
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
        upload_lighting_uniforms();
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