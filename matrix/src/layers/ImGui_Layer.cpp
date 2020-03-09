#include "ImGui_Layer.h"
#include "Application.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

namespace MX
{
  ImGui_Layer::ImGui_Layer()
    : Layer("ImGuiLayer")
  {

  }

  void ImGui_Layer::OnAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init(Constants::glsl_version.c_str());
  }

  void ImGui_Layer::OnDetach()
  {

  }

  void ImGui_Layer::OnUpdate()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    MX_WARN("Ok");

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(MX_WINDOW->m_Props.m_Width, MX_WINDOW->m_Props.m_Height);

    float time = static_cast<float>(MX_WINDOW->m_Props.m_Time);
    io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGui_Layer::OnEvent(Event& event)
  {

  }
}