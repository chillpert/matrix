#define STB_IMAGE_IMPLEMENTATION
#include "matrix/src/platform/api/Texture_OpenGL.h"

namespace MX
{
  Texture_OpenGL::Texture_OpenGL(const std::string &file_name, bool instant_init)
  {
    m_FileName = file_name;

    if (instant_init)
      initialize();
  }

  Texture_OpenGL::~Texture_OpenGL()
  {
    
  }

  void Texture_OpenGL::create_texture()
  {
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  void Texture_OpenGL::use()
  {
    glBindTexture(GL_TEXTURE_2D, m_ID);
  }

  void Texture_OpenGL::initialize()
  {
    create_texture();
    load_texture();
  }

  void Texture_OpenGL::load_texture()
  {
    unsigned char *data = stbi_load((MX_TEXTURE_PATH + m_FileName).c_str(), &stb.width, &stb.height, &stb.channels, 0);
    
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, stb.width, stb.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
      MX_FATAL("MX: Texture: OpenGL: Failed to load texture file");
  
    stbi_image_free(data);
  }
}