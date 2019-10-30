#include "Editor_Profiler.h"
#include "Application.h"

namespace MX
{
  Editor_Profiler::Editor_Profiler()
    : m_min_fps(0), 
      m_max_fps(0),
      m_average_fps(0) { }

  bool Editor_Profiler::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  void Editor_Profiler::update()
  {
    ImGui_Window::update();
  }

  void Editor_Profiler::render()
  {
    if (ImGui_Window::begin())
    {
      if (ImGui::BeginMenuBar())
      {
        if (ImGui::MenuItem("Reset"))
        {

        }

        if (ImGui::MenuItem("Pause"))
        {

        }

        if (ImGui::MenuItem("Continue"))
        {

        }

        ImGui::EndMenuBar();
      }

      ImGui::Text("TVM: %u", m_data.get_tvm());
      ImGui::Text("CVM: %u", m_data.get_cvm());

      auto current_fps = Application::get().m_Window->m_Props.m_Frames;
    }

    ImGui_Window::end();
  }
}