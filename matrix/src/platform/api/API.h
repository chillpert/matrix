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
  class MX_API API
  {
  public:
    API() = default;
    virtual ~API() = default;

    API(const API&) = default;
    API &operator=(const API&) = default;

    virtual bool initialize() { return false; }
    virtual void update() {}
    virtual void render() {}
    virtual void clear() {}

    int m_test;
    MX_FRAMEBUFFER m_framebuffer;
  };
}

#endif // API_H