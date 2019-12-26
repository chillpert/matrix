#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include "Ray.h"

namespace MX
{
  class MousePicker
  {
  public:
    MX_API bool initialize();
    MX_API void update();
  
    Ray m_pick_ray;
    glm::vec3 ray_wor;
  };
}

#endif // MOUSEPICKER_H