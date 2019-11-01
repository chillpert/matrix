#ifndef API_OPENGL_H
#define API_OPENGL_H

#include "API.h"
#include "Framebuffer_OpenGL.h"

namespace MX
{
  class MX_API API_OpenGL : public API
  {
  public:
    API_OpenGL() = default;

    bool initialize() override;
    void update() override;
    void render() override;
    void clear() override;

  private:
    void initialize_framebuffer();
  };
}

#endif // API_OPENGL_H