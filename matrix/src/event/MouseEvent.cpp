#include "matrix/src/event/MouseEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX 
{

  void MouseButtonPressed::handle()
  {
    Controller::get().handleMousePressed(m_KeyCode);
  }

  void MouseButtonReleased::handle()
  {
    Controller::get().handleMouseReleased(m_KeyCode);
  }

  void MouseMoved::handle()
  {
    if (Controller::get().m_MouseHidden)
      Controller::get().handleMouseMoved(m_X, m_Y);
  }

  void MouseScrolled::handle()
  {
    Controller::get().handleMouseScrolled(m_Xaxis, m_Yaxis);
  }
}