#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stdafx.h"

namespace MX
{
  enum Trans
  {
    FORWARDS, LEFT, BACKWARDS, RIGHT, DOWN, UP, 
    X, Y, Z,
    SCALE
  };

  struct Transform_Props
  {
    Trans t;
    float factor;
    bool is_animated = 0;
  };

  class Transform
  {
  public:
    Transform() = default;
    ~Transform() = default;

    Transform(const Transform&) = default;
    Transform &operator=(const Transform&) = default;

    glm::fmat4 update();
    void push(const Trans &t, float factor, bool is_animated);
    float get_time() const;

  public:
    glm::fmat4 m_local = glm::fmat4(1.0f);
    glm::fmat4 m_world = glm::fmat4(1.0f);

    std::vector<Transform_Props> m_transforms;
    bool m_moving = 1;
  };
}

#endif // TRANSFORM_H