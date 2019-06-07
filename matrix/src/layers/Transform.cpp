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

  void Transform::scale(float factor)
  {
    isTransformed = 1;
  }

  void Transform::rotate(Transform_Axis axis, float factor)
  {
    isTransformed = 1;
  }

  void Transform::translate(Transform_Direction, float factor)
  {
    isTransformed = 1;
  }

  void Transform::animate_direction(Transform_Direction dir, float speed, bool never_stop)
  {
    isAnimated = 1;
  }

  void Transform::animate_rotation(Transform_Axis axis, float factor, bool never_stop)
  {
    switch (axis)
    {
      case X:
      {
        m_LocalTransform = glm::rotate(m_LocalTransform, getTime() * factor, glm::vec3(getTime() * factor, 0.0f, 0.0f));
        break;
      }
      case Y:
      {
        m_LocalTransform = glm::rotate(m_LocalTransform, getTime() * factor, glm::vec3(0.0f, getTime() * factor, 0.0f));
        break;
      }
      case Z:
      {
        m_LocalTransform = glm::rotate(m_LocalTransform, getTime() * factor, glm::vec3(0.0f, 0.0f, getTime() * factor));
        break;
      }
    }

    isAnimated = 1;
  }
}