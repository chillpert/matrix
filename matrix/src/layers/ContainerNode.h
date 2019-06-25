#ifndef CONTAINERNODE_H
#define CONTAINERNODE_H

#include <Node.h>

namespace MX
{
  class ContainerNode;

  typedef ContainerNode* MX_ContainerNode;

  class ContainerNode : public Node
  {
  public:
    MX_API ContainerNode() = delete;
    MX_API ContainerNode(const std::string &name);

    MX_API ContainerNode *getNode() override { return this; }

    MX_API std::string getIdentifier() { return "Container"; }
  };
}

#endif // CONTAINERNODE_H