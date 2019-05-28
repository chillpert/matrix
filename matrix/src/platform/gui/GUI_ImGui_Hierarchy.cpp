#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"

namespace MX
{
  static bool no_titlebar = 1;
  static bool no_scrollbar = 0;
  static bool no_menu = 0;
  static bool no_move = 0;
  static bool no_resize = 1;
  static bool no_collapse = 0;
  static bool no_close = 1;
  static bool no_nav = 0;
  static bool no_background = 0;
  static bool no_bring_to_front = 0;
  static bool p_open = 1;

  void GUI_ImGui::renderHierarchyWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Hierarchy", &p_open, window_flags);

    ImGui::SetWindowPos(ImVec2(0.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f + 21.0f));
    ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));

    ImGui::End();
  #endif
  }
}