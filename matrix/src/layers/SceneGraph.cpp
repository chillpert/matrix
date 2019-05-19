#include "matrix/src/layers/SceneGraph.h"

namespace MX
{
/*
  if recursive search is called then this pointer will
  point to the item that has been search the last time
*/
  Node *search_holder = NULL;

  void SceneGraph::render()
  {
    recursive_render(*m_Root);
  }

  // set the global search_holder pointer to a hit if possible
  void SceneGraph::recursive_search(const std::string &name, Node *it)
  {
    if (it->m_Name != name)
    {
      if (!it->getChildren().empty())
      {
        for (Node *itChild : it->getChildren())
          recursive_search(name, itChild);
      }
    }
    else
      search_holder = it;
  }

  // deletes all children recursively from a given node
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
      Node *parent = it->getParent();

      for (std::list<Node*>::iterator iter = parent->getChildren().begin(); iter != parent->getChildren().end(); ++iter)
      {
        if ((*iter)->m_Name == it->m_Name)
        {
          parent->getChildren().erase(iter);
          break;
        }
      }
      delete it;
    }
  }

  void SceneGraph::getAllObjects(std::vector<std::string> *vec, Node *it)
  {
    vec->push_back(it->m_Name);

    if (!it->getChildren().empty())
    {
      for (Node *itChild : it->getChildren())
        getAllObjects(vec, itChild);
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
  }
}