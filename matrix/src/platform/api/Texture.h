#ifndef TEXTURE_H
#define TEXTURE_H

#include "matrix/src/pch/stdafx.h"

#ifdef MX_OPENGL_ACTIVE
  #define MX_TEXTURE MX::Texture_OpenGL
#elif
  #define MX_TEXTURE MX::Texture_DirectX
#endif


namespace MX
{
  struct STB_Texture
  {
    int width = 0;
    int height = 0;
    int channels = 0;
  };

  class Texture
  {
  public:
    MX_API Texture();
    MX_API ~Texture();

    MX_API virtual void initialize() = 0;

    MX_API const std::string &getName() const { return m_FileName; }
  
  private:

  protected:
    std::string m_FileName;
    STB_Texture stb;
  };
}

#endif // TEXTURE_H