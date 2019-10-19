#include "GUI_ImGui_Window.h"

namespace MX
{
  ImGui_Window::ImGui_Window()
    : p_open(true),
      p_enabled(true)
  { }

  void ImGui_Window::no_titlebar()
  {
    flags |= ImGuiWindowFlags_NoTitleBar;
  }

  void ImGui_Window::no_scrollbar()
  {
    flags |= ImGuiWindowFlags_NoScrollbar;
  }

  void ImGui_Window::no_menu()
  {
    flags |= ImGuiWindowFlags_MenuBar;
  }

  void ImGui_Window::no_move()
  {
    flags |= ImGuiWindowFlags_NoMove;
  }

  void ImGui_Window::no_resize()
  {
    flags |= ImGuiWindowFlags_NoResize;
  }

  void ImGui_Window::no_collapse()
  {
    flags |= ImGuiWindowFlags_NoCollapse;
  }

  void ImGui_Window::no_navigation()
  {
    flags |= ImGuiWindowFlags_NoNav;
  }

  void ImGui_Window::no_background()
  {
    flags |= ImGuiWindowFlags_NoBackground;
  }

  void ImGui_Window::no_bring_to_front()
  {
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
  }
}