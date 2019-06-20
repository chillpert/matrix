#ifndef MODEL_H
#define MODEL_H

#include <stdafx.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Mesh.h>
#include <Mesh_OpenGL.h>
#include <Shader.h>
#include <Shader_OpenGL.h>

#ifdef MX_OPENGL_ACTIVE
  #define MX_MESH Mesh_OpenGL
#elif MX_DIRECTX_ACTIVE
  #define MX_MESH Mesh_DirectX
#endif

namespace MX {

  class Model
  {
  public:
    MX_API Model() = delete;
    MX_API Model(const std::string &path, bool instant_init = 0, bool gamma = 0);
    MX_API ~Model() = default;

    MX_API Model(const Model&) = default;
    MX_API Model &operator=(const Model&) = default;

    MX_API void initialize();
    MX_API void render(std::shared_ptr<MX_SHADER> shader);

  private:
    MX_API void process_node(aiNode *node, const aiScene *scene);
    MX_API MX_MESH process_mesh(aiMesh *mesh, const aiScene *scene);

    MX_API std::vector<Assimp_Texture> load_material_texture(aiMaterial *mat, aiTextureType type, std::string typeName);

  public:
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Assimp_Texture> textures_loaded;

    std::vector<MX_MESH> m_meshes;
    std::vector<MX_TEXTURE> m_textures;
    std::string m_directory;
    std::string m_full_path;
    std::string m_name;
    bool m_initialized;
    bool m_gamma_correction;
  };
}

#endif // MODEL_H
