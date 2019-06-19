#include <WindowEvent.h>
#include <Controller.h>

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