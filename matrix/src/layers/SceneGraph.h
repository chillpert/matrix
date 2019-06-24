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
    MX_API void upload_lighting_unfiorms();
    MX_API void recursive_initialize(std::shared_ptr<Node> it);
    MX_API void recursive_render(std::shared_ptr<Node> it, glm::fmat4 mat = glm::fmat4(1.0f));

  public:
    std::shared_ptr<Node> m_Root;

    std::vector<std::shared_ptr<ContainerNode>> m_container_nodes;
    std::vector<std::shared_ptr<ObjectNode>> m_object_nodes;
    
    std::vector<std::shared_ptr<DirectionalLightNode>> m_directional_light_nodes;
    std::vector<std::shared_ptr<PointLightNode>> m_point_light_nodes;
    std::vector<std::shared_ptr<SpotLightNode>> m_spot_light_nodes;

    bool is_paused = 0;
  };
}

#endif // SCENEGRAPH_HPP