#include "Editor_Object.h"
#include "GUI_ImGui_ContextMenu.h"
#include "GUI_ImGui_Icon.h"

#include "Application.h"
#include "Node.h"
#include "GeometryNode.h"
#include "LightNode.h"
#include "ContainerNode.h"

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
      static ImGui_Icon info_icon("icons/info.png", 15.0f, 15.0f);

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

            static ImGui_ContextMenu transform_context_menu("Context Menu Transform");

            if (transform_context_menu.begin())
            {
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
            
              transform_context_menu.end();
            }
   
            // calculate width of drag fields so that three fields and their labels fit next to each other 
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

          
          if (dynamic_cast<GeometryNode*>(current.get()))
          {
            ImGui::Spacing();
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("Model"))
            {
              auto current_ptr = std::dynamic_pointer_cast<GeometryNode>(current);
              static std::string model_name = current_ptr->m_Model->m_name;

              ImGui::Text("Model "); ImGui::SameLine();
              ImGui::Button(model_name.c_str());

              if (ImGui::BeginDragDropTarget())
              {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECT_FE"))
                {
                  IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                  std::string temp = (char*)payload->Data;
                  current_ptr->m_Model = Application::get().m_World.getModelByPath(temp);
                  model_name = temp.substr(temp.find_last_of("/") + 1);
                }
                ImGui::EndDragDropTarget();
              }
            }
          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Rendering"))
          {
            ImGui::Spacing();

            ImGui::Text("Visible "); ImGui::SameLine();
            ImGui::Checkbox("##NodeVisibilityToggle", &current->m_visible);
            
            static bool show_shader_info = false;
            static std::string shader_name = current->m_Shader->m_Name;

            ImGui::Text("Shader"); ImGui::SameLine();

            // if hovered over text ("Shader") display info window
            if (ImGui::IsItemHovered())
              show_shader_info = true;
            else
              show_shader_info = false;

            static ImGui_ContextMenu shader_info("Info##Shader Info");
            if (shader_info.begin(show_shader_info))
            {
              ImGui::Text("Drag and drop any shader file (.vert or .frag) onto this field");
              shader_info.end();
            }

            if (ImGui::Button(shader_name.c_str(), ImVec2(-1.0f, 0.0f))) { }

            if (ImGui::BeginDragDropTarget())
            {
              if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_FE"))
              {
                IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                std::string temp = (char*)payload->Data;
                temp = temp.substr(temp.find_last_of("/") + 1, temp.find_last_of(".") - temp.find_last_of("/") - 1);
                current->m_Shader = Application::get().m_World.getShader(temp);
                shader_name = temp;
              }
              ImGui::EndDragDropTarget();
            }
          }


          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Material"))
          {

          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Logics"))
          {

          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Physics"))
          {

          }

          ImGui::Text(get_selection().at(0)->to_string().c_str());          
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