#include "WindowEvent.h"
#include "Controller.h"

namespace MX 
{
  WindowResized::WindowResized(unsigned int width, unsigned int height)
    : m_width(width), m_height(height) { }

  void WindowResized::handle()
  {
    Controller::get().handleResizeWindow(m_width, m_height);
  }

  std::string WindowResized::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: WindowResized: " << std::to_string(m_width) << ", " << std::to_string(m_height);
    return ss.str();
  }

  void WindowClosed::handle()
  {
    Controller::get().handleCloseWindow();
  }

  std::string WindowClosed::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: WindowClosed";
    return ss.str();
  }
}