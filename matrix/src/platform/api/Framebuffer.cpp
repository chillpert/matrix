#include <Framebuffer.h>
#include <Application.h>

namespace MX
{
  void Framebuffer::reset_settings()
  {
    m_inversed_color = 0;
    m_depth_map = 0;
  }
}