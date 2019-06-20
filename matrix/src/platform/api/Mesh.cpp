#include <Mesh.h>

namespace MX
{
  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Assimp_Texture> textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures) { }
}