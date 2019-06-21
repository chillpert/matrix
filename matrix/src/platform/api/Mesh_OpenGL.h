#ifndef MESH_OPENGL_H
#define MESH_OPENGL_H

#include <Mesh.h>

namespace MX
{
  class Mesh_OpenGL : public Mesh
  {
  public:
    MX_API Mesh_OpenGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
    MX_API ~Mesh_OpenGL() = default;

    MX_API Mesh_OpenGL(const Mesh_OpenGL&) = default;
    MX_API Mesh_OpenGL &operator=(const Mesh_OpenGL&) = default;
 
    MX_API void initialize() override;
    MX_API void render_mesh(std::shared_ptr<MX_SHADER> shader) override;
  };
}

#endif // MESH_OPENGL_H