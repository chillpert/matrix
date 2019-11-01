#include "Mesh_OpenGL.h"

namespace MX
{
  Mesh_OpenGL::Mesh_OpenGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures)
    : Mesh(vertices, indices, textures)
  {
    initialize();
  }

  void Mesh_OpenGL::initialize()
  {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

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

  void Mesh_OpenGL::render_mesh(std::shared_ptr<Shader> shader)
  {
    u_int64_t diffuse_nr = 1;
    u_int64_t specular_nr = 1;
    u_int64_t normal_nr = 1;
    u_int64_t height_nr = 1;

    for (u_int64_t i = 0; i < m_textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);

      std::shared_ptr<MX_TEXTURE> temp_texture = std::static_pointer_cast<MX_TEXTURE>(m_textures.at(i));
      std::shared_ptr<MX_SHADER> temp_shader = std::static_pointer_cast<MX_SHADER>(shader);

      std::string number;
      std::string name = temp_texture->m_type;

      if(name == "texture_diffuse")
        number = std::to_string(diffuse_nr++);
      else if(name == "texture_specular")
        number = std::to_string(specular_nr++);
      else if(name == "texture_normal")
        number = std::to_string(normal_nr++);
      else if(name == "texture_height")
        number = std::to_string(height_nr++);
      
      glUniform1i(glGetUniformLocation(temp_shader->m_ID, (name + number).c_str()), i);
      glBindTexture(GL_TEXTURE_2D, temp_texture->m_ID);
    }

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
  }
}