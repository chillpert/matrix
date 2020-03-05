#ifndef EDITOR_PROFILER_H
#define EDITOR_PROFILER_H

#include "GUI_ImGui_Window.h"
#include "Profiler.h"

namespace MX
{
  class Editor_Profiler : public ImGui_Window
  {
  public:
    MX_API Editor_Profiler();
    MX_API Editor_Profiler(const char*, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const char*, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;

    unsigned int m_min_fps;
    unsigned int m_max_fps;
    unsigned int m_average_fps;
  
    Profiler m_data;
  };
}

#endif // EDITOR_PROFILER_H