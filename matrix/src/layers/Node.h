#ifndef NODE_HPP
#define NODE_HPP

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  class Node 
  {
  public:
    Node() {}
    Node(const std::string name)
      : m_Name(name) {}
    ~Node() {}
    
    void addChild(Node* node); 
    Node* &getChild(std::string aName);
    Node* &getAnyChild(std::string aName);

    void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    glm::fmat4 &getLocalTransform() { return m_LocalTransform; }
    glm::fmat4 &getWorldTransform() { return m_WorldTransform; }

    void toString();

  private:
    glm::fmat4 m_LocalTransform = glm::fmat4(1.0f);
    glm::fmat4 m_WorldTransform = glm::fmat4(1.0f);
  
  public:
    Node* m_Parent;
    std::vector<Node*> m_Children;
    std::string m_Name;
  };
}

#endif // NODE_HPP