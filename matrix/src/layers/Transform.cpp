#include "matrix/src/layers/Transform.h"
#include "matrix/src/Application.h"

namespace MX
{
  Transform::Transform() { }
  Transform::~Transform() { }

  float Transform::getTime()
  {
    return Application::get().m_Window->m_Props.m_Time;
  }

  void Transform::update_transform()
  {
    std::vector<Transform_Props>::iterator iter = m_Transforms.begin();

    while (iter != m_Transforms.end())
    {
      switch (iter->t)
      {
        case X:
        {
          m_Local = glm::rotate(m_Local, getTime() * iter->factor, glm::vec3(getTime() * iter->factor, 0.0f, 0.0f));
          iter = m_Transforms.erase(iter);
          break;
        }
        case Y:
        {
          m_Local = glm::rotate(m_Local, getTime() * iter->factor, glm::vec3(0.0f, getTime() * iter->factor, 0.0f));
          iter = m_Transforms.erase(iter);
          break;
        }
        case Z:
        {
          m_Local = glm::rotate(m_Local, getTime() * iter->factor, glm::vec3(0.0f, 0.0f, getTime() * iter->factor));
          iter = m_Transforms.erase(iter);
          break;
        }
        case FORWARDS:
        {
          std::cout << "forwards" << std::endl;
          m_Local = glm::translate(m_Local, glm::vec3(0.0f, 0.0f, getTime() * iter->factor * -1.0f));
          iter = m_Transforms.erase(iter);
          break;
        }
        default:
        {
          ++iter;
          break;
        }
      }    
    }
  }

  glm::fmat4 Transform::update()
  {
    update_transform();

    glm::fmat4 trans = glm::fmat4(1.0f);

    for (std::vector<Transform_Props>::iterator iter = m_Animations.begin(); iter != m_Animations.end(); ++iter)
    {
      switch (iter->t)
      {
        case X:
        {
          trans = glm::rotate(trans, getTime() * iter->factor, glm::vec3(getTime() * iter->factor, 0.0f, 0.0f));
          break;
        }
        case Y:
        {
          trans = glm::rotate(trans, getTime() * iter->factor, glm::vec3(0.0f, getTime() * iter->factor, 0.0f));
          break;
        }
        case Z:
        {
          trans = glm::rotate(trans, getTime() * iter->factor, glm::vec3(0.0f, 0.0f, getTime() * iter->factor));
          break;
        }
        case FORWARDS:
        {
          trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, getTime() * iter->factor * -1.0f));
          break;
        }
      }
    }

    return m_Local * trans;
  }

  void Transform::push_animation(Trans t, float factor)
  {
    m_Animations.push_back(Transform_Props{t, factor, 1});
  }

  void Transform::push_translation(Trans t, float factor)
  {
    m_Transforms.push_back(Transform_Props{t, factor, 0});
  }
}