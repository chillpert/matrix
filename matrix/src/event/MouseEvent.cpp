#include "MouseEvent.h"
#include "Controller.h"

namespace MX 
{
  MouseMoved::MouseMoved(float x, float y)
    : m_mouse_x(x), m_mouse_y(y) { }

  void MouseMoved::handle()
  {
    if (Controller::get().m_MouseHidden)
      Controller::get().handleMouseMoved(static_cast<int>(m_mouse_x), static_cast<int>(m_mouse_y));
  }

  std::string MouseMoved::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: MouseMoved: " << std::to_string(m_mouse_x) << ", " << std::to_string(m_mouse_y);
    return ss.str();
  }

  MouseScrolled::MouseScrolled(float offset_x, float offset_y)
    : m_offset_x(offset_x), m_offset_y(offset_y) { }

  void MouseScrolled::handle()
  {
    Controller::get().handleMouseScrolled(static_cast<int>(m_offset_x), static_cast<int>(m_offset_y));
  }

  std::string MouseScrolled::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: MouseMoved: " << std::to_string(m_offset_x) << ", " << std::to_string(m_offset_y);
    return ss.str();
  }

  MouseButtonEvent::MouseButtonEvent(int button)
    : m_button(button) { }

  MouseButtonPressed::MouseButtonPressed(int button)
    : MouseButtonEvent(button) { }

  void MouseButtonPressed::handle()
  {
    Controller::get().handleMousePressed(m_button);
  }

  std::string MouseButtonPressed::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: MouseButtonPressed: " << std::to_string(m_button);
    return ss.str();
  }

  MouseButtonReleased::MouseButtonReleased(int button)
    : MouseButtonEvent(button) { }

  void MouseButtonReleased::handle()
  {
    Controller::get().handleMouseReleased(m_button);
  }

  std::string MouseButtonReleased::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: MouseButtonReleased: " << std::to_string(m_button);
    return ss.str();
  }
}