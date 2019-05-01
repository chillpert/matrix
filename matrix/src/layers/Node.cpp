#include "matrix/src/layers/Node.h"

namespace MX
{
  Node* &Node::getChild(std::string aName)
  {
    int size = m_Children.size();

    for (unsigned int i = 0; i < size; i++)
    {
      if (m_Children.at(i)->m_Name == aName)
      {
        return m_Children.at(i);
      } 
    }

    std::cerr << aName + " is not a child of " + m_Name << std::endl;
    throw std::exception();
  }

  void Node::setLocalTransform(const glm::fmat4& mat)
  {  
    m_LocalTransform = mat * m_LocalTransform; 
  }

  void Node::setWorldTransform(const glm::fmat4& mat)
  {
    glm::fmat4 trans = glm::fmat4(1.0f);
    m_WorldTransform = mat * m_LocalTransform * trans;
  }

}