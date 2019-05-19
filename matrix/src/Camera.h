#ifndef CAMERA_H
#define CAMERA_H

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  // camera directions
  enum m_Camera
  {
    FORWARDS, BACKWARDS, LEFT, RIGHT, UP, DOWN
  };

  class Camera
  {
  public:
    MX_API Camera()
      : m_Position(glm::vec3(0.0f, 0.0f, 3.0f)), 
        m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_Yaw(-90.0f),
        m_Pitch(0.0f),
        m_Sensitivity(0.06f),
        m_Fov(45.0f)
    {
      update();
    }

    MX_API ~Camera() {}
  
    MX_API void processKeyboard(m_Camera direction, float speed); 
    MX_API void processMouse(float xoffset, float yoffset);

    MX_API inline glm::mat4 getViewMatrix() { return glm::lookAt(m_Position, m_Position + m_Front, m_WorldUp); }
    MX_API inline glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(m_Fov), (float)1200 / (float)600, 0.1f, 100.0f); }

    MX_API inline glm::fvec3 getPosition() { return m_Position; }
  private:
    glm::fvec3 m_Position; 
    glm::fvec3 m_Front;
    glm::fvec3 m_WorldUp;
    glm::fvec3 m_Up;
    glm::fvec3 m_Right;

    float m_Yaw;
    float m_Pitch;
    float m_Sensitivity;
    float m_Fov;

    MX_API void update();
  };
}

#endif // CAMERA_H