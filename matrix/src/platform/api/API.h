#ifndef API_H
#define API_H

#ifdef MX_OPENGL_ACTIVE
  #define MX_API_TYPE API_OpenGL
#elif MX_DIRECTX_ACTIVE
  #define MX_API_TYPE API_DirectX
#else
  #error "Matrix Framework only supports OpenGL and DirectX for now"
#endif

#include "stdafx.h"

#include "Framebuffer.h"
#include "Framebuffer_OpenGL.h"

namespace MX
{
  class API
  {
  public:
    MX_API API() = default;
    MX_API virtual ~API() = default;

    MX_API API(const API&) = default;
    MX_API API &operator=(const API&) = default;

    MX_API virtual bool initialize() { return false; }
    MX_API virtual void update() {}
    MX_API virtual void render() {}
    MX_API virtual void clear() {}

    int m_test;
    MX_FRAMEBUFFER m_framebuffer;
  };
}

#endif // API_H