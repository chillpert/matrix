#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  enum Trans
  {
    FORWARDS, LEFT, BACKWARDS, RIGHT, DOWN, UP, 
    X, Y, Z, XYZ,
    SCALE_GROW, SCALE_SHRINK
  };

  struct Transform_Props
  {
    Trans t;
    float factor;
    bool isAnimated = 0;
  };

  class Transform
  {
  public:
    Transform();
    ~Transform();

    void update_transform();
    glm::fmat4 update();

    void push_animation(Trans t, float factor);
    void push_translation(Trans t, float factor);

    float getTime();

    glm::fmat4 m_Local = glm::fmat4(1.0f);
    glm::fmat4 m_World = glm::fmat4(1.0f);

    std::vector<Transform_Props> m_Animations;
    std::vector<Transform_Props> m_Transforms;
  };
}

#endif // TRANSFORM_H