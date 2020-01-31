#include "Editor_Profiler.h"
#include "Application.h"

namespace MX
{
  Editor_Profiler::Editor_Profiler()
    : m_min_fps(0), 
      m_max_fps(0),
      m_average_fps(0) { }

  Editor_Profiler::Editor_Profiler(const std::string& name, ImGuiWindowFlags flags)
    : m_min_fps(0), 
      m_max_fps(0),
      m_average_fps(0)
  {
    initialize(name, flags);
  }

  bool Editor_Profiler::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Profiler::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Profiler::render()
  {
    if (ImGui_Window::begin())
    {
      // ImGui::Text("TVM: %u", m_data.get_tvm());
      // ImGui::Text("CVM: %u", m_data.get_cvm());

      // auto current_fps = MX_WINDOW->m_Props.m_Frames;
    
    }
      ImGui_Window::end();
  }
}