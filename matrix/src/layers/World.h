#ifndef WORLD_H
#define WORLD_H

#define MX_GET_SHADER(name) MX::MX_WORLD.getShader(name)
#define MX_GET_MODEL(name) MX::MX_WORLD.getModel(name)
#define MX_GET_TEXTURE(name) MX::MX_WORLD.getTexture(name)
#define MX_GET_TEXTURE_PROFILE(diffuse, normal, bump, height) MX::MX_WORLD.getTextureProfile(diffuse, normal, bump, height)

#include "stdafx.h"
#include "Scene.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"

namespace MX
{
  class World
  {
  public:
    MX_API World() = default;
    MX_API ~World();

    MX_API static World &get_default_world();

    MX_API World &operator=(const World&) = default;

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    MX_API void push(std::shared_ptr<Scene> scene);
    MX_API void pop(const std::string &name);

    MX_API std::shared_ptr<Model> getModel(const std::string &name) const;
    MX_API std::shared_ptr<Shader> getShader(const std::string &name) const;
    MX_API std::shared_ptr<Texture> getTexture(const std::string &name) const;
    
    MX_API std::shared_ptr<Model> getModelByPath(const std::string& path) const;
    MX_API std::shared_ptr<Shader> getShaderByPath(const std::string& path) const;
    MX_API std::shared_ptr<Texture> getTextureByPath(const std::string& path) const;

    MX_API bool load_scene(const std::string &name);

  private:
    MX_API World(const World&) = delete;

  public:
    std::shared_ptr<Scene> m_ActiveScene;
    std::vector<std::shared_ptr<Scene>> m_ExistingScenes;
  
    std::vector<std::shared_ptr<Model>> m_Models;
    std::vector<std::shared_ptr<Shader>> m_Shaders;

    std::vector<std::shared_ptr<Texture>> m_diffuse_maps;
    std::vector<std::shared_ptr<Texture>> m_specular_maps;
    std::vector<std::shared_ptr<Texture>> m_normal_maps;
    std::vector<std::shared_ptr<Texture>> m_bump_maps;
    std::vector<std::shared_ptr<Texture>> m_height_maps;
    std::vector<std::shared_ptr<Texture>> m_displacement_maps;
  };
}

#endif // WORLD_H