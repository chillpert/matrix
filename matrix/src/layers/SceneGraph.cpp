#include <SceneGraph.h>
#include <World.h>
#include <Application.h>

namespace MX
{
  SceneGraph::SceneGraph()
  {
    m_Root = std::shared_ptr<Node>(new Node("Root"));
  }

  SceneGraph::~SceneGraph()
  {
    MX_INFO_LOG("MX: SceneGraph: Destructor");
  }

  void SceneGraph::update()
  {

  }

  void SceneGraph::render()
  {
    recursive_render(*m_Root);
  }

  std::shared_ptr<Node> hidden_search_holder = nullptr;

  std::shared_ptr<Node> SceneGraph::search(const std::string &name, std::shared_ptr<Node> it)
  {
    if (it->m_Name == name)
      hidden_search_holder = it;

    if (!it->m_Children.empty())
    {
      for (auto it : it->m_Children)
        search(name, it);
    }

    return hidden_search_holder;
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

  void SceneGraph::recursive_render(Node &it, glm::fmat4 mat)
  {
    if (is_paused)
      it.m_Trans.m_moving = 0;
    else
      it.m_Trans.m_moving = 1;

    it.setWorldTransform(mat);

    if (it.m_Shader != nullptr)
    {
      it.m_Shader->use();
      it.m_Shader->setfMat4("model", it.getWorldTransform());
      it.m_Shader->setfMat4("view", MX_WORLD.m_ActiveScene->m_Cam.getViewMatrix());
      it.m_Shader->setfMat4("projection", MX_WORLD.m_ActiveScene->m_Cam.getProjectionMatrix());

      it.m_Shader->setfVec3("lightPosition", glm::fvec3(5.0f, -5.0f, 1.0f));
      it.m_Shader->setfVec3("lightColor", glm::fvec3(1.0f, 1.0f, 1.0f));
      it.m_Shader->setfVec3("viewPosition", MX_WORLD.m_ActiveScene->m_Cam.getPosition());    
      it.m_Shader->setFloat("ambientStrength", 0.08f);
    }

    if (it.m_Texture != nullptr)
    {
      it.m_Shader->use();
      it.m_Texture->use();
      it.m_Shader->setInt("texture1", 0);
    }

    if (it.m_Model != nullptr)
      it.m_Model->draw();

    if (!it.m_Children.empty())
    {
      for (auto itChild : it.m_Children)
      {
        recursive_render(*std::shared_ptr<Node>(itChild), it.getWorldTransform());
      }
    }
  }
}