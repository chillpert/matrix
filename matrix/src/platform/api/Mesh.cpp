#include <Mesh.h>

namespace MX
{
  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Assimp_Texture> textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures)
  {
    initialize();
  }

  void Mesh::render_mesh(MX_SHADER shader) 
  {
    // bind appropriate textures
    u_int64_t diffuse_nr = 1;
    u_int64_t specular_nr = 1;
    u_int64_t normal_nr = 1;
    u_int64_t height_nr = 1;

    for (u_int64_t i = 0; i < m_textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
      // retrieve texture number (the N in diffuse_textureN)
      std::string number;
      std::string name = m_textures[i].type;

      if(name == "texture_diffuse")
        number = std::to_string(diffuse_nr++);
      else if(name == "texture_specular")
        number = std::to_string(specular_nr++);
      else if(name == "texture_normal")
        number = std::to_string(normal_nr++);
      else if(name == "texture_height")
        number = std::to_string(height_nr++);

      // now set the sampler to the correct texture unit
      glUniform1i(glGetUniformLocation(shader.m_ID, (name + number).c_str()), i);
      // and finally bind the texture
      glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // draw mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
  }

  void Mesh::initialize()
  {
    // create buffers/arrays
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tex_coords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, bitangent));

    glBindVertexArray(0);
  }

}