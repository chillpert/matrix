#include "matrix/src/layers/Transform.h"
#include "matrix/src/Application.h"

namespace MX
{
  Transform::Transform() { }
  Transform::~Transform() { }

  float Transform::get_time() const
  {
    return Application::get().m_Window->m_Props.m_Time;
  }

  glm::fmat4 Transform::update()
  {
    glm::fmat4 trans = glm::fmat4(1.0f);
  
    std::vector<Transform_Props>::iterator iter = m_Transforms.begin();

    while (iter != m_Transforms.end())
    {
      if (iter->t == X)
      {
        if (!iter->isAnimated)
          m_Local = glm::rotate(m_Local, get_time() * iter->factor, glm::vec3(get_time() * iter->factor, 0.0f, 0.0f));
        else
          trans = glm::rotate(trans, iter->factor, glm::vec3(iter->factor, 0.0f, 0.0f));
      }
      else if (iter->t == Y)
      {
        if (!iter->isAnimated)
          m_Local = glm::rotate(m_Local, get_time() * iter->factor, glm::vec3(0.0f, get_time() * iter->factor, 0.0f));
        else
          trans = glm::rotate(trans, iter->factor, glm::vec3(0.0f, iter->factor, 0.0f));
      }
      else if (iter->t == Z)
      {
        if (!iter->isAnimated)
          m_Local = glm::rotate(m_Local, get_time() * iter->factor, glm::vec3(0.0f, 0.0f, get_time() * iter->factor));
        else
          trans = glm::rotate(trans, iter->factor, glm::vec3(0.0f, 0.0f, iter->factor));
      }
      else if (iter->t == FORWARDS)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(0.0f, 0.0f, get_time() * iter->factor * -1.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, iter->factor * -1.0f));
      }
      else if (iter->t == BACKWARDS)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(0.0f, 0.0f, get_time() * iter->factor * 1.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, iter->factor * 1.0f));
      }
      else if (iter->t == LEFT)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(get_time() * iter->factor * -1.0f, 0.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(iter->factor * -1.0f, 0.0f, 0.0f));
      }
      else if (iter->t == RIGHT)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(get_time() * iter->factor * 1.0f, 0.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(iter->factor * 1.0f, 0.0f, 0.0f));
      }
      else if (iter->t == UP)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(0.0f, get_time() * iter->factor * 1.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f,iter->factor * 1.0f, 0.0f));
      }
      else if (iter->t == DOWN)
      {
        if (!iter->isAnimated)
          m_Local = glm::translate(m_Local, glm::vec3(0.0f, get_time() * iter->factor * -1.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, iter->factor * -1.0f, 0.0f));
      }
      else if (iter->t == SCALE)
      {
        if (!iter->isAnimated)
          m_Local = glm::scale(m_Local, glm::vec3(get_time() * iter->factor, get_time() * iter->factor, get_time() * iter->factor));
        else
          trans = glm::scale(trans, glm::vec3(iter->factor, iter->factor, iter->factor));
      }

      if (!iter->isAnimated)
        iter = m_Transforms.erase(iter);
      else
        ++iter;
    }

    return m_Local * trans;
  }

  void Transform::push(Trans t, float factor, bool isAnimated)
  {
    m_Transforms.push_back(Transform_Props{t, factor, isAnimated});
  }
}