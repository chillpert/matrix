#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  enum Transform_Direction
  {
    FORWARDS, LEFT, BACKWARDS, RIGHT, DOWN, UP
  };

  enum Transform_Axis
  {
    X, Y, Z
  };

  class Transform
  {
  public:
    Transform();
    ~Transform();

    float getTime();

    void scale(float factor);
    void rotate(Transform_Axis axis, float factor);
    void translate(Transform_Direction, float factor);

    void animate_direction(Transform_Direction dir, float factor, bool never_stop = 1);
    void animate_rotation(Transform_Axis axis, float factor, bool never_stop = 1);

    glm::fmat4 m_LocalTransform = glm::fmat4(1.0f);
    glm::fmat4 m_WorldTransform = glm::fmat4(1.0f);

    bool isAnimated = 0;
    bool isTransformed = 0;
  };
}

#endif // TRANSFORM_H