#ifndef API_ERRORHANDLING_H
#define API_ERRORHANDLING_H

#include <stdafx.h>

namespace MX 
{
#ifdef MX_DEBUG
  #ifdef MX_OPENGL_ACTIVE 
    #define MX_API_ERROR glDebugMessageCallback(messageCallback, 0);

      void messageCallback(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar *message, const void *useParam);
    
  #elif MX_DIRECTX_ACTIVE
    #define MX_API_ERROR DirectX_ErrorHandling

  #endif
#else
  #define MX_API_ERROR
#endif
}

#endif // API_ERRORHANDLING_H