#include "Editor_Profiler.h"

namespace MX
{
  bool Editor_Profiler::initialize()
  {
    return ImGui_Window::initialize("Profiler##MatrixEditor");
  }

  void Editor_Profiler::update()
  {
    ImGui_Window::update();
  }

  void Editor_Profiler::render()
  {
    ImGui_Window::begin();



    ImGui_Window::end();
  }
}