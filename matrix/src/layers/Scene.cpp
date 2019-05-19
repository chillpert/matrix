#include "matrix/src/layers/Scene.h"
#include "matrix/src/Application.h"

namespace MX
{
  void Scene::initialize()
  {
    std::string shader_name = "trivial";
    
    m_Sg.m_Shader.setName(shader_name);
    m_Sg.m_Shader.initialize();
    
    MX_INFO("MX: Scene: " + m_Name + ": Initalized with default shader: " + shader_name);
  }

  void Scene::update()
  {
    m_Sg.m_Shader.use();
    m_Sg.m_Shader.setfMat4("view", m_Cam.getViewMatrix());
    m_Sg.m_Shader.setfMat4("projection", m_Cam.getProjectionMatrix());
  }

  void Scene::render()
  {
    m_Sg.m_Shader.use();
    m_Sg.m_Shader.setfVec3("lightPosition", glm::vec3(5, -5, 1));
    m_Sg.m_Shader.setfVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    m_Sg.m_Shader.setfVec3("viewPos", m_Cam.getPosition());

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