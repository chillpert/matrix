#include <Transform.h>
#include <Application.h>

namespace MX
{
  static float last_time = 0.0f;

  float Transform::get_time() const
  {
    if (!m_moving)
      return last_time;

    last_time = Application::get().m_Window->m_Props.m_Time;
    return last_time;
  }

  glm::fmat4 Transform::update()
  {
    glm::fmat4 trans = glm::fmat4(1.0f);

    std::vector<Transform_Props>::iterator iter = m_transforms.begin();

    while (iter != m_transforms.end())
    {
      if (iter->t == X)
      {
        if (!iter->is_animated)
          m_local = glm::rotate(m_local, glm::radians(iter->factor), glm::vec3(iter->factor, 0.0f, 0.0f));
        else
          trans = glm::rotate(trans, get_time() * iter->factor, glm::vec3(get_time() * iter->factor, 0.0f, 0.0f));
      }
      else if (iter->t == Y)
      {
        if (!iter->is_animated)
          m_local = glm::rotate(m_local, iter->factor, glm::vec3(0.0f, iter->factor, 0.0f));
        else
          trans = glm::rotate(trans, get_time() * iter->factor, glm::vec3(0.0f, get_time() * iter->factor, 0.0f));
      }
      else if (iter->t == Z)
      {
        if (!iter->is_animated)
          m_local = glm::rotate(m_local, iter->factor, glm::vec3(0.0f, 0.0f, iter->factor));
        else
          trans = glm::rotate(trans, get_time() * iter->factor, glm::vec3(0.0f, 0.0f, get_time() * iter->factor));
      }
      else if (iter->t == FORWARDS)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(0.0f, 0.0f, iter->factor * -1.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, get_time() * iter->factor * -1.0f));
      }
      else if (iter->t == BACKWARDS)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(0.0f, 0.0f, iter->factor * 1.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, get_time() * iter->factor * 1.0f));
      }
      else if (iter->t == LEFT)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(iter->factor * -1.0f, 0.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(get_time() * iter->factor * -1.0f, 0.0f, 0.0f));
      }
      else if (iter->t == RIGHT)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(iter->factor * 1.0f, 0.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(get_time() * iter->factor * 1.0f, 0.0f, 0.0f));
      }
      else if (iter->t == UP)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(0.0f, iter->factor * 1.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, get_time() * iter->factor * 1.0f, 0.0f));
      }
      else if (iter->t == DOWN)
      {
        if (!iter->is_animated)
          m_local = glm::translate(m_local, glm::vec3(0.0f, iter->factor * -1.0f, 0.0f));
        else
          trans = glm::translate(trans, glm::vec3(0.0f, get_time() * iter->factor * -1.0f, 0.0f));
      }
      else if (iter->t == SCALE)
      {
        if (!iter->is_animated)
          m_local = glm::scale(m_local, glm::vec3(iter->factor, iter->factor, iter->factor));
        else
          trans = glm::scale(trans, glm::vec3(get_time() * iter->factor, get_time() * iter->factor, get_time() * iter->factor));
      }

      if (!iter->is_animated)
        iter = m_transforms.erase(iter);
      else
        ++iter;
    }

    return m_local * trans;
  }

  void Transform::push(const Trans &t, float factor, bool is_animated)
  {
    m_transforms.push_back(Transform_Props{t, factor, is_animated});
  }
}