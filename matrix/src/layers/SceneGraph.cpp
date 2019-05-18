#include "matrix/src/layers/SceneGraph.h"

namespace MX
{
  void SceneGraph::render()
  {    
    recursive_render(*m_Root);
  }

  Node *SceneGraph::recursive_search(const std::string &name, Node *it)
  {
    MX_INFO_LOG("MX: SceneGraph: Searching: Comparing: " + name + " and " + it->m_Name);
    MX_WARN("Current Node's name: " + it->m_Name);
    if (it->m_Name == name)
    {
      MX_FATAL("returning: " + it->m_Name);
      return it;
    }
    else
    {
      if (!it->getChildren().empty())
      {
        for (Node *itChild : it->getChildren())
          recursive_search(name, itChild);
      }
    }
  }

  void SceneGraph::recursive_delete(Node *it)
  {
    if (!it->getChildren().empty())
    {
      for (Node *itChild : it->getChildren())
      {
        recursive_delete(itChild);
        delete itChild;
      }
    }
    else
    {
      delete it;
    }
  }

  void SceneGraph::recursive_render(Node &it, glm::fmat4 mat)
  {  
    it.setWorldTransform(mat);
    
    for (auto &model : m_Models) 
    {
      if (model.getName() == it.m_ModelName)
      {
        m_Shader.setfMat4("model", it.getWorldTransform());
        model.draw();
      }
    }

    if (!it.getChildren().empty())
    {
      for (Node* itChild : it.getChildren())
      {
        Node ptr = *itChild;
        recursive_render(*itChild, it.getWorldTransform());
      }
    }
    else
    {
      // MX_INFO_LOG("MX: Scene Graph: Recursive Render: " + it.m_Name + " does not have any children");
    }
  }
}