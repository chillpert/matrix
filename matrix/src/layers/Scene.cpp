#include "matrix/src/layers/Scene.h"
#include "matrix/src/Application.h"
#include "matrix/src/Camera.h"

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
    m_Sg.m_Shader.setfMat4("view", MX::Camera::get().getViewMatrix());
    m_Sg.m_Shader.setfMat4("projection", MX::Camera::get().getProjectionMatrix());
  }

  void Scene::render()
  {
    m_Sg.m_Shader.use();
    m_Sg.m_Shader.setfVec3("lightPosition", glm::vec3(5, -5, 1));
    m_Sg.m_Shader.setfVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    m_Sg.m_Shader.setfVec3("viewPos", MX::Camera::get().getPosition());

    m_Sg.render();
  }

  void Scene::push(const std::string &object_name, const std::string &file_name)
  {
    bool objectExists = 0;

    for (auto &it : m_Sg.m_Models)
    {
      if (it.getName() == file_name)
      {
        MX_INFO("MX: Model Handler: Object already exists: Continue without parsing");

        objectExists = 1;
        m_Sg.m_Root->addChild(new Node(object_name, file_name));
        break;
      }
    }

    if (!objectExists)
    {
      MX_INFO("MX: Model Handler: Object does not exist: Continue with parsing");

      MX_MODEL temp(file_name, 1);
      m_Sg.m_Models.push_back(temp);
      m_Sg.m_Root->addChild(new Node(object_name, file_name));
    }
  }

  void Scene::pop(const std::string &name)
  {
    m_Sg.recursive_delete(m_Sg.recursive_search(name, m_Sg.m_Root));
  }

  void Scene::setShader(const std::string &name)
  {
    m_Sg.m_Shader = MX_SHADER(name, 1);
    MX_INFO("MX: Scene: " + m_Name + ": Added: Shader");
  }
}