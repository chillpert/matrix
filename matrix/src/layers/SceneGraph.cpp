#include "matrix/src/layers/SceneGraph.h"

namespace MX
{
  void SceneGraph::render(Node& it, glm::fmat4& mat) {    
    
    if (it.m_Name != this->m_Name) 
      it.setWorldTransform(mat);
  
    if (!it.m_Children.empty()) {

      for (Node* itChild : it.m_Children) {
        Node ptr = *itChild;
        render(*itChild, it.getWorldTransform());
      }
    }
  }

}