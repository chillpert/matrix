#include "Editor_Object.h"

namespace MX
{
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
      if (ImGui::CollapsingHeader("Transform"))
      {
        ImGui::Text("Translate");
        ImGui::SameLine();

        static float slider_width = 3.5f;
        // 5 cm
        static float distance = 0.05f;
        float spacing = ImGui::GetContentRegionAvailWidth() / slider_width;
        std::cout << ImGui::GetContentRegionAvailWidth() << std::endl;

        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("x", &translation[0], distance);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("y", &translation[1], distance);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(spacing);
        ImGui::DragFloat("z", &translation[2], distance);

        ImGui::DragFloat("DEBUG: slider width", &slider_width, 0.05f);

        // 3.4 - 382
        // 4.05 - 167

      }

    }
    ImGui_Window::end();
  }
}