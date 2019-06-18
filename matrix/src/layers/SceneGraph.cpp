#include "matrix/src/layers/SceneGraph.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  SceneGraph::SceneGraph()
  {
    m_Root = std::shared_ptr<Node>(new Node("Root"));
  }

  SceneGraph::~SceneGraph()
  {
    std::list<std::shared_ptr<Node>> temp;
    std::copy(m_Root->m_Children.begin(), m_Root->m_Children.end(), std::back_inserter(temp));

    for (auto it : temp)
      iterative_delete(it->m_Name);
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
    {
      MX_SUCCESS("MX: SceneGraph: Found: " + it->m_Name);
      hidden_search_holder = it;
    }

    if (!it->m_Children.empty())
    {
      for (auto it : it->m_Children)
        search(name, it);
    }

    return hidden_search_holder;
  }

  // deletes all children recursively from a given node
  void SceneGraph::recursive_delete(std::shared_ptr<Node> it)
  {
    if (!it->m_Children.empty())
    {
      for (auto itChild : it->m_Children)
      {
        recursive_delete(std::shared_ptr<Node>(itChild));
        MX_INFO_LOG("MX: SceneGraph: Recursive Delete: Deleting: " + itChild->m_Name);
        // delete itChild;
        // itChild = nullptr;
      }
    }
    // leaf
    else
    {
      std::shared_ptr<Node> parent = it->m_Parent;

      for (std::list<std::shared_ptr<Node>>::iterator iter = parent->m_Children.begin(); iter != parent->m_Children.end(); ++iter)
      {
        if ((*iter)->m_Name == it->m_Name)
        {
          parent->m_Children.erase(iter);
          break;
        }
      }

      MX_INFO_LOG("MX: SceneGraph: Recursive Delete (leaf): Deleting: " + it->m_Name);
    }
  }

  void SceneGraph::iterative_delete(const std::string &name)
  {
    std::vector<std::string> all_kids;
    std::shared_ptr<Node> temp;

    try
    {
      temp = search(name, m_Root);
    }
    catch (const std::exception &e)
    {
      return;
    }
    
    getAllObjects(&all_kids, std::shared_ptr<Node>(temp));
    
    std::reverse(all_kids.begin(), all_kids.end());

    for (const auto &it : all_kids)
    {
      temp = search(it, m_Root);

      std::shared_ptr<Node> parent = temp->m_Parent;

      for (std::list<std::shared_ptr<Node>>::iterator iter = parent->m_Children.begin(); iter != parent->m_Children.end(); ++iter)
      {
        if ((*iter)->m_Name == temp->m_Name)
        {
          parent->m_Children.erase(iter);
          break;
        }
      }

      MX_INFO_LOG("MX: SceneGraph: Iterative Delete: Node: " + temp->m_Name);
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

  void SceneGraph::recursive_render(Node &it, glm::fmat4 mat)
  {
    it.setWorldTransform(mat);

    if (it.m_Shader != nullptr)
    {
      it.m_Shader->use();
      it.m_Shader->setfMat4("model", it.getWorldTransform());
      it.m_Shader->setfMat4("view", World::get().m_ActiveScene->m_Cam.getViewMatrix());
      it.m_Shader->setfMat4("projection", World::get().m_ActiveScene->m_Cam.getProjectionMatrix());

      it.m_Shader->setfVec3("lightPosition", glm::fvec3(5.0f, -5.0f, 1.0f));
      it.m_Shader->setfVec3("lightColor", glm::fvec3(1.0f, 1.0f, 1.0f));
      it.m_Shader->setfVec3("viewPosition", World::get().m_ActiveScene->m_Cam.getPosition());    
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