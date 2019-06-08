#include "matrix/src/layers/SceneGraph.h"
#include "matrix/src/layers/World.h"

namespace MX
{
/*
  if recursive search is called then this pointer will
  point to the item that has been searched for the last
  time
*/
  Node *search_holder = NULL;

  SceneGraph::SceneGraph()
  {

  }

  SceneGraph::~SceneGraph()
  {
    std::list<Node*> temp;
    std::copy(m_Root->getChildren().begin(), m_Root->getChildren().end(), std::back_inserter(temp));

    for (Node *it : temp)
      iterative_delete(it->m_Name);
  }

  void SceneGraph::update()
  {
    
  }

  void SceneGraph::render()
  {
    recursive_render(*m_Root);
  }

  static std::string first_node;
  static bool first_iteration = 1;
  static bool found_node = 0;

  // result equals global pointer: search_holder
  void SceneGraph::recursive_search(const std::string &name, Node *it)
  {
    if (first_iteration)
    {
      first_node = it->m_Name;
      found_node = 0;
      first_iteration = 0;
    }

    if (it->m_Name != name)
    {
      if (!it->getChildren().empty())
      {
        for (Node *itChild : it->getChildren())
          recursive_search(name, itChild);
      }
    }
    else
    {
      search_holder = it;
      found_node = 1;
    }
    
    if (first_node == it->m_Name && !found_node)
    {
      MX_FATAL("MX: SceneGraph: Recursive Search: " + first_node);
      first_iteration = 1;
      found_node = 0;
      throw new std::exception();
    }
    else if (first_node == it->m_Name && found_node)
    {
      first_iteration = 1;
      found_node = 0;
    }
  }

  Node *hidden_search_holder = nullptr;

  Node *SceneGraph::search(const std::string &name, Node *it)
  {
    if (first_iteration)
    {
      first_node = it->m_Name;
      found_node = 0;
      first_iteration = 0;
    }

    if (it->m_Name != name)
    {
      if (!it->getChildren().empty())
      {
        for (Node *itChild : it->getChildren())
          search(name, itChild);
      }
    }
    else
    {
      hidden_search_holder = it;
      found_node = 1;
    }
    
    if (first_node == it->m_Name && !found_node)
    {
      MX_FATAL("MX: SceneGraph: Recursive Search: " + first_node);
      first_iteration = 1;
      found_node = 0;
      throw new std::exception();
    }
    else if (first_node == it->m_Name && found_node)
    {
      first_iteration = 1;
      found_node = 0;
      return hidden_search_holder;
    }
  }

  // deletes all children recursively from a given node
  void SceneGraph::recursive_delete(Node *it)
  {
    if (!it->getChildren().empty())
    {
      for (Node *itChild : it->getChildren())
      {
        recursive_delete(itChild);
        MX_INFO_LOG("MX: SceneGraph: Recursive Delete: Deleting: " + itChild->m_Name);
        delete itChild;
        itChild = nullptr;
      }
    }
    // leaf
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

      MX_INFO_LOG("MX: SceneGraph: Recursive Delete (leaf): Deleting: " + it->m_Name);
      delete it;
      it = nullptr;
    }
  }

  void SceneGraph::iterative_delete(const std::string &name)
  {
    std::vector<std::string> all_kids;

    try
    {
      recursive_search(name, m_Root);
    }
    catch (const std::exception &e)
    {
      return;
    }
    
    getAllObjects(&all_kids, search_holder);
    
    std::reverse(all_kids.begin(), all_kids.end());

    for (const auto &it : all_kids)
    {
      recursive_search(it, m_Root);

      Node *parent = search_holder->getParent();

      for (std::list<Node*>::iterator iter = parent->getChildren().begin(); iter != parent->getChildren().end(); ++iter)
      {
        if ((*iter)->m_Name == search_holder->m_Name)
        {
          parent->getChildren().erase(iter);
          break;
        }
      }

      MX_INFO_LOG("MX: SceneGraph: Iterative Delete: Node: " + search_holder->m_Name);
      delete search_holder;
      search_holder = nullptr;
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

    if (it.m_Shader != nullptr)
    {
      it.m_Shader->update();
      it.m_Shader->setfMat4("model", it.getWorldTransform());
    }

    if (it.m_Texture != nullptr)
      it.m_Texture->use();
    
    if (it.m_Model != nullptr)
      it.m_Model->draw();

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