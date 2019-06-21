#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include <Node.h>

namespace MX
{
  class LightNode : public Node
  {
  public:
    MX_API LightNode();
    MX_API ~LightNode() = default;

    MX_API LightNode(const LightNode&) = default;
    MX_API LightNode &operator=(const LightNode&) = default;
  };
}

#endif // LIGHTNODE_H