#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "matrix/src/layers/Node.h"

namespace MX
{
  class SceneGraph
  {
  public:
    MX_API SceneGraph();
    MX_API ~SceneGraph();

    MX_API void initialize();
    MX_API void update();
    MX_API void render();
    
    MX_API void recursive_search(const std::string &name, Node *it);
    MX_API Node *search(const std::string &name, Node *it);
    MX_API void recursive_delete(Node *it);
    MX_API void iterative_delete(const std::string &name);
    MX_API void getAllObjects(std::vector<std::string> *vec, Node *it);

  private:
    MX_API void recursive_render(Node &it, glm::fmat4 mat = glm::fmat4(1.0f));

  public:
    Node *m_Root = new Node("root");
  };

  extern Node *search_holder;
}

#endif // SCENEGRAPH_HPP