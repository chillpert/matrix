#define STB_IMAGE_IMPLEMENTATION
#include "Texture_OpenGL.h"

namespace MX
{
  Texture_OpenGL::Texture_OpenGL(const std::string &path, bool instant_init)
    : Texture(path)
  {
    if (instant_init)
      initialize();
  }

  Texture_OpenGL::~Texture_OpenGL()
  {
    if (m_initialized)
      glDeleteTextures(1, &m_ID);
  }

  void Texture_OpenGL::use(int index) const
  {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_ID);
  }

  void Texture_OpenGL::unbind() const
  {
    glBindTexture(m_ID, 0);
  }

  void Texture_OpenGL::initialize()
  {
    unsigned char *data = stbi_load(m_path.c_str(), &m_Stb.width, &m_Stb.height, &m_Stb.channels, 0);

    glGenTextures(1, &m_ID);

    if (data)
    {
      GLenum format;
      if (m_Stb.channels == 1)
        format = GL_RED;
      else if (m_Stb.channels == 3)
        format = GL_RGB;
      else if (m_Stb.channels == 4)
        format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, m_ID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, m_Stb.width, m_Stb.height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      // set the texture wrapping parameters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      
      // set texture filtering parameters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      m_initialized = 1;
    }
    else
      MX_FATAL("MX: Texture: OpenGL: Failed to load texture file: " + m_Name);

    stbi_image_free(data);
  }
}