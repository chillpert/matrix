#include "Editor_Object.h"
#include "GUI_ImGui_ContextMenu.h"
#include "GUI_ImGui_Icon.h"

#include "Application.h"
#include "Node.h"
#include "GeometryNode.h"
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
    Editor_Global::field_has_changed();
    return ImGui_Window::update();
  }

  void Editor_Object::render()
  {
    if (ImGui_Window::begin())
    {
      static ImGui_Icon info_icon("info.png", 15.0f, 15.0f);
      const float button_height = 20.0f;
      const float button_spacing = 75.0f;
      const float drag_speed = 0.05f;

      // only ever show components if an object is selected
      if (Editor_Global::get_selection().size() > 0)
      {
        if (Editor_Global::get_selection().at(0) != nullptr)
        {
          auto current = Editor_Global::get_selection().at(0);
          
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
            //
            //for (std::shared_ptr<Node> it : Editor_Global::get_selection())
            //{
            //  it->m_Trans.translate(*translation);
            //}
          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Relations"))
          {
            ImGui::Spacing();

            if (current->m_Parent != nullptr)
            {
              ImGui::Text("Parent "); ImGui::SameLine(button_spacing);
              std::string current_parent_name = current->m_Parent->m_Name;
              ImGui::Button(current_parent_name.c_str(), ImVec2(-1, 0));

              if (ImGui::BeginDragDropTarget())
              {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_H"))
                {
                  IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                  std::string temp = (char*)payload->Data;

                  if (MX_SCENE != nullptr)
                  {
                    std::shared_ptr<Node> new_parent = MX_SCENEGRAPH.search<Node>(temp);
                    
                    if (new_parent != nullptr)
                      current->setParent(new_parent.get());
                  }
                }
                ImGui::EndDragDropTarget();
              }
            }
          }
          
          if (dynamic_cast<GeometryNode*>(current.get()))
          {
            ImGui::Spacing();
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("Model"))
            {
              auto current_ptr = std::dynamic_pointer_cast<GeometryNode>(current);

              static std::string model_name = "undef";

              if (current_ptr->m_Model != nullptr)
                model_name = current_ptr->m_Model->m_name;
              else
                model_name = "undef";

              ImGui::Spacing();
              ImGui::Text("Model "); ImGui::SameLine(button_spacing);
              ImGui::Button(model_name.c_str(), ImVec2(-1.0f, button_height));

              if (ImGui::BeginDragDropTarget())
              {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECT_FE"))
                {
                  IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                  std::string temp = (char*)payload->Data;
                  current_ptr->m_Model = MX_GET_MODEL(temp);
                  model_name = temp.substr(temp.find_last_of("/") + 1);
                }
                ImGui::EndDragDropTarget();
              }

              if (current_ptr->m_textures != nullptr)
              {
                static std::string diffuse_name = "undef";

                if (current_ptr->m_textures->diffuse != nullptr)
                  diffuse_name = current_ptr->m_textures->diffuse->m_Name;
                else
                  diffuse_name = "undef";

                ImGui::Separator();
                ImGui::Text("Diffuse"); ImGui::SameLine(button_spacing);
                ImGui::Button(diffuse_name.c_str(), ImVec2(-1.0f, button_height));

                if (ImGui::BeginDragDropTarget())
                {
                  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("IMAGE_FE"))
                  {
                    IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                    std::string temp = (char*)payload->Data;
                    std::string texture_type = "texture_diffuse";
                    current_ptr->m_textures->diffuse = MX_GET_TEXTURE(temp, texture_type);
                    diffuse_name = temp.substr(temp.find_last_of("/") + 1);
                  }
                  ImGui::EndDragDropTarget();
                }

                static std::string specular_name = "undef";
                
                if (current_ptr->m_textures->specular != nullptr)
                  specular_name = current_ptr->m_textures->specular->m_Name;
                else
                  specular_name = "undef";

                ImGui::Text("Specular"); ImGui::SameLine(button_spacing);
                ImGui::Button(specular_name.c_str() , ImVec2(-1.0f, button_height));

                if (ImGui::BeginDragDropTarget())
                {
                  if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("IMAGE_FE"))
                  {
                    IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                    std::string temp = (char*)payload->Data;
                    std::string texture_type = "texture_specular";
                    current_ptr->m_textures->specular = MX_GET_TEXTURE(temp, texture_type);
                    specular_name = temp.substr(temp.find_last_of("/") + 1);
                  }
                  ImGui::EndDragDropTarget();
                }
              }
            }
          }


          if (dynamic_cast<DirectionalLightNode*>(current.get()))
          {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("Directional Light"))
            {               
              render_light_node_props(std::dynamic_pointer_cast<LightNode>(current), button_spacing);

              auto current_ptr = std::dynamic_pointer_cast<DirectionalLightNode>(current);
              ImGui::Text("Direction"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat3("##Direction", &current_ptr->m_direction[0], drag_speed);
            }
          }

          if (dynamic_cast<PointLightNode*>(current.get()))
          {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("Point Light"))
            {               
              render_light_node_props(std::dynamic_pointer_cast<LightNode>(current), button_spacing);

              auto current_ptr = std::dynamic_pointer_cast<PointLightNode>(current);
              ImGui::Text("Position"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat3("##Position", &current_ptr->m_position[0], drag_speed);

              ImGui::Text("Attenuation");
              ImGui::Separator();
              ImGui::Text("Constant"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Constant", &current_ptr->m_constant, drag_speed, 0.0f);
              ImGui::Text("Linear"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Linear", &current_ptr->m_linear, drag_speed, 0.0f);
              ImGui::Text("Quadratic"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Quadratic", &current_ptr->m_quadratic, drag_speed, 0.0f);
            }
          }

          if (dynamic_cast<SpotLightNode*>(current.get()))
          {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("Spot Light"))
            {               
              render_light_node_props(std::dynamic_pointer_cast<LightNode>(current), button_spacing);

              auto current_ptr = std::dynamic_pointer_cast<SpotLightNode>(current);
              
              ImGui::Text("Direction"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat3("##Direction", &current_ptr->m_direction[0], drag_speed);
              ImGui::Text("Position"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat3("##Position", &current_ptr->m_position[0], drag_speed);

              ImGui::Text("Attenuation");
              ImGui::Separator();
              ImGui::Text("Constant"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Constant", &current_ptr->m_constant, drag_speed, 0.0f);
              ImGui::Text("Linear"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Linear", &current_ptr->m_linear, drag_speed, 0.0f);
              ImGui::Text("Quadratic"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##Quadratic", &current_ptr->m_quadratic, drag_speed, 0.0f);

              ImGui::Text("Light Cone");
              ImGui::Text("Cut off"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##CutOff", &current_ptr->m_cut_off, drag_speed);
              ImGui::Text("Outer cut off"); ImGui::SameLine(button_spacing);
              ImGui::DragFloat("##OuterCutoff", &current_ptr->m_outer_cut_off, drag_speed);
            }
          }

          ImGui::Spacing();
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);
          if (ImGui::CollapsingHeader("Rendering"))
          {
            ImGui::Spacing();

            ImGui::Text("Visible "); ImGui::SameLine(button_spacing);
            ImGui::Checkbox("##NodeVisibilityToggle", &current->m_visible);
            
            if (current->m_Shader != nullptr)
            {
              static bool show_shader_info = false;

              std::string temp = current->m_Shader->m_Name;
              std::string shader_name = temp.substr(temp.find_last_of("/") + 1, temp.find_last_of(".") - temp.find_last_of("/") - 1);
            
              ImGui::Text("Shader"); ImGui::SameLine(button_spacing);

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

              if (ImGui::Button(shader_name.c_str(), ImVec2(-1.0f, button_height))) { }

              if (ImGui::BeginDragDropTarget())
              {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_FE"))
                {
                  IM_ASSERT(payload->DataSize == sizeof(char) * 200);
                  std::string temp = (char*)payload->Data;
                  current->m_Shader = MX_GET_SHADER(temp.substr(0, temp.find_last_of(".")));
                  shader_name = temp.substr(temp.find_last_of("/") + 1, temp.find_last_of(".") - temp.find_last_of("/") - 1);
                }
                ImGui::EndDragDropTarget();
              }
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

          //ImGui::Text(current->to_string().c_str());          
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

  void Editor_Object::render_light_node_props(std::shared_ptr<LightNode> light, float button_spacing)
  {
    ImGui::Text("Diffuse"); ImGui::SameLine(button_spacing);
    ImGui::ColorEdit3("##DiffuseColor", &light->m_diffuse[0]);

    ImGui::Text("Specular"); ImGui::SameLine(button_spacing);
    ImGui::ColorEdit3("##SpecularColor", &light->m_specular[0]);

    ImGui::Text("Ambient"); ImGui::SameLine(button_spacing);
    ImGui::ColorEdit3("##AmbientColor", &light->m_ambient[0]);

    ImGui::Text("Intensity"); ImGui::SameLine(button_spacing);
    ImGui::DragFloat("##AmbientStrength", &light->m_ambient_strength, 0.05f);
  }
}