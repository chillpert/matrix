#ifndef EDITOR_GLOBAL_H
#define EDITOR_GLOBAL_H

#include "Node.h"

namespace MX
{
  // acts as a communication bridge between modules
  class Editor_Global
  {
  public:
    Editor_Global() = default;

    std::vector<std::shared_ptr<Node>> &get_selection()
    {
      static std::vector<std::shared_ptr<Node>> selection;
      return selection;
    }
  };
}

#endif // EDITOR_GLOBAL_H