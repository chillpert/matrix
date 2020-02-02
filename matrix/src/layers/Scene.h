#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "SceneGraph.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"

namespace MX
{
  class Scene
  {
  public:
    MX_API Scene() = delete;
    MX_API Scene(const std::string &name);
    MX_API ~Scene();

    MX_API Scene(const Scene&) = default;
    MX_API Scene &operator=(const Scene&) = default;

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    // return 1 if name is unique, searches the entire scene's scenegraph
    MX_API bool addItemEntry(const std::string &name);

    // push arbitrary node
    MX_API bool push(std::shared_ptr<Node> node, std::shared_ptr<Node> node_to_attach_to);
    
    // add containers
    MX_API bool push_container(const std::string &name, const std::string &node_to_attach_to = default_root_name);

    // add objects
    MX_API bool push_object(const std::string &name, const std::string &node_to_attach_to= default_root_name);
    MX_API bool push_object(
      const std::string &name,
      std::shared_ptr<Model> model,
      std::shared_ptr<Shader> shader,
      const std::string &node_to_attach_to = default_root_name
    );
    MX_API bool push_object_with_diffuse_texture(
      const std::string &name,
      std::shared_ptr<Model> model,
      std::shared_ptr<Shader> shader,
      std::shared_ptr<Texture> texture,
      const std::string &node_to_attach_to = default_root_name
    );
    MX_API bool push_object_with_texture_profile(
      const std::string &name,
      std::shared_ptr<Model> model,
      std::shared_ptr<Shader> shader,
      const TextureProfile &texture_profile,
      const std::string &node_to_attach_to = default_root_name
    );
    MX_API bool push_object_with_material_profile(
      const std::string &name,
      std::shared_ptr<Model> model,
      std::shared_ptr<Shader> shader,
      const MaterialProfile &material_profile,
      const std::string &node_to_attach_to = default_root_name
    );
    MX_API bool push_object_with_material_and_texture_profile(
      const std::string &name,
      std::shared_ptr<Model> model,
      std::shared_ptr<Shader> shader,
      const MaterialProfile &material_profile,
      const TextureProfile &texture_profile,
      const std::string &node_to_attach_to = default_root_name
    );

    // add light sources
    MX_API bool push_directional_light(const std::string &name, const std::string &node_to_attach_to = default_root_name);
    MX_API bool push_point_light(const std::string &name, const std::string &node_to_attach_to = default_root_name);
    MX_API bool push_spot_light(const std::string &name, const std::string &node_to_attach_to = default_root_name);

    MX_API bool pop(const std::string& name);

    MX_API void save();
    MX_API void save_name();

  private:
    MX_API bool object_already_exists(const std::string& name);
    MX_API void rename(const std::string& name);

  public:
    Camera m_Cam;
    SceneGraph m_Sg;
    std::string m_Name;
    
    std::vector<std::string> m_ExistingObjects;
    std::map<std::string, std::shared_ptr<Node>> m_objects;
  };
}

#endif // SCENE_H