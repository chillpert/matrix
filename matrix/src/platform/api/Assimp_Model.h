#ifndef ASSIMP_MODEL_H
#define ASSIMP_MODEL_H

#include <stdafx.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Mesh.h>
#include <Shader.h>
#include <Shader_OpenGL.h>

namespace MX {

  class Assimp_Model
  {
  public:
    Assimp_Model() = delete;
    Assimp_Model(const std::string &path, bool gamma = false);
    ~Assimp_Model() = default;

    Assimp_Model(const Assimp_Model&) = default;
    Assimp_Model &operator=(const Assimp_Model&) = default;

    void render(MX_SHADER shader);

  private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void load_model(const std::string &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this 
    // process on its children nodes (if any).
    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Assimp_Texture> load_material_texture(aiMaterial *mat, aiTextureType type, std::string typeName);

  public:
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Assimp_Texture> textures_loaded;

    std::vector<Mesh> m_meshes;
    std::string m_directory;
    bool m_gamma_correction;
  };

}
#endif
