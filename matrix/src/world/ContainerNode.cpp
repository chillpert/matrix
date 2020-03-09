#include "ContainerNode.h"

namespace MX
{
  ContainerNode::ContainerNode(const std::string &name)
    : Node(name, NodeType::type_container) { }

  std::string ContainerNode::to_string() const
  {
    std::stringstream ss;
    ss << Node::to_string();

    return ss.str();
  }
}