#ifndef API_OPENGL_H
#define API_OPENGL_H

#include <API.h>

namespace MX
{
  class MX_API API_OpenGL : public API
  {
  public:
    API_OpenGL() {}
    ~API_OpenGL() {}

    bool initialize() const override;
    void update() const override;
    void render() const override;
    void clear() const override;
  };
}

#endif // API_OPENGL_H