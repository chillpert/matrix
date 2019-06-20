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
    MX_API Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Assimp_Texture> textures);
    MX_API virtual ~Mesh() = default;

    MX_API Mesh(const Mesh&) = default;
    MX_API Mesh &operator=(const Mesh&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void render_mesh(std::shared_ptr<MX_SHADER> shader) = 0;

  protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Assimp_Texture> m_textures;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
  };
}

#endif // MESH_H