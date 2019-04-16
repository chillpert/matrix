#ifndef API_ERRORHANDLING_H
#define API_ERRORHANDLING_H

#include "matrix/src/pch/stdafx.h"

#ifdef MX_DEBUG
    #ifdef MX_OPENGL_ACTIVE 
        #define MX_API_ERROR glDebugMessageCallback(messageCallback, 0);

        namespace MX {
            void messageCallback(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar *message, const void *useParam);
        }

    #elif MX_DIRECTX_ACTIVE
        #define MX_API_ERROR DirectX_ErrorHandling

        namespace MX {

        }

    #endif
#else
    #define MX_API_ERROR
#endif

#endif // API_ERRORHANDLING_H