#include "Editor_Object.h"

namespace MX
{
  Editor_Object::Editor_Object(const std::string& name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Object::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Object::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Object::render()
  {
    static float translation[3] = {0.0f, 0.0f, 0.0f};
    static float rotation[3] = {0.0f, 0.0f, 0.0f};
    static float scale[3] = {0.0f, 0.0f, 0.0f};

    if (ImGui_Window::begin())
    {
      ImGui::SetNextItemOpen(true, ImGuiCond_Once);
      if (ImGui::CollapsingHeader("Transform"))
      {
        ImGui::Text("Translate");

        static float step = 0.02f; // 2 cm
        float spacing = ImGui::GetContentRegionAvailWidth() / 3.0f - 16.0f;

        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("x##x translate", &translation[0], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("y##y translate", &translation[1], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("z##z translate", &translation[2], step);

        ImGui::Text("Rotate");

        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("x##x rotate", &rotation[0], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("y##y rotate", &rotation[1], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("z##z rotate", &rotation[2], step);

        ImGui::Text("Scale");

        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("x##x scale", &scale[0], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("y##y scale", &scale[1], step);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("z##z scale", &scale[2], step);
      }
    }

    ImGui_Window::end();
  }
}