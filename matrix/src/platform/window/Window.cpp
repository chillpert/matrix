#include "matrix/src/platform/window/Window.h"

namespace MX
{
  void Window::WindowProps::update_time()
  {
    float currentFrame = (float) m_Time;
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;
  }
}