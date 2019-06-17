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
    MX_API Texture(const std::string &file_name);
    MX_API virtual ~Texture() = default;

    MX_API Texture(const Texture&) = default;
    MX_API Texture &operator=(const Texture&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void use() const = 0;

    MX_API const std::string &getName() const { return m_FileName; }

  protected:
    MX_API virtual void create() = 0;
    MX_API virtual void load() = 0;

    std::string m_FileName;
    STB_Texture m_Stb;
  };
}

#endif // TEXTURE_H