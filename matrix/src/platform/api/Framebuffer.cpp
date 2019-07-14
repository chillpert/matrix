#include <Framebuffer.h>
#include <Application.h>

namespace MX
{
  Framebuffer::Framebuffer(bool instant_init)
  {
    if (instant_init)
      if (initialize())
        m_initialized = 1;
  }

  bool Framebuffer::initialize()
  {
    bool success = 1;

    m_screen_shader->setPath("screen_buffer");
    m_screen_shader->initialize();

    m_quad = Application::get().m_World.getModel("quad.obj");

    if (m_quad != nullptr)
      m_quad->initialize();
    else
      success = 0;

    return success;
  }
}