#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include "Mesh.h"
#include "Mesh_OpenGL.h"
#include "Shader.h"
#include "Shader_OpenGL.h"
#include "Texture.h"
#include "Texture_OpenGL.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef MX_OPENGL_ACTIVE
  #define MX_MESH Mesh_OpenGL
#elif MX_DIRECTX_ACTIVE
  #define MX_MESH Mesh_DirectX
#endif

namespace MX
{
  class Model
  {
  public:
    MX_API Model() = delete;
    MX_API Model(const std::string &path, bool instant_init = 0, bool gamma = 0);
    MX_API ~Model() = default;

    MX_API Model(const Model&) = default;
    MX_API Model &operator=(const Model&) = default;

    MX_API void initialize();
    MX_API void render(std::shared_ptr<Shader> shader);

  private:
    MX_API void process_node(aiNode *node, const aiScene *scene);
    MX_API std::shared_ptr<Mesh> process_mesh(aiMesh *mesh, const aiScene *scene);

    MX_API std::vector<std::shared_ptr<Texture>> load_material_texture(aiMaterial *mat, aiTextureType type, std::string typeName);

  public:
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<std::shared_ptr<Texture>> textures_loaded;
    std::vector<std::shared_ptr<Mesh>> m_meshes;

    std::string m_directory;
    std::string m_full_path;
    std::string m_relative_path;
    std::string m_name;
    bool m_gamma_correction;
    bool m_initialized = 0;
  };
}

#endif // MODEL_H
