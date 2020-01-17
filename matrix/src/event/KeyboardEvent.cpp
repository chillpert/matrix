#include "KeyboardEvent.h"
#include "Controller.h"

namespace MX 
{
  KeyboardButtonEvent::KeyboardButtonEvent(int keycode)
    : m_keycode(keycode) { }

  void KeyboardButtonPressed::handle() 
  {
    int esc_KeyCode;
    esc_KeyCode = SDLK_ESCAPE;

    if (Controller::get().m_MouseHidden || m_keycode == esc_KeyCode)
      Controller::get().handleKeyPressed(m_keycode);
  }

  KeyboardButtonPressed::KeyboardButtonPressed(int keycode, int repeat_count)
    : KeyboardButtonEvent(keycode), m_repeat_count(repeat_count) { }

  std::string KeyboardButtonPressed::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: KeyboardButtonPressed: " << std::to_string(m_keycode) << " (repeat count: " << m_repeat_count << ")";
    return ss.str();
  }

  KeyboardButtonReleased::KeyboardButtonReleased(int keycode)
    : KeyboardButtonEvent(keycode) { }

  void KeyboardButtonReleased::handle() 
  {
    int esc_KeyCode;
    esc_KeyCode = SDLK_ESCAPE;

    if (Controller::get().m_MouseHidden || m_keycode == esc_KeyCode)
      Controller::get().handleKeyReleased(m_keycode);
  }

  std::string KeyboardButtonReleased::toString() const
  {
    std::stringstream ss;
    ss << "MX: Event: KeyboardButtonReleased: " << std::to_string(m_keycode);
    return ss.str();
  }
}