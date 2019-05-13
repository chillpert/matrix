#include "matrix/src/layers/SceneGraph.h"

namespace MX
{
  void SceneGraph::render()
  {    
    recursive_render(*m_Root);
  }

  void SceneGraph::recursive_render(Node &it, glm::fmat4 mat)
  {  
    it.setWorldTransform(mat);
    
    for (auto &model : m_Models) 
    {
      if (model.getName() == it.m_ModelName)
      {
        m_Shader.setfMat4("model", it.getWorldTransform());
        model.draw();
      }
    }

    if (!it.getChildren().empty())
    {
      for (Node* itChild : it.getChildren())
      {
        Node ptr = *itChild;
        recursive_render(*itChild, it.getWorldTransform());
      }
    }
    else
    {
      // MX_INFO_LOG("MX: Scene Graph: Recursive Render: " + it.m_Name + " does not have any children");
    }
  }
}