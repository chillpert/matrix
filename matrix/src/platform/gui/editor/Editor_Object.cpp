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

          static float speed_translation = 0.005f; // 5 mm;
          static float speed_rotation = 0.5f;
          static float speed_scale = 0.005f; // 5 mm;

          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Transform"))
          {
            glm::vec3* translation = &current->m_Trans.m_translation;
            glm::vec3* rotation = &current->m_Trans.m_rotation; 
            glm::vec3* scale = &current->m_Trans.m_scale;

            ImGuiIO& io = ImGui::GetIO();
            ImVec2 pos = ImGui::GetCursorScreenPos();

            static bool show_properties = false;

            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
              show_properties = !show_properties;

            if (show_properties)
            {
              /*
              quite ugly right now, so redo this shit
              */

              ImGui::Text("Drag Speed:");
              ImGui::SetNextItemWidth(90.0f);
              ImGui::InputFloat("Translation", &speed_translation, 0.001f);
              ImGui::SetNextItemWidth(90.0f);
              ImGui::InputFloat("Rotation", &speed_rotation, 0.5f);
              ImGui::SetNextItemWidth(90.0f);
              ImGui::InputFloat("Scale", &speed_scale, 0.001f);

              if (ImGui::Button("Reset"))
              {
                translation->x = 0.0f;
                translation->y = 0.0f;
                translation->z = 0.0f;

                rotation->x = 0.0f;
                rotation->y = 0.0f;
                rotation->z = 0.0f;

                scale->x = 1.0f;
                scale->y = 1.0f;
                scale->z = 1.0f;
              }
            }
            else
            {
              float spacing = ImGui::GetContentRegionAvailWidth() / 3.0f - 16.0f;

              ImGui::Text("Translate");

              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("x##x translate", &translation->x, speed_translation); 
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                translation->x = 0.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("y##y translate", &translation->y, speed_translation);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                translation->y = 0.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("z##z translate", &translation->z, speed_translation);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                translation->z = 0.0f;

              ImGui::Text("Rotate");

              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("x##x rotate", &rotation->x, speed_rotation);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                rotation->x = 0.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("y##y rotate", &rotation->y, speed_rotation);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                rotation->y = 0.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("z##z rotate", &rotation->z, speed_rotation);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                rotation->z = 0.0f;

              ImGui::Text("Scale");

              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("x##x scale", &scale->x, speed_scale);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                scale->x = 1.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("y##y scale", &scale->y, speed_scale);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                scale->y = 1.0f;
              ImGui::SameLine();
              ImGui::SetNextItemWidth(spacing);
              ImGui::DragFloat("z##z scale", &scale->z, speed_scale);
              if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                scale->z = 1.0f;
            
              // NEEDS TO BE FIXED
              for (std::shared_ptr<Node> it : get_selection())
              {
                it->m_Trans.translate(*translation);
              }
            }
          }
        }
      }
    }

    ImGui_Window::end();
  }
}