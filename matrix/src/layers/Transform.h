#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stdafx.h"

namespace MX
{
  class Transform
  {
  public:
    MX_API Transform();

    MX_API void update(const glm::mat4 mat = glm::mat4(1.0f));

    MX_API void translateX(float factor);
    MX_API void translateY(float factor);
    MX_API void translateZ(float factor);
    MX_API void translate(float x, float y, float z);
    MX_API void translate(const glm::vec3& translate);
    MX_API void translate(const glm::mat4& translate);

    MX_API void rotateX(float rad);
    MX_API void rotateY(float rad);
    MX_API void rotateZ(float rad);
    MX_API void rotate(float x, float y, float z);
    MX_API void rotate(const glm::vec3& rotation);
    MX_API void rotate(const glm::mat4& rotation);

    MX_API void scaleX(float factor);
    MX_API void scaleY(float factor);
    MX_API void scaleZ(float factor);
    MX_API void scale(float x, float y, float z);
    MX_API void scale(const glm::vec3& scale);
    MX_API void scale(const glm::mat4& scale);

    glm::fmat4 m_local = glm::fmat4(1.0f);
    glm::fmat4 m_world = glm::fmat4(1.0f);

    glm::vec3 m_translation;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
  };
}

#endif // TRANSFORM_H