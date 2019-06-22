#ifndef GUI_H
#define GUI_H

#include <stdafx.h>

namespace MX
{
  class GUI
  {
  public:
    MX_API GUI() = default;
    MX_API virtual ~GUI() = default;

    MX_API GUI(const GUI&) = default;
    MX_API GUI &operator=(const GUI&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void update() = 0;
    MX_API virtual void render() = 0;
    MX_API virtual void clean() = 0;
  };
}

#endif // GUI_H