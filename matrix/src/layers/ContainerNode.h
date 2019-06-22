#ifndef CONTAINERNODE_H
#define CONTAINERNODE_H

#include <Node.h>

namespace MX
{
  class ContainerNode : public Node
  {
  public:
    MX_API ContainerNode() = delete;
    MX_API ContainerNode(const std::string &name);


  };
}

#endif // CONTAINERNODE_H