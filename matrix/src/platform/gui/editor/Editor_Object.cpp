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
    if (ImGui_Window::begin())
    {
      // only ever show components if an object is selected
      if (get_selection().size() > 0)
      {
        if (get_selection().at(0) != nullptr)
        {
          auto current = get_selection().at(0);

          static bool first_run = true;
          static glm::vec3 scale;
          static glm::quat rotation;
          static glm::vec3 translation;
          static glm::vec3 skew;
          static glm::vec4 perspective;
          
          glm::decompose(current->m_Trans.m_world, scale, rotation, translation, skew, perspective);
          first_run = false;

          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Transform"))
          {
            ImGui::Text("Translate");

            static float step = 0.02f; // 2 cm
            float spacing = ImGui::GetContentRegionAvailWidth() / 3.0f - 16.0f;

            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("x##x translate", &translation.x, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("y##y translate", &translation.y, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("z##z translate", &translation.z, step);

            ImGui::Text("Rotate");

            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("x##x rotate", &rotation.x, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("y##y rotate", &rotation.y, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("z##z rotate", &rotation.z, step);

            ImGui::Text("Scale");

            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("x##x scale", &scale.x, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("y##y scale", &scale.y, step);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(spacing);
            ImGui::DragFloat("z##z scale", &scale.z, step);

            auto temp = glm::mat4(1.0f);
            temp = glm::scale(temp, scale);
            temp *= glm::toMat4(rotation);
            temp = glm::translate(temp, translation);
          }
        }
      }
    }

    ImGui_Window::end();
  }
}