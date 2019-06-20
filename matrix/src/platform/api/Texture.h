#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdafx.h>

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
    MX_API Texture(const std::string &name);
    MX_API virtual ~Texture() = default;

    MX_API Texture(const Texture&) = default;
    MX_API Texture &operator=(const Texture&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void use() const = 0;

    MX_API const std::string &getName() const { return m_Name; }
    MX_API virtual u_int64_t getID() = 0;

  public:
    STB_Texture m_Stb;
    std::string m_Name;
    std::string m_path;

    bool m_initialized = 0;
  };
}

#endif // TEXTURE_H