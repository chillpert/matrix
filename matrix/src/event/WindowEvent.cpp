#include "matrix/src/Event/WindowEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX 
{
  void WindowClosed::handle()
  {
    Controller::get().handleCloseWindow();
  }

  void WindowResized::handle()
  {
    Controller::get().handleResizeWindow(m_Width, m_Height);
  }
}