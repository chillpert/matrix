#ifndef FRAMEBUFFER_OPENGL_H
#define FRAMEBUFFER_OPENGL_H

#include <Framebuffer.h>

namespace MX
{
  class Framebuffer_OpenGL : public Framebuffer
  {
  public:
    MX_API Framebuffer_OpenGL(bool instant_init);

    MX_API bool initialize() override;
    MX_API void update() override;
    MX_API void render() override;
  };
}

#endif // FRAMEBUFFER_OPENGL_H