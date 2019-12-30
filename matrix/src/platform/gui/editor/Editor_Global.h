#ifndef EDITOR_GLOBAL_H
#define EDITOR_GLOBAL_H

#include "Node.h"

namespace MX
{
  // acts as a communication bridge between modules (let any module inherit this class)
  class Editor_Global
  {
  public:
    std::vector<std::shared_ptr<Node>> &get_selection()
    {
      static std::vector<std::shared_ptr<Node>> selection;
      return selection;
    }

    bool selection_has_changed()
    {
      if (!get_selection().empty())
      {
        static std::shared_ptr<Node> prev = get_selection().at(0);

        if (prev != get_selection().at(0))
          return true;

        prev = get_selection().at(0);
      }

      return false;
    }
  };
}

#endif // EDITOR_GLOBAL_H