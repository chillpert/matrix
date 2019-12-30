#ifndef TEXTURE_OPENGL_H
#define TEXTURE_OPENGL_H

#include "Texture.h"

namespace MX
{
  class Texture_OpenGL : public Texture
  {
  public:
    MX_API Texture_OpenGL() = delete;
    MX_API Texture_OpenGL(const std::string &path, bool instant_init = false);

    MX_API ~Texture_OpenGL();

    MX_API Texture_OpenGL(const Texture_OpenGL&) = default;
    MX_API Texture_OpenGL &operator=(const Texture_OpenGL&) = default;
    
    MX_API void initialize() override;
    MX_API void use(int index = 0) const override;
    MX_API void unbind() const override;

    MX_API u_int64_t getID() { return static_cast<u_int64_t>(m_ID); }
    MX_API Texture_OpenGL *get() { return this; }

  public:
    GLuint m_ID;
  };
}

#endif // TEXTURE_OPENGL_H