#include "Transform.h"
#include "Application.h"

namespace MX
{
  // return m_local * trans;
  Transform::Transform() : 
    m_local(glm::fmat4(1.0f)), 
    m_world(glm::fmat4(1.0f)),
    m_rotation(glm::vec3()),
    m_translation(glm::vec3()),
    m_scale(glm::vec3(1.0f))
    { }

  void Transform::update(const glm::mat4 mat)
  {
    glm::mat4 temp = glm::mat4(1.0f);
    
    m_local = 
      glm::translate(temp, m_translation) *
      glm::rotate(temp, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
      glm::rotate(temp, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
      glm::rotate(temp, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
      glm::scale(temp, m_scale);
    
    m_world = mat * m_local;
  }

  void Transform::translateX(float factor)
  {
    m_translation.x = factor;
  }

  void Transform::translateY(float factor)
  {
    m_translation.y = factor;
  }

  void Transform::translateZ(float factor)
  {
    m_translation.z = factor;
  }

  void Transform::translate(float x, float y, float z)
  {
    m_translation.x = x;
    m_translation.y = y;
    m_translation.z = z;
  }

  void Transform::translate(const glm::vec3& translate)
  {
    m_translation = translate;
  }

  void Transform::translate(const glm::mat4& translate)
  {
    
  }

  void Transform::rotateX(float rad)
  {
    m_rotation.x = rad;
  }

  void Transform::rotateY(float rad)
  {
    m_rotation.y = rad;
  }

  void Transform::rotateZ(float rad)
  {
    m_rotation.z = rad;
  }

  void Transform::rotate(float x, float y, float z)
  {
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
  }

  void Transform::rotate(const glm::vec3& rotation)
  {
    m_rotation = rotation;
  }

  void Transform::rotate(const glm::mat4& rotation)
  {

  }

  void Transform::scaleX(float factor)
  {
    m_scale.x = factor;
  }

  void Transform::scaleY(float factor)
  {
    m_scale.y = factor;
  }

  void Transform::scaleZ(float factor)
  {
    m_scale.z = factor;
  }

  void Transform::scale(float x, float y, float z)
  {
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
  }

  void Transform::scale(const glm::vec3& scale)
  {
    m_scale = scale;
  }

  void Transform::scale(const glm::mat4& scale)
  {

  }
}