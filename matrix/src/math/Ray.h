#ifndef RAY_H
#define RAY_H

#include "pch/stdafx.h"

namespace MX
{
  struct Ray
  {
    glm::vec3 m_origin{ 0.0f, 0.0f, 0.0f };
    glm::vec3 m_direction{ 0.0f, 0.0f, -1.0f };
  };
}

#endif // RAY_H