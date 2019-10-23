#ifndef EDITOR_PROFILER_H
#define EDITOR_PROFILER_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Profiler : public ImGui_Window
  {
  public:
    MX_API Editor_Profiler() = default;

    MX_API bool initialize();
    MX_API void update();
    MX_API void render();
  };
}

#endif // EDITOR_PROFILER_H