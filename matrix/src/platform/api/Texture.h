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
  class Texture;

  struct Material
  {
    glm::vec3 ambient = {1.0f, 1.0f, 1.0f};
    glm::vec3 diffuse = {1.0f, 1.0f, 1.0f};
    glm::vec3 specular = {1.0f, 1.0f, 1.0f};

    float shininess = 32.0f;
  };

  struct TextureProfile
  {
    std::shared_ptr<Texture> diffuse = nullptr;
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
    MX_API Texture() = default;
    MX_API Texture(const std::string &name, const std::string &path = MX_TEXTURE_PATH);
    MX_API virtual ~Texture() = default;

    MX_API Texture(const Texture&) = default;
    MX_API Texture &operator=(const Texture&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void use() const = 0;
    MX_API virtual void unbind() const = 0;

    MX_API virtual u_int64_t getID() = 0;
    MX_API virtual Texture *get() { return this; }

  public:
    STB_Texture m_Stb;

    std::string m_Name;
    std::string m_path;
    std::string m_type = "texture_diffuse1";

    bool m_initialized = 0;
  };
}

#endif // TEXTURE_H