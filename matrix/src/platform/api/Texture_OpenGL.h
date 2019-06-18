#ifndef TEXTURE_OPENGL_H
#define TEXTURE_OPENGL_H

#include "matrix/src/platform/api/Texture.h"

namespace MX
{
  class Texture_OpenGL : public Texture
  {
    public:
      MX_API Texture_OpenGL(const std::string &name, bool instant_init = 0);
      MX_API virtual ~Texture_OpenGL();

      MX_API Texture_OpenGL(const Texture_OpenGL&) = default;
      MX_API Texture_OpenGL &operator=(const Texture_OpenGL&) = default;
      
      MX_API void initialize() override;
      MX_API void use() const override;

      MX_API u_int64_t getID() { return static_cast<u_int64_t>(m_ID); }

    private:
      MX_API void create() override;
      MX_API void load() override;

    public:
      GLuint m_ID;
  };
}

#endif // TEXTURE_OPENGL_H