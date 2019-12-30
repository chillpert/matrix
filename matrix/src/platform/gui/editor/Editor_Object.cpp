#include "Editor_Object.h"
#include "GUI_ImGui_ContextMenu.h"

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

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Model"))
          {

          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Shader"))
          {

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

          /*
          ImGui::Text("Shader: ");
          if (get_selection().at(0)->m_Shader != nullptr)
          {
            ImGui::SameLine();
            ImGui::Text(get_selection().at(0)->m_Shader->m_Name.c_str());
            ImGui::Text("Initialized: "); ImGui::SameLine();
            ImGui::Text("%i", get_selection().at(0)->m_Shader->m_initialized);
          }
          */
          /*
          ImGui::Text("Node: ");
          ImGui::Text("Name: "); ImGui::SameLine();
          ImGui::Text(get_selection().at(0)->m_Name.c_str());

          ImGui::Text("Shader: ");
          if (get_selection().at(0)->m_Shader != nullptr)
          {
            ImGui::SameLine();
            ImGui::Text(get_selection().at(0)->m_Shader->m_Name.c_str());
            ImGui::Text("Initialized: "); ImGui::SameLine();
            ImGui::Text("%i", get_selection().at(0)->m_Shader->m_initialized);
          }

          ImGui::Text("Parent: ");
          if (get_selection().at(0)->m_Parent != nullptr)
          {
            ImGui::SameLine();
            ImGui::Text(get_selection().at(0)->m_Parent->m_Name.c_str());
          }

          ImGui::Text("Visible: "); ImGui::SameLine();
          ImGui::Text("%i", get_selection().at(0)->m_Parent->m_visible);
          ImGui::Text("Type: "); ImGui::SameLine();
          
          if (dynamic_cast<GeometryNode*>(get_selection().at(0).get()))
          {
            auto geometry_node_ptr = std::static_pointer_cast<GeometryNode>(get_selection().at(0));

            ImGui::Text("Geometry Node: ");
            ImGui::Text("Name: "); ImGui::SameLine();
            ImGui::Text(geometry_node_ptr->m_Model->m_name.c_str());
            ImGui::Text("Directory: "); ImGui::SameLine();
            ImGui::Text(geometry_node_ptr->m_Model->m_directory.c_str());
            ImGui::Text("Full Path:"); ImGui::SameLine();
            ImGui::Text(geometry_node_ptr->m_Model->m_full_path.c_str());
            ImGui::Text("Gamma Correction: "); ImGui::SameLine();
            ImGui::Text("%i", geometry_node_ptr->m_Model->m_gamma_correction);
            ImGui::Text("Initialized: "); ImGui::SameLine();
            ImGui::Text("%i", geometry_node_ptr->m_Model->m_initialized);
          }

          if (dynamic_cast<LightNode*>(get_selection().at(0).get()))
          {
            auto light_node_ptr = std::static_pointer_cast<LightNode>(get_selection().at(0));

            ImGui::Text("Point Light Node");
            ImGui::Text("Ambient: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(light_node_ptr->ambient).c_str());
            ImGui::Text("Diffuse: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(light_node_ptr->diffuse).c_str());
            ImGui::Text("Specular: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(light_node_ptr->specular).c_str());
            ImGui::Text("Ambient Strength: "); ImGui::SameLine();
            ImGui::Text("%f", light_node_ptr->ambient_strength);
            
          }

          if (dynamic_cast<DirectionalLightNode*>(get_selection().at(0).get()))
          {
            auto directional_light_node_ptr = std::static_pointer_cast<DirectionalLightNode>(get_selection().at(0));

            ImGui::Text("Directional Light Node");
            ImGui::Text("Direction: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(directional_light_node_ptr->direction).c_str());
          }

          if (dynamic_cast<PointLightNode*>(get_selection().at(0).get()))
          {
            auto point_light_node_ptr = std::static_pointer_cast<PointLightNode>(get_selection().at(0));

            ImGui::Text("Point Light Node");
            ImGui::Text("Position: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(point_light_node_ptr->position).c_str());
            ImGui::Text("Constant: "); ImGui::SameLine();
            ImGui::Text("%f", point_light_node_ptr->constant);
            ImGui::Text("Linear: "); ImGui::SameLine();
            ImGui::Text("%f", point_light_node_ptr->linear);
            ImGui::Text("Quadratic: "); ImGui::SameLine();
            ImGui::Text("%f", point_light_node_ptr->quadratic);
          }

          if (dynamic_cast<SpotLightNode*>(get_selection().at(0).get()))
          {
            auto spot_light_node_ptr = std::static_pointer_cast<SpotLightNode>(get_selection().at(0));

            ImGui::Text("Spot Light Node");
            ImGui::Text("Position: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(spot_light_node_ptr->position).c_str());
            ImGui::Text("Direction: "); ImGui::SameLine();
            ImGui::Text(glm::to_string(spot_light_node_ptr->direction).c_str());
            ImGui::Text("Constant: "); ImGui::SameLine();
            ImGui::Text("%f", spot_light_node_ptr->constant);
            ImGui::Text("Linear: "); ImGui::SameLine();
            ImGui::Text("%f", spot_light_node_ptr->linear);
            ImGui::Text("Quadratic: "); ImGui::SameLine();
            ImGui::Text("%f", spot_light_node_ptr->quadratic);
            ImGui::Text("Cut Off: "); ImGui::SameLine();
            ImGui::Text("%f", spot_light_node_ptr->cut_off);
            ImGui::Text("Outer Cut Off: "); ImGui::SameLine();
            ImGui::Text("%f", spot_light_node_ptr->outer_cut_off);
          }
          
          */
          
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