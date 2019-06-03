#ifndef TEXTURE_H
#define TEXTURE_H

#include "matrix/src/pch/stdafx.h"

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
  
  private:

  protected:
    STB_Texture stb;
  };
}

#endif // TEXTURE_H