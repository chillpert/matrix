#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include <imgui.h>

namespace MX
{
  MX_API void resize_on_max_size();

  class ImGui_Window
  {
  public:
    MX_API ImGui_Window();
    MX_API ImGui_Window(const char* name, ImGuiWindowFlags flags = 0);
    MX_API virtual ~ImGui_Window() = default;

    MX_API virtual std::pair<std::string, bool*> visibilty() { return {m_name, &m_p_enabled}; }
    MX_API virtual bool initialize(const char* name, ImGuiWindowFlags flags = 0);
    MX_API virtual bool update();
    MX_API virtual void render();

    // invokes imgui begin
    MX_API virtual bool begin();
    // invokes imgui end
    MX_API virtual void end();

    MX_API virtual void open();
    MX_API virtual void close();

    MX_API virtual void add_flags(ImGuiWindowFlags flags);
    MX_API virtual void set_flags(ImGuiWindowFlags flags);

    MX_API virtual void push_style(ImGuiStyleVar idx, const ImVec2& val);
    MX_API virtual void push_style(ImGuiStyleVar idx, float val);

  public:
    MX_API void activate_styles();
    MX_API void remove_styles();

    // scales down window size if too big
    MX_API void resize_on_max_size();

    bool m_p_enabled;
    bool m_p_open;
    bool m_called_begin;

    const char* m_name = "undef";
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