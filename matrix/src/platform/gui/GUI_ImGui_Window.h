#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  class ImGui_Window
  {
  public:
    MX_API ImGui_Window();

    MX_API bool initialize(const std::string& name, ImGuiWindowFlags flags = 0);
    MX_API void update();

    // invokes imgui begin
    MX_API bool begin();
    // invokes imgui end
    MX_API void end();

    MX_API void add_flags(ImGuiWindowFlags flags);
    MX_API void set_flags(ImGuiWindowFlags flags);

    MX_API void push_style(ImGuiStyleVar idx, const ImVec2& val);
    MX_API void push_style(ImGuiStyleVar idx, float val);

  private:
    MX_API void activate_styles();
    MX_API void remove_styles();

    // scales down window size if too big
    MX_API void resize_on_max_size();

    bool m_p_enabled;
    bool m_p_open;

    std::string m_name = "undef";
    ImGuiWindowFlags m_window_flags;
    
    std::vector<std::pair<ImGuiStyleVar, ImVec2>> m_style_vector;
    std::vector<std::pair<ImGuiStyleVar, float>> m_style_float;
  };

  struct ImGui_DockNode
  {
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
  };
}

#endif // GUI_IMGUI_WINDOW_H