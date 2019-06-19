#include <Camera.h>
#include <InputMap.h>
#include <Application.h>

namespace MX
{
  void Camera::update()
  {
    processKeyboard();
  }

  void Camera::updateVectors()
  {
    glm::vec3 t_front;
    t_front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    t_front.y = sin(glm::radians(m_Pitch));
    t_front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(t_front);
    m_Right = glm::normalize(glm::cross(m_Front, m_worldUp));
    m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
  }

  void Camera::setScreenDimensions(int width, int height)
  {
    m_ScreenWidth = (float) width;
    m_ScreenHeight = (float) height;
  }

  void Camera::processKeyboard()
  {
    float finalSpeed = speed * Application::get().m_Window->m_Props.m_DeltaTime;
    if (key_w)
      m_Position += m_Front * finalSpeed;
    if (key_s)
      m_Position -= m_Front * finalSpeed;
    if (key_a)
      m_Position -= m_Right * finalSpeed; 
    if (key_d)
      m_Position += m_Right * finalSpeed;
    if (key_c)
      m_Position.y -= finalSpeed / 2.0f;
    if (key_space)
      m_Position.y += finalSpeed / 2.0f;
  }

  void Camera::processMouse(float xoffset, float yoffset)
  {
    xoffset *= m_Sensitivity; // for mouse smoothing (* Application::get().m_Window->m_Props.m_DeltaTime;)
    yoffset *= m_Sensitivity; // for mouse smoothing (* Application::get().m_Window->m_Props.m_DeltaTime;)

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    if (m_Yaw > 360.0f)
      m_Yaw = fmod(m_Yaw, 360.0f);

    if (m_Yaw < 0.0f)
      m_Yaw = 360.0f + fmod(m_Yaw, 360.0f);

    if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;

    if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;

    updateVectors();
  }
}