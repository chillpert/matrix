#include "Editor_Hierarchy.h"

namespace MX
{
  Editor_Hierachy::Editor_Hierachy(const std::string& name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Hierachy::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Hierachy::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Hierachy::render()
  {

  }
}