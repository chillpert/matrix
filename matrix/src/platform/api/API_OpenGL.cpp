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
    glViewport(0, 0, Application::get().m_Window->m_Props.m_Width, Application::get().m_Window->m_Props.m_Height);
    glClearColor(0.0f, 0.1f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}
