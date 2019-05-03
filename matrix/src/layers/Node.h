#ifndef NODE_HPP
#define NODE_HPP

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  class Node 
  {
  public:
    Node(const std::string &node_name, const std::string &model_name = "")
      : m_Name(node_name), m_ModelName(model_name) {}
    ~Node() {}
    
    void addChild(Node* node); 
    Node* &getChild(const std::string &name);
    std::vector<Node*> &getChildren() { return m_Children; }

    void setParent(Node* node);
    Node* &getParent() { return m_Parent; }

    void setLocalTransform(const glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(const glm::fmat4& mat = glm::fmat4(1.0f));

    glm::fmat4 &getLocalTransform() { return m_LocalTransform; }
    glm::fmat4 &getWorldTransform() { return m_WorldTransform; }

    // scale object over vector and set scale speed
    void scale(const glm::fvec3 &vec, float speed);
    // rotate object over vector and set rotation speed
    void rotate(const glm::fvec3 &vec, float speed);
    // translate object over vector and set translation speed
    void translate(const glm::fvec3 &vec, float speed);

    void toString();

  private:
    glm::fmat4 m_LocalTransform = glm::fmat4(1.0f);
    glm::fmat4 m_WorldTransform = glm::fmat4(1.0f);

    Node* m_Parent;
    std::vector<Node*> m_Children;  

  public:
    std::string m_Name;
    std::string m_ModelName;

    // objects are not moving if speed is zero
    float scalingSpeed = 0.0f;
    float rotationSpeed = 0.0f;
    float translatingSpeed = 0.0f;
  };
}

#endif // NODE_HPP