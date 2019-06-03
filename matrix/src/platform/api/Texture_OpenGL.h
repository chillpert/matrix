#ifndef TEXTURE_OPENGL_H
#define TEXTURE_OPENGL_H

#include "matrix/src/platform/api/Texture.h"

namespace MX
{
  class Texture_OpenGL : public Texture
  {
    public:
      MX_API Texture_OpenGL(const std::string &file_name);
      MX_API ~Texture_OpenGL();

      MX_API void create_texture();
      MX_API void load_texture();
      MX_API void use();

      MX_API void initialize() override;

    private:
      GLuint m_ID;
      std::string m_FileName;
  };
}

#endif // TEXTURE_OPENGL_H