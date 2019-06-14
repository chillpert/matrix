#ifndef TEXTURE_OPENGL_H
#define TEXTURE_OPENGL_H

#include "matrix/src/platform/api/Texture.h"

namespace MX
{
  class Texture_OpenGL : public Texture
  {
    public:
      MX_API Texture_OpenGL(const std::string &file_name, bool instant_init = 0);
      MX_API virtual ~Texture_OpenGL();

      MX_API void create_texture();
      MX_API void load_texture();
      MX_API void use();

      MX_API void initialize() override;

    private:
      GLuint m_ID;
      
  };
}

#endif // TEXTURE_OPENGL_H