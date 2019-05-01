#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "matrix/src/layers/Node.h"

namespace MX
{
  class SceneGraph
  {
  public:
    SceneGraph() {}
    ~SceneGraph() {}

    void render(Node& it, glm::fmat4& mat);

    std::string m_Name;
  };
}

#endif // SCENEGRAPH_H