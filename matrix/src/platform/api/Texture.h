#ifndef TEXTURE_H
#define TEXTURE_H

#include "stdafx.h"

#ifdef MX_OPENGL_ACTIVE
  #define MX_TEXTURE MX::Texture_OpenGL
#elif
  #define MX_TEXTURE MX::Texture_DirectX
#endif


namespace MX
{
  class Texture;

  enum TextureType
  {
    E_DIFFUSE, E_SPECULAR, E_NORMAL, E_BUMP, E_HEIGHT
  };

  struct MaterialProfile
  {
    glm::vec3 ambient = {1.0f, 1.0f, 1.0f};
    glm::vec3 diffuse = {1.0f, 1.0f, 1.0f};
    glm::vec3 specular = {1.0f, 1.0f, 1.0f};

    float shininess = 32.0f;
  };

  struct TextureProfile
  {
    std::shared_ptr<Texture> diffuse = nullptr;
    std::shared_ptr<Texture> specular = nullptr;
    std::shared_ptr<Texture> normal = nullptr;
    std::shared_ptr<Texture> bump = nullptr;
    std::shared_ptr<Texture> height = nullptr;
  };

  struct STB_Texture
  {
    int width = 0;
    int height = 0;
    int channels = 0;
  };

  class Texture
  {
  public:
    MX_API Texture() = delete;
    MX_API Texture(const std::string &path);

    MX_API virtual ~Texture() = default;

    MX_API Texture(const Texture&) = default;
    MX_API Texture &operator=(const Texture&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void use(int index = 0) const = 0;
    MX_API virtual void unbind() const = 0;

    MX_API virtual uint64_t getID() = 0;
    MX_API virtual Texture *get() { return this; }

  public:
    STB_Texture m_Stb;

    std::string m_Name;
    std::string m_path;
    std::string m_relative_path;
    std::string m_type = "texture_diffuse";

    bool m_initialized = 0;
  };
}

#endif // TEXTURE_H