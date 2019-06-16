#include "matrix/src/platform/api/API_OpenGL.h"
#include "matrix/src/Application.h"

namespace MX
{
  bool API_OpenGL::initialize() const
  {
    glewExperimental = GL_TRUE; 
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
      MX_FATAL("MX: API: OpenGL: GLEW: Initialization");
      return false;
    } 
    else
    {
      MX_SUCCESS("MX: API: OpenGL: GLEW: Initialization");
      return true;
    }

    MX_API_ERROR;
  }

  void API_OpenGL::update() const
  {
    glEnable(GL_DEPTH_TEST);
  }

  void API_OpenGL::render() const
  {
  
  }

  void API_OpenGL::clear() const
  {
    Window::WindowProps::ViewPort *app_viewport = &Application::get().m_Window->m_Props.m_Viewport;

    int viewport_x = app_viewport->m_Viewport_max_x;
    int viewport_y = app_viewport->m_Viewport_max_y;

    int corner_x = app_viewport->m_Viewport_min_x;
    int corner_y = app_viewport->m_Viewport_min_y;

    int screen_y = Application::get().m_Window->m_Props.m_Height;

    World::get().m_ActiveScene->m_Cam.setScreenDimensions(viewport_x, viewport_y);

    glViewport(corner_x,
               screen_y - corner_y,
               viewport_x,
               viewport_y);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}
