#include "matrix/src/Camera.h"

namespace MX
{

  void Camera::update()
  {
    glm::vec3 t_front;
    t_front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    t_front.y = sin(glm::radians(m_Pitch));
    t_front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(t_front); 
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  
    m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
  }

  void Camera::processKeyboard(m_Camera direction, float speed)
  {
    switch (direction)
    {
      case FORWARDS:
        m_Position += m_Front * speed;
        break;
      case BACKWARDS:
        m_Position -= m_Front * speed;
        break;
      case LEFT:
        m_Position -= m_Right * speed; 
        break;
      case RIGHT:
        m_Position += m_Right * speed;
        break;
      case UP:
        m_Position.y += speed;
        break;
      case DOWN:
        m_Position.y -= speed;
        break;
      default:
        MX_WARN("Camera direction unkown");
        break;
    }
    update();
  }

  void Camera::processMouse(float xoffset, float yoffset)
  {
    xoffset *= m_Sensitivity;
    yoffset *= m_Sensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    if (m_Yaw > 360.0f)
    {
      m_Yaw = fmod(m_Yaw, 360.0f);
    }

    if (m_Yaw < 0.0f)
    {
      m_Yaw = 360.0f + fmod(m_Yaw, 360.0f);
    }

    if (m_Pitch > 89.0f)
    {
      m_Pitch = 89.0f;
    }

    if (m_Pitch < -89.0f)
    {
      m_Pitch = -89.0f;
    }

    update();
  }
}