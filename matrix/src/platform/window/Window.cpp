#include "matrix/src/platform/window/Window.h"

namespace MX
{
  static int temp_frames = 0;
  static float previous_time = 0.0f;

  void Window::WindowProps::update_time()
  {
    float current_time = (float) m_Time;

    temp_frames++;
    if (current_time - previous_time >= 1.0f)
    {
      m_Frames = temp_frames;
      temp_frames = 0;
      previous_time = current_time;
    }

    m_DeltaTime = current_time - m_PreviousTime;
    m_PreviousTime = current_time;
  }
}