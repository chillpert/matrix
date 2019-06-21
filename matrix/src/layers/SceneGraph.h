#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <Node.h>
#include <ContainerNode.h>
#include <LightNode.h>
#include <ObjectNode.h>

namespace MX
{
  class SceneGraph
  {
  public:
    MX_API SceneGraph();
    MX_API ~SceneGraph();

    MX_API SceneGraph(const SceneGraph&) = default;
    MX_API SceneGraph &operator=(const SceneGraph&) = default;

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    MX_API std::shared_ptr<Node> search(const std::string &name, std::shared_ptr<Node> it);

    MX_API void getAllObjects(std::vector<std::string> *vec, std::shared_ptr<Node> it);
    MX_API void getAllObjects(std::vector<const char*> &vec, std::shared_ptr<Node> it);

  private:
    MX_API void recursive_render(Node &it, glm::fmat4 mat = glm::fmat4(1.0f));

  public:
    std::shared_ptr<Node> m_Root;

    std::vector<std::shared_ptr<ContainerNode>> m_container_nodes;
    std::vector<std::shared_ptr<ObjectNode>> m_object_nodes;
    std::vector<std::shared_ptr<LightNode>> m_light_nodes;
    bool is_paused = 0;
  };
}

#endif // SCENEGRAPH_HPP