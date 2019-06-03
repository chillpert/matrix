#include "matrix/src/layers/Scene.h"
#include "matrix/src/layers/World.h"
#include "matrix/src/Application.h"

namespace MX
{
  void Scene::initialize()
  {

  }

  void Scene::update()
  {
    m_Cam.update();
  }

  void Scene::render()
  {
    m_Sg.render();
  }

  // adds object to scene graph
  void Scene::push(const std::string &object_name, const std::string &file_name, const std::string &node_to_attach_to)
  {
    bool objectExists = 0;

    for (auto &it : World::get().m_Models)
    {
      if (it.getName() == file_name)
      {
        MX_INFO_LOG("MX: Model Handler: Object already exists: Continue without parsing");

        objectExists = 1;
        Node *temp_node = new Node(object_name, file_name);
        m_Sg.recursive_search(node_to_attach_to, m_Sg.m_Root);
        search_holder->addChild(temp_node);

        #ifdef MX_DEBUG
          std::ostringstream address;
          address << temp_node;
          std::string address_s =  address.str(); 
          MX_INFO_LOG("MX: Scene: " + m_Name + ": Push: " + object_name + ": Address: " + address_s);
        #endif
        break;
      }
    }

    if (!objectExists)
    {
      MX_INFO_LOG("MX: Model Handler: Object does not exist: Continue with parsing");

      MX_MODEL temp(file_name, 1);
      World::get().m_Models.push_back(temp);

      Node *temp_node = new Node(object_name, file_name);
      m_Sg.recursive_search(node_to_attach_to, m_Sg.m_Root);
      search_holder->addChild(temp_node);
      
      #ifdef MX_DEBUG
        std::ostringstream address; 
        address << temp_node;
        std::string address_s =  address.str(); 
        MX_INFO_LOG("MX: Scene: " + m_Name + ": Push: " + object_name + ": Address: " + address_s);
      #endif
    }

    MX_SUCCESS_LOG("MX: Scene: Push: " + object_name);
  }

  // delete object from scene graph
  void Scene::pop(const std::string &name)
  {
  #ifdef MX_DEBUG
    m_Sg.recursive_search(name, m_Sg.m_Root);

    std::ostringstream address; 
    address << search_holder;
    std::string address_s =  address.str();
    MX_INFO_LOG("MX: Scene: " + m_Name + ": Pop: Trying to pop: " + search_holder->m_Name + ": Adress: " + address_s);
  #endif              
    m_Sg.iterative_delete(name);

    MX_SUCCESS_LOG("MX: Scene: " + m_Name + ": Pop: " + name);
  }
}