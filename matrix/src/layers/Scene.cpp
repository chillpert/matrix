#include "matrix/src/layers/Scene.h"
#include "matrix/src/Application.h"

namespace MX
{
  void Scene::initialize()
  {
    m_Sg.m_Shader.initialize();
  }

  void Scene::update()
  {
    m_Cam.update();
    m_Sg.m_Shader.update();
  }

  void Scene::render()
  {
    m_Sg.render();
  }

  // adds object to scene graph
  void Scene::push(const std::string &object_name, const std::string &file_name)
  {
    bool objectExists = 0;

    for (auto &it : m_Sg.m_Models)
    {
      if (it.getName() == file_name)
      {
        MX_INFO_LOG("MX: Model Handler: Object already exists: Continue without parsing");

        objectExists = 1;
        Node *temp_node = new Node(object_name, file_name);
        m_Sg.m_Root->addChild(temp_node);

        #ifdef MX_DEBUG
          std::ostringstream address; 
          address << temp_node;
          std::string address_s =  address.str(); 
          MX_INFO_LOG("MX: Scene: Push: " + object_name + ": Address: " + address_s);
        #endif
        break;
      }
    }

    if (!objectExists)
    {
      MX_INFO_LOG("MX: Model Handler: Object does not exist: Continue with parsing");

      MX_MODEL temp(file_name, 1);
      m_Sg.m_Models.push_back(temp);

      Node *temp_node = new Node(object_name, file_name);
      m_Sg.m_Root->addChild(temp_node);
      
      #ifdef MX_DEBUG
        std::ostringstream address; 
        address << temp_node;
        std::string address_s =  address.str(); 
        MX_INFO_LOG("MX: Scene: Push: " + object_name + ": Address: " + address_s);
      #endif
    }

    MX_SUCCESS_LOG("MX: Scene: Push: " + object_name);
  }

  // delete object from scene graph
  void Scene::pop(const std::string &name)
  {
    MX_INFO_LOG("MX: Scene: Pop: " + name);
    m_Sg.recursive_search(name, m_Sg.m_Root);
    m_Sg.recursive_delete(search_holder);
    MX_SUCCESS_LOG("MX: Scene: Pop: " + name);
  }

  void Scene::setShader(const std::string &name)
  {
    MX_INFO_LOG("MX: Scene: Shader: " + m_Name);
    m_Sg.m_Shader = MX_SHADER(name, 1);
    MX_SUCCESS_LOG("MX: Scene: Shader: " + m_Name);
  }
}