#include <API_OpenGL.h>
#include <Application.h>

namespace MX
{
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

    glViewport(0, 0, 1400, 800);
    m_framebuffer.initialize();

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    MX_SUCCESS("MX: API: OpenGL: GLEW: Initialization");
    return true;
  }

  void API_OpenGL::update()
  {
    //clear();
    glViewport(0, 0, 1000, 500);

    glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_framebuffer.m_initialized)
    {
      m_framebuffer.bind();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void API_OpenGL::clear()
  {
    int screen_y = Application::get().m_Window->m_Props.m_Height;

  #ifdef MX_IMGUI_ACTIVE
    Window::WindowProps::ViewPort *app_viewport = &Application::get().m_Window->m_Props.m_Viewport;

    int viewport_x = app_viewport->m_Viewport_max_x;
    int viewport_y = app_viewport->m_Viewport_max_y;

    int corner_x = app_viewport->m_Viewport_min_x;
    int corner_y = app_viewport->m_Viewport_min_y;

    if (MX_WORLD.m_ActiveScene != nullptr)
      MX_WORLD.m_ActiveScene->m_Cam.setScreenDimensions(viewport_x, viewport_y);

    glViewport(corner_x,
               screen_y - corner_y,
               viewport_x,
               viewport_y);

    static bool waiting_for_framebuffer = 1;
    static size_t counter = 0;

    if (waiting_for_framebuffer)
      ++counter;

    if (counter > 10 && !m_framebuffer.m_initialized)
    {
      waiting_for_framebuffer = 0;
      m_framebuffer.initialize();
    }

    //std::cout << "Screen_y: " << screen_y << ", corner_y: " << corner_y << std::endl;
    //std::cout << corner_x << ", " << screen_y - corner_y << ", " << viewport_x << ", " << viewport_y << std::endl;

    // m_framebuffer.resize(viewport_x, viewport_y);

  #else
    if (MX_WORLD.m_ActiveScene != nullptr)
      MX_WORLD.m_ActiveScene->m_Cam.setScreenDimensions(1000, 500);

    int screen_x = Application::get().m_Window->m_Props.m_Width;
    glViewport(0, 20, 1000, 500);
  #endif
  }

  void API_OpenGL::render()
  {
    if (m_framebuffer.m_initialized)
    {
      m_framebuffer.unbind();
      glViewport(0, 20, 1000, 500);
      m_framebuffer.render();
    }
  }
}
