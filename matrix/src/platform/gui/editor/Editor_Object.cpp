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
              show_properties = true;

            // opens a window with additional settings for the transform component, just right click the header
            if (show_properties)
            {
              static ImGuiWindowFlags transform_settings_flags = 
                ImGuiWindowFlags_AlwaysAutoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoTitleBar;

              // make sure the window always appears where you right clicked at
              static bool update_mouse_pos = true;
              static ImVec2 mouse_pos;
              if (update_mouse_pos)
              {
                mouse_pos = ImGui::GetMousePos();
                update_mouse_pos = false;
              }


              if (ImGui::Begin("Transform Settings", NULL, transform_settings_flags))
              {
                ImGui::SetWindowPos(mouse_pos);

                // on first right click on header set window to being focused to avoid it being deactivated
                static bool first_run = true;
                if (first_run)
                {
                  ImGui::SetWindowFocus();
                  first_run = false;
                }

                if (!ImGui::IsWindowFocused())
                {
                  show_properties = false;
                  first_run = true;
                  update_mouse_pos = true;
                }

                ImGui::Text("Drag Speed:");
                ImGui::SetNextItemWidth(90.0f);
                ImGui::InputFloat("Translation", &speed_translation, 0.001f);
                ImGui::SetNextItemWidth(90.0f);
                ImGui::InputFloat("Rotation", &speed_rotation, 0.5f);
                ImGui::SetNextItemWidth(90.0f);
                ImGui::InputFloat("Scale", &speed_scale, 0.001f);

                ImGui::Separator();
                ImGui::SetNextItemWidth(-1.0f);
                if (ImGui::Button("Reset"))
                {
                  *translation = glm::vec3(0.0f);
                  *rotation = glm::vec3(0.0f);
                  *scale = glm::vec3(1.0f);
                }
              }
              ImGui::End();
            }
   
            float spacing = ImGui::GetContentRegionAvailWidth() / 3.0f - 16.0f;

            transformDrag("Translate", translation, speed_translation, spacing, 0.0f);
            transformDrag("Rotate", rotation, speed_rotation, spacing, 0.0f);
            transformDrag("Scale", scale, speed_scale, spacing, 1.0f);
          
            // NEEDS TO BE FIXED
            for (std::shared_ptr<Node> it : get_selection())
            {
              it->m_Trans.translate(*translation);
            }
          }
        }
      }
    }

    ImGui_Window::end();
  }

  void Editor_Object::transformDrag(const std::string& label, glm::vec3* vec, float drag_speed, float spacing, float reset_value)
  {
    ImGui::Text(label.c_str());

    ImGui::SetNextItemWidth(spacing);
    std::string full_label = "x##x" + label;
    ImGui::DragFloat(full_label.c_str(), &vec->x, drag_speed); 
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
      vec->x = reset_value;

    ImGui::SameLine();
    ImGui::SetNextItemWidth(spacing);
    full_label = "y##y" + label;
    ImGui::DragFloat(full_label.c_str(), &vec->y, drag_speed);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
      vec->y = reset_value;

    ImGui::SameLine();
    ImGui::SetNextItemWidth(spacing);
    full_label = "z##z" + label;
    ImGui::DragFloat(full_label.c_str(), &vec->z, drag_speed);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
      vec->z = reset_value;
  }
}