#include "matrix/src/layers/Level.h"
#include "matrix/src/Application.h"
#include "matrix/src/Camera.h"

namespace MX
{
  MX_SHADER s1("trivial");
  MX_MODEL m1("monkey.obj");

  void Level::initialize()
  {
    s1.initialize();
    m1.initialize();
  }

  void Level::update()
  {
    s1.use();
    glm::fmat4 view_matrix = MX::Camera::get().getViewMatrix();
    glm::fmat4 projection_matrix = MX::Camera::get().getProjectionMatrix();
    s1.setfMat4("view", view_matrix);
    s1.setfMat4("projection", projection_matrix);
  }

  void Level::render()
  {
    s1.use();
    m.model_matrix = glm::rotate(m.model_matrix, 0.05f, glm::fvec3(0.0f, 1.0f, 0.0f));
    s1.setfMat4("model", m.model_matrix);
    s1.setfVec3("lightPosition", glm::vec3(5, -5, 1));
    s1.setfVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    s1.setfVec3("viewPos", MX::Camera::get().getPosition());
    m1.draw();

    //m_SG.render();
  }

  template <typename T>
  void Level::push(T obj)
  {
    if (typeid(T) == typeid(MX_MODEL))
    {
      MX_INFO("MX: Level: " + m_Name + ": Added: Model");
    }
    else if (typeid(T) == typeid(MX_SHADER))
    {
      MX_INFO("MX: Level: " + m_Name + ": Added: Shader");
    }
    else
    {
      MX_WARN("MX: Level: " + m_Name + ": Failed to add entity");
    }
  }

  template <typename T>
  T &find(const std::string &name)
  {
    return m_SG.find(name);
  }

  template MX_API void Level::push(MX_MODEL m);
  template MX_API void Level::push(MX_SHADER s);

  template MX_API MX_MODEL &Level::find(const std::string &name);
  template MX_API MX_MODEL &Level::find(const std::string &name);
}