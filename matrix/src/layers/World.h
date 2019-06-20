#ifndef WORLD_H
#define WORLD_H

#define MX_GET_SHADER(name) MX::MX_WORLD.getShader(name)
#define MX_GET_MODEL(name) MX::MX_WORLD.getModel(name)
#define MX_GET_TEXTURE(name) MX::MX_WORLD.getTexture(name)

#include <stdafx.h>
#include <Scene.h>
#include <Shader.h>
#include <Assimp_Model.h>
#include <Texture.h>

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

    MX_API std::shared_ptr<Assimp_Model> getModel(const std::string &name) const;
    MX_API std::shared_ptr<MX_SHADER> getShader(const std::string &name) const;
    MX_API std::shared_ptr<MX_TEXTURE> getTexture(const std::string &name) const;

  private:
    MX_API World(const World&) = delete;

  public:
    std::shared_ptr<Scene> m_ActiveScene;
    std::vector<std::shared_ptr<Scene>> m_ExistingScenes;
  
    std::vector<std::shared_ptr<Assimp_Model>> m_Models;
    std::vector<std::shared_ptr<Shader>> m_Shaders;
    std::vector<std::shared_ptr<Texture>> m_Textures;
  };
}

#endif // WORLD_H