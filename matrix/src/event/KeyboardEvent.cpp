#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX 
{
  void KeyboardButtonPressed::handle() 
  {
    int esc_KeyCode;
    #ifdef MX_SDL2_ACTIVE
      esc_KeyCode = SDLK_ESCAPE;
    #elif MX_GLFW_ACTIVE
      esc_KeyCode = GLFW_KEY_ESCAPE;
    #endif

    if (Controller::get().m_MouseHidden || m_KeyCode == esc_KeyCode)
      Controller::get().handleKeyPressed(m_KeyCode);
  }

  void KeyboardButtonReleased::handle() 
  {
    int esc_KeyCode;
    #ifdef MX_SDL2_ACTIVE
      esc_KeyCode = SDLK_ESCAPE;
    #elif MX_GLFW_ACTIVE
      esc_KeyCode = GLFW_KEY_ESCAPE;
    #endif

    if (Controller::get().m_MouseHidden || m_KeyCode == esc_KeyCode)
      Controller::get().handleKeyReleased(m_KeyCode);
  }
}