#ifndef EDITOR_GLOBAL_H
#define EDITOR_GLOBAL_H

#include "Node.h"

namespace MX
{
  // acts as a communication bridge between modules (let any module inherit this class)
  class Editor_Global
  {
  public:
    static std::vector<std::shared_ptr<Node>> &get_selection()
    {
      static std::vector<std::shared_ptr<Node>> selection;
      return selection;
    }

    static bool field_has_changed()
    {
      static bool has_changed = false;

      if (!Editor_Global::get_selection().empty())
      {
        static std::shared_ptr<Node> prev = Editor_Global::get_selection().at(0);

        if (prev != Editor_Global::get_selection().at(0))
          has_changed = true;
        else
          has_changed = false;

        prev = Editor_Global::get_selection().at(0);
      }

      return has_changed;
    }
  };
}

#endif // EDITOR_GLOBAL_H