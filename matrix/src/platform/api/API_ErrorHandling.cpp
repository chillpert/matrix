#include <API_ErrorHandling.h>

namespace MX 
{

#ifdef MX_OPENGL_ACTIVE

  void messageCallback(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar *message, const void *useParam)
  {
    switch(severity)
    {
      // low
      case 0x9148:
        MX_INFO("MX: API: OpenGL: " + std::string(message));
        break;
      // medium
      case 0x9147:
        MX_WARN("MX: API: OpenGL: " + std::string(message));
        break;
      // high
      case 0x9146:
        MX_FATAL("MX: API: OpenGL: " + std::string(message));
        break;
      // unknown
      default: 
        MX_WARN("MX: API: OpenGL: " + std::string(message));
        break;
    }
  }

#elif MX_DIRECTX_ACTIVE

#endif

}