#ifndef API_OPENGL_H
#define API_OPENGL_H

#include "API.h"
#include "Framebuffer_OpenGL.h"

namespace MX
{
  class API_OpenGL : public API
  {
  public:
    MX_API API_OpenGL() = default;

    MX_API bool initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clear() override;

  private:
    MX_API void initialize_framebuffer();
  };
}

#endif // API_OPENGL_H