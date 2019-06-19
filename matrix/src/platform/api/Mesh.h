#ifndef MESH_H
#define MESH_H

#include <stdafx.h>

#include <Shader.h>
#include <Shader_OpenGL.h>

namespace MX
{
  struct Vertex
  {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
  };

  struct Assimp_Texture
  {
    unsigned int id;
    std::string type;
    std::string path;
  };

  class Mesh
  {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Assimp_Texture> textures);
    ~Mesh() = default;

    Mesh(const Mesh&) = default;
    Mesh &operator=(const Mesh&) = default;

    void initialize();
    void render_mesh(MX_SHADER shader);

  public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Assimp_Texture> m_textures;
    unsigned int m_vao;

  private:
    unsigned int m_vbo, m_ebo;
  };
}

#endif // MESH_H

