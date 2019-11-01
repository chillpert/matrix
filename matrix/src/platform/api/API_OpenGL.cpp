#include "API_OpenGL.h"
#include "Application.h"

namespace MX
{
  Window::WindowProps *window;

  static bool waiting_for_framebuffer = 1;
  static size_t counter = 0;

  void API_OpenGL::initialize_framebuffer()
  {
    waiting_for_framebuffer = 0;
    glViewport(0, 0, window->m_Width, window->m_Height);

    if (m_framebuffer.m_needs_refresh && m_framebuffer.m_initialized)
    {
      m_framebuffer.m_needs_refresh = 0;
      m_framebuffer.refresh();
    }
    else
      m_framebuffer.initialize();
  }

  bool API_OpenGL::initialize()
  {
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
      MX_FATAL("MX: API: OpenGL: GLEW: Initialization");
      return false;
    }

    MX_API_ERROR;

    window = &Application::get().m_Window->m_Props;

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    MX_SUCCESS("MX: API: OpenGL: GLEW: Initialization");
    return true;
  }

  void API_OpenGL::update()
  {
    int viewport_x = window->m_Viewport.m_Viewport_max_x;
    int viewport_y = window->m_Viewport.m_Viewport_max_y;

    if (MX_WORLD.m_ActiveScene != nullptr)
      MX_WORLD.m_ActiveScene->m_Cam.setScreenDimensions(viewport_x, viewport_y);

    if (m_framebuffer.m_is_active)
      glViewport(0, 0, viewport_x, viewport_y);
    else
    {
      glViewport(
        window->m_Viewport.m_Viewport_min_x,
        window->m_Viewport.m_Viewport_min_y,
        viewport_x,
        viewport_y
      );
    }

    // view port needs to be set according to GUI window size, therefore wait until assignments
    if (waiting_for_framebuffer)
      ++counter;

    if (m_framebuffer.m_needs_refresh || (viewport_x != initial_window_width && !m_framebuffer.m_initialized))
      initialize_framebuffer();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    clear();

    if (m_framebuffer.m_initialized)
      m_framebuffer.update();

    if (m_framebuffer.m_initialized && m_framebuffer.m_is_active)
    {
      m_framebuffer.bind();
      clear();
    }

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void API_OpenGL::clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void API_OpenGL::render()
  {
    if (m_framebuffer.m_initialized && m_framebuffer.m_is_active)
    {
      m_framebuffer.unbind();

      glViewport(
        window->m_Viewport.m_Viewport_min_x,
        window->m_Viewport.m_Viewport_min_y,
        window->m_Viewport.m_Viewport_max_x,
        window->m_Viewport.m_Viewport_max_y
      );
      m_framebuffer.render();
    }
  }
}
