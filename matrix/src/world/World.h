#ifndef WORLD_H
#define WORLD_H

#define MX_GET_SHADER(path) MX::MX_WORLD.getShader(path)
#define MX_GET_MODEL(path) MX::MX_WORLD.getModel(path)
#define MX_GET_TEXTURE(path, type) MX::MX_WORLD.getTexture(path, type)

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

    MX_API World &operator=(const World&) = default;

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    MX_API void push(std::shared_ptr<Scene> scene, bool consider_local_files = false, bool instant_save = false);
    MX_API void pop(const std::string &name);

    MX_API std::shared_ptr<Model> getModel(const std::string& path);
    MX_API std::shared_ptr<Shader> getShader(const std::string& path);
    MX_API std::shared_ptr<Texture> getTexture(const std::string& path, const std::string& type);

    MX_API std::shared_ptr<Scene> getScene(const std::string& name);
    
    MX_API bool load_scene(const std::string &name);
    MX_API bool rename_scene(const std::string old_path, const std::string& new_path);

    MX_API bool remove_scene_file(const std::string& path);
    MX_API bool remove_scene(const std::string &name);
    MX_API bool remove_scene(const std::shared_ptr<Scene> scene);

  private:
    MX_API World(const World&) = delete;

  public:
    std::shared_ptr<Scene> m_ActiveScene;
    std::vector<std::shared_ptr<Scene>> m_ExistingScenes;
  
    std::vector<std::shared_ptr<Model>> m_models;
    std::vector<std::shared_ptr<Shader>> m_shaders;
    std::vector<std::shared_ptr<Texture>> m_textures;

    /*
    std::vector<std::shared_ptr<Texture>> m_diffuse_maps;
    std::vector<std::shared_ptr<Texture>> m_specular_maps;
    std::vector<std::shared_ptr<Texture>> m_normal_maps;
    std::vector<std::shared_ptr<Texture>> m_bump_maps;
    std::vector<std::shared_ptr<Texture>> m_height_maps;
    std::vector<std::shared_ptr<Texture>> m_displacement_maps;
    */
  };
}

#endif // WORLD_H