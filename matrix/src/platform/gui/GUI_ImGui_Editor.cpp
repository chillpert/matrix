#include <Utils.h>
#include <GUI_ImGui.h>
#include <Application.h>
#include <WindowEvent.h>
#include <Controller.h>

namespace MX
{
  static const float grab_speed = 0.001f;
  static const float transform_factor = 100.0f;

  static const float drag_min = 0.0f;
  static const float drag_max = 1.0f;

  // pop_flags
  static ImGuiWindowFlags popup_flags = 0;
  static bool popup_no_titlebar = 0;
  static bool popup_no_scrollbar = 0;
  static bool popup_no_menu = 1;
  static bool popup_no_move = 1;
  static bool popup_no_resize = 1;
  static bool popup_no_collapse = 1;
  static bool popup_no_nav = 0;
  static bool popup_no_background = 0;
  static bool popup_no_bring_to_front = 0;
  static bool popup_no_autoresize = 0;

  static void render_new_scene_popup();
  static void render_load_scene_popup();
  static void render_delete_scene_popup();

  void renderFileInspectorWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::Begin("File Inspector", &file_inspector_enabled))
    {
      ImGui::Text(file_inspector_name.c_str());
      ImGui::Image(
        file_inspector_id,
        ImVec2(
          file_inspector_width / (file_inspector_width / ImGui::GetWindowWidth()), 
          file_inspector_height / (file_inspector_height / ImGui::GetWindowHeight())
        )
      );
    }
    ImGui::End();
  #endif
  }

  void renderSpawnMenu()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    if (ImGui::Begin("Spawn", &p_open_spawn, window_flags))
    {
      float max_button_width = (ImGui::GetWindowWidth() / 3.0f) - 10.0f;

      static char object_name[128];
      ImGui::SetNextItemWidth(-1);
      ImGui::InputText("##give object an unique name", object_name, IM_ARRAYSIZE(object_name));

      if (ImGui::Button("Object", ImVec2(max_button_width, 20.0f)))
      {
        if (current_scene->push_object(std::string(object_name), default_root_name))
        {
          MX_INFO_LOG("MX: Scene: Push: Object: " + std::string(object_name));
          current_node = current_scenegraph->search(object_name, current_root);
          needs_refresh = 1;
          MX_SUCCESS("MX: Scene: Push: Object: " + std::string(object_name));
        }
      }
      ImGui::SameLine();
      if (ImGui::Button("Container", ImVec2(max_button_width, 20.0f)))
      {
        if (current_scene->push_container(std::string(object_name), default_root_name))
        {
          MX_INFO_LOG("MX: Scene: Push: Container: " + std::string(object_name));
          current_node = current_scenegraph->search(object_name, current_root);
          needs_refresh = 1;
          MX_SUCCESS("MX: Scene: Push: Container: " + std::string(object_name));
        }
      }

      ImGui::SameLine();
      if (ImGui::Button("Effect", ImVec2(-1, 20.0f)))
      {
        MX_WARN("Well this doesn't do shit");
      }

      const int max_directional_light_entities = 5;
      const int max_point_light_entities = 5;
      const int max_spot_light_entities = 5;
      int current_directional_light_entities = MX_SCENEGRAPH.m_directional_light_nodes.size();
      int current_point_light_entities = MX_SCENEGRAPH.m_point_light_nodes.size();
      int current_spot_light_entities = MX_SCENEGRAPH.m_spot_light_nodes.size();

      if (ImGui::Button("Directional Light", ImVec2(max_button_width, 20.0f)))
      {
        if (current_scene->push_directional_light(std::string(object_name), default_root_name) && current_directional_light_entities <= max_directional_light_entities)
        {
          MX_INFO_LOG("MX: Scene: Push: Directional Light: " + std::string(object_name));
          ++current_directional_light_entities;
          current_node = current_scenegraph->search(object_name, current_root);
          needs_refresh = 1;
          MX_SUCCESS("MX: Scene: Push: Directional Light: " + std::string(object_name));
        }
      }
      ImGui::SameLine();
      if (ImGui::Button("Point Light", ImVec2(max_button_width, 20.0f)))
      {
        if (current_scene->push_point_light(std::string(object_name), default_root_name) && current_point_light_entities <= max_point_light_entities)
        {
          MX_INFO_LOG("MX: Scene: Push: Point Light: " + std::string(object_name));
          ++current_point_light_entities;
          current_node = current_scenegraph->search(object_name, current_root);
          needs_refresh = 1;
          MX_SUCCESS("MX: Scene: Push: Point Light: " + std::string(object_name));
        }
      }
      ImGui::SameLine();
      if (ImGui::Button("Spot Light", ImVec2(-1, 20.0f)))
      {
        if (current_scene->push_spot_light(std::string(object_name), default_root_name) && current_spot_light_entities <= max_spot_light_entities)
        {
          MX_INFO_LOG("MX: Scene: Push: Spot Light: " + std::string(object_name));
          ++current_spot_light_entities;
          current_node = current_scenegraph->search(object_name, current_root);
          needs_refresh = 1;
          MX_SUCCESS("MX: Scene: Push: Spot Light: " + std::string(object_name));
        }
      }
    }
    ImGui::End();
  #endif
  }

  void renderAssestsMenu()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    if (ImGui::Begin("Assets", &p_open_assets, window_flags))
    {
      static int item_models = -1;
      static int item_shaders = -1;
      static int item_diffuse_map = -1;
      static int item_normal_map = -1;
      static int item_bump_map = -1;
      static int item_height_map = -1;
      static int item_parent = -1;

      static ImTextureID diffuse_tex_id;
      static ImTextureID normal_tex_id;
      static ImTextureID bump_tex_id;
      static ImTextureID height_tex_id;

      int item_prev_models = item_models;
      int item_prev_shaders = item_shaders;
      int item_prev_diffuse_map = item_diffuse_map;
      int item_prev_normal_map = item_normal_map;
      int item_prev_bump_map = item_bump_map;
      int item_prev_height_map = item_height_map;
      int item_prev_parent = item_parent;

      if (needs_refresh)
      {
        needs_refresh = 0;

        item_models = -1;
        item_shaders = -1;
        item_diffuse_map = -1;
        item_normal_map = -1;
        item_bump_map = -1;
        item_height_map = -1;
        item_parent = -1;

        diffuse_tex_id = nullptr;
        normal_tex_id = nullptr;
        bump_tex_id = nullptr;
        height_tex_id = nullptr;

        if (current_node != current_root && current_node != nullptr)
        {
          if (current_node->m_Shader != nullptr)
          {
            for (u_int64_t i = 0; i < all_shaders.size(); ++i)
            {
              if (current_node->m_Shader->m_Name == all_shaders[i])
                item_shaders = i;
            }
          }
          else
            item_shaders = -1;

          if (dynamic_cast<GeometryNode*>(current_node.get()))
          {
            auto object_node_ptr = dynamic_cast<GeometryNode*>(current_node.get());

            if (object_node_ptr->m_Model != nullptr)
            {
              for (u_int64_t i = 0; i < all_models.size(); ++i)
              {
                std::string rhs = all_models[i] + std::string(".obj");
                if (object_node_ptr->m_Model->m_name == rhs)
                  item_models = i;
              }
            }
            else
              item_models = -1;

            if (object_node_ptr->m_textures != nullptr)
            {
              if (object_node_ptr->m_textures->diffuse != nullptr)
              {
                for (u_int64_t i = 0; i < all_diffuse_maps.size(); ++i)
                {
                  std::string rhs = all_diffuse_maps[i] + std::string(".jpg");
                  if (object_node_ptr->m_textures->diffuse->m_Name == rhs)
                    item_diffuse_map = i;
                }
              }
            }
            else
              item_diffuse_map = -1;

            if (object_node_ptr->m_textures != nullptr)
            {
              if (object_node_ptr->m_textures->normal != nullptr)
              {
                for (u_int64_t i = 0; i < all_normal_maps.size(); ++i)
                {
                  std::string rhs = all_normal_maps[i] + std::string(".jpg");
                  if (object_node_ptr->m_textures->normal->m_Name == rhs)
                    item_normal_map = i;
                }
              }
            }
            else
              item_normal_map = -1;

            if (object_node_ptr->m_textures != nullptr)
            {
              if (object_node_ptr->m_textures->bump != nullptr)
              {
                for (u_int64_t i = 0; i < all_bump_maps.size(); ++i)
                {
                  std::string rhs = all_bump_maps[i] + std::string(".jpg");
                  if (object_node_ptr->m_textures->bump->m_Name == rhs)
                    item_bump_map = i;
                }
              }
            }
            else
              item_bump_map = -1;

            if (object_node_ptr->m_textures != nullptr)
            {
              if (object_node_ptr->m_textures->height != nullptr)
              {
                for (u_int64_t i = 0; i < all_height_maps.size(); ++i)
                {
                  std::string rhs = all_height_maps[i] + std::string(".jpg");
                  if (object_node_ptr->m_textures->height->m_Name == rhs)
                    item_height_map = i;
                }
              }
            }
            else
              item_height_map = -1;
          }

          if (current_node->m_Parent != nullptr)
          {
            for (u_int64_t i = 0; i < all_objects.size(); ++i)
            {
              if (current_node->m_Parent->m_Name == all_objects[i])
                item_parent = i;
            }
          }
          else
            item_parent = -1;
        }
        else
        {
          item_models = -1;
          item_shaders = -1;
          item_diffuse_map = -1;
          item_normal_map = -1;
          item_bump_map = -1;
          item_height_map = -1;
          item_parent = -1;
        }
      } // needs_refresh

      if (current_node != current_root && current_node != nullptr)
      {
        ImGui::Text(current_node->m_Name.c_str());

        static float diffuse_tex_w;
        static float diffuse_tex_h;

        static float normal_tex_w;
        static float normal_tex_h;

        static float bump_tex_w;
        static float bump_tex_h;

        static float height_tex_w;
        static float height_tex_h;

        static float max_parent_child_height = 40.0f;
        static float max_shader_child_height = 115.0f;
        static float max_model_child_height = 40.0f;
        static float max_map_child_height = 230.0f;

        if (dynamic_cast<GeometryNode*>(current_node.get()))
        {
          auto object_node_ptr = std::static_pointer_cast<GeometryNode>(current_node);

          if (object_node_ptr->m_textures != nullptr)
          {
            if (object_node_ptr->m_textures->diffuse != nullptr)
            {
              diffuse_tex_id = (void*)object_node_ptr->m_textures->diffuse->getID();
              diffuse_tex_w = static_cast<float>(object_node_ptr->m_textures->diffuse->m_Stb.width);
              diffuse_tex_h = static_cast<float>(object_node_ptr->m_textures->diffuse->m_Stb.height);
            }

            if (object_node_ptr->m_textures->normal != nullptr)
            {
              normal_tex_id = (void*)object_node_ptr->m_textures->normal->getID();
              normal_tex_w = static_cast<float>(object_node_ptr->m_textures->normal->m_Stb.width);
              normal_tex_h = static_cast<float>(object_node_ptr->m_textures->normal->m_Stb.height);
            }

            if (object_node_ptr->m_textures->bump != nullptr)
            {
              bump_tex_id = (void*)object_node_ptr->m_textures->bump->getID();
              bump_tex_w = static_cast<float>(object_node_ptr->m_textures->bump->m_Stb.width);
              bump_tex_h = static_cast<float>(object_node_ptr->m_textures->bump->m_Stb.height);
            }

            if (object_node_ptr->m_textures->height != nullptr)
            {
              height_tex_id = (void*)object_node_ptr->m_textures->height->getID();
              height_tex_w = static_cast<float>(object_node_ptr->m_textures->height->m_Stb.width);
              height_tex_h = static_cast<float>(object_node_ptr->m_textures->height->m_Stb.height);
            }
          }
        }
        else
        {
          diffuse_tex_id = nullptr;
          normal_tex_id = nullptr;
          bump_tex_id = nullptr;
          height_tex_id = nullptr;

          item_diffuse_map = -1;
          item_normal_map = -1;
          item_bump_map = -1;
          item_height_map = -1;
        }

        const int max_combo = 5;
        if (ImGui::CollapsingHeader("Parent##parent header"))
        {
          if (ImGui::BeginChild("parent child", ImVec2(-1, max_parent_child_height), true))
          {
            ImGui::SetNextItemWidth(-1);
            ImGui::Combo("##objects to select", &item_parent, all_objects.data(), IM_ARRAYSIZE(all_objects.data()) * all_objects.size(), max_combo);

            if (item_prev_parent != item_parent)
            {
              current_node->setParent(current_scenegraph->search(all_objects.at(item_parent), current_root));
              needs_refresh = 1;
            }
          }
          ImGui::EndChild();
        }

        if (ImGui::CollapsingHeader("Shader##shader header"))
        {
          if (ImGui::BeginChild("shader child", ImVec2(-1, max_shader_child_height), true))
          {
            ImGui::SetNextItemWidth(-1);
            ImGui::Combo("##shaders to select", &item_shaders, all_shaders.data(), IM_ARRAYSIZE(all_shaders.data()) * all_shaders.size(), max_combo);
          
            if (dynamic_cast<LightNode*>(current_node.get()))
            {
              std::shared_ptr<LightNode>lightnode_ptr = std::static_pointer_cast<LightNode>(current_node);
              
              ImGui::Spacing();
              ImGui::Separator();
              ImGui::Spacing();

              ImVec4 ambient{lightnode_ptr->ambient.r, lightnode_ptr->ambient.g, lightnode_ptr->ambient.b, 1.0f};
              ImGui::ColorEdit3("Ambient##ambient light colorr", (float*)&ambient);
              lightnode_ptr->ambient.r = ambient.x;
              lightnode_ptr->ambient.g = ambient.y;
              lightnode_ptr->ambient.b = ambient.z;

              ImVec4 diffuse{lightnode_ptr->diffuse.r, lightnode_ptr->diffuse.g, lightnode_ptr->diffuse.b, 1.0f};
              ImGui::ColorEdit3("Diffuse##diffuse light color", (float*)&diffuse);
              lightnode_ptr->diffuse.r = diffuse.x;
              lightnode_ptr->diffuse.g = diffuse.y;
              lightnode_ptr->diffuse.b = diffuse.z;

              ImVec4 specular{lightnode_ptr->specular.r, lightnode_ptr->specular.g, lightnode_ptr->specular.b, 1.0f};
              ImGui::ColorEdit3("Specular##specular light color", (float*)&specular);
              lightnode_ptr->specular.r = specular.x;
              lightnode_ptr->specular.g = specular.y;
              lightnode_ptr->specular.b = specular.z;

              if (dynamic_cast<PointLightNode*>(current_node.get()))
              {
                std::shared_ptr<PointLightNode> pointlight_ptr = std::static_pointer_cast<PointLightNode>(current_node);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Light Attenuation");
                ImGui::SliderFloat("Constant##constant light", &pointlight_ptr->constant, 0.0f, 2.0f);
                ImGui::SliderFloat("Linear##linear attenuation", &pointlight_ptr->linear, 0.0f, 10.0f);
                ImGui::SliderFloat("Quadratic##linear attenutation", &pointlight_ptr->quadratic, 0.0f, 2.0f);
              
                max_shader_child_height = 230.0f;
              }
              else if (dynamic_cast<SpotLightNode*>(current_node.get()))
              {
                std::shared_ptr<SpotLightNode> pointlight_ptr = std::static_pointer_cast<SpotLightNode>(current_node);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Light Attenuation");
                ImGui::SliderFloat("Constant##constant light", &pointlight_ptr->constant, 0.0f, 2.0f);
                ImGui::SliderFloat("Linear##linear attenuation", &pointlight_ptr->linear, 0.0f, 10.0f);
                ImGui::SliderFloat("Quadratic##linear attenutation", &pointlight_ptr->quadratic, 0.0f, 2.0f);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Spot");
                ImGui::SliderFloat("Cut off##spot light cut off", &pointlight_ptr->cut_off, 0.0f, 100.0f);
                ImGui::SliderFloat("Outer cut off##spot light outer cut off", &pointlight_ptr->outer_cut_off, 0.0f, 100.0f);
              
                max_shader_child_height = 320.0f;
              }
              else
                max_shader_child_height = 130.0f;
            }
            else
              max_shader_child_height = 40.0f;
            
          }
          ImGui::EndChild();
        }

        if (dynamic_cast<GeometryNode*>(current_node.get()))
        {
          if (ImGui::CollapsingHeader("Model##model header"))
          {
            if (ImGui::BeginChild("model child", ImVec2(-1, max_model_child_height), true))
            {
              ImGui::SetNextItemWidth(-1);
              ImGui::Combo("##models to select", &item_models, all_models.data(), IM_ARRAYSIZE(all_models.data()) * all_models.size(), max_combo);
            }
            ImGui::EndChild();
          }

          if (ImGui::CollapsingHeader("Maps##texture maps"))
          {
            if (ImGui::BeginChild("maps child", ImVec2(-1, max_map_child_height), true))
            {
              if (dynamic_cast<GeometryNode*>(current_node.get()))
              {
                auto object_node_ptr = std::static_pointer_cast<GeometryNode>(current_node);

                if (object_node_ptr->m_textures != nullptr)
                {
                  if (ImGui::ImageButton(diffuse_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / diffuse_tex_w, 16.0f / diffuse_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
                  {
                    if (object_node_ptr->m_textures->diffuse != nullptr)
                    {
                      file_inspector_id = diffuse_tex_id;
                      file_inspector_width = diffuse_tex_w;
                      file_inspector_height = diffuse_tex_h;
                      file_inspector_name = object_node_ptr->m_textures->diffuse->m_Name;
                      file_inspector_enabled = 1;
                    }
                  }
                  ImGui::SameLine();
                  ImGui::Combo("Diffuse##diffuse map", &item_diffuse_map, all_diffuse_maps.data(), IM_ARRAYSIZE(all_diffuse_maps.data()) * all_diffuse_maps.size(), max_combo);
                  ImGui::SameLine();
                  if (ImGui::Button("X##delete diffuse texture"))
                  {
                    if (object_node_ptr->m_textures->diffuse != nullptr)
                    {
                      object_node_ptr->m_textures->diffuse->unbind();
                      object_node_ptr->m_textures->diffuse = nullptr;
                    }
                    
                  }

                  if (ImGui::ImageButton(normal_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / normal_tex_w, 16.0f / normal_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
                  {
                    if (object_node_ptr->m_textures->normal != nullptr)
                    {
                      file_inspector_id = normal_tex_id;
                      file_inspector_width = normal_tex_w;
                      file_inspector_height = normal_tex_h;
                      file_inspector_name = object_node_ptr->m_textures->normal->m_Name;
                      file_inspector_enabled = 1;
                    }
                  }
                  ImGui::SameLine();
                  ImGui::Combo("Normal##normal map", &item_normal_map, all_normal_maps.data(), IM_ARRAYSIZE(all_normal_maps.data()) * all_normal_maps.size(), max_combo);

                  if (ImGui::ImageButton(bump_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / bump_tex_w, 16.0f / bump_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
                  {
                    if (object_node_ptr->m_textures->bump != nullptr)
                    {
                      file_inspector_id = bump_tex_id;
                      file_inspector_width = bump_tex_w;
                      file_inspector_height = bump_tex_h;
                      file_inspector_name = object_node_ptr->m_textures->bump->m_Name;
                      file_inspector_enabled = 1;
                    }
                  }
                  ImGui::SameLine();
                  ImGui::Combo("Bump##bump map", &item_bump_map, all_bump_maps.data(), IM_ARRAYSIZE(all_bump_maps.data()) * all_bump_maps.size(), max_combo);

                  if (ImGui::ImageButton(height_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / height_tex_w, 16.0f / height_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
                  {
                    if (object_node_ptr->m_textures->height != nullptr)
                    {
                      file_inspector_id = height_tex_id;
                      file_inspector_width = height_tex_w;
                      file_inspector_height = height_tex_h;
                      file_inspector_name = object_node_ptr->m_textures->height->m_Name;
                      file_inspector_enabled = 1;
                    }
                  }
                  ImGui::SameLine();
                  ImGui::Combo("Height##height map", &item_height_map, all_height_maps.data(), IM_ARRAYSIZE(all_height_maps.data()) * all_height_maps.size(), max_combo);
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Material");
                
                ImVec4 ambient{object_node_ptr->material.ambient.r, object_node_ptr->material.ambient.g, object_node_ptr->material.ambient.b, 1.0f};
                ImGui::ColorEdit3("Ambient##ambient material color", (float*)&ambient);
                object_node_ptr->material.ambient.r = ambient.x;
                object_node_ptr->material.ambient.g = ambient.y;
                object_node_ptr->material.ambient.b = ambient.z;

                ImVec4 diffuse{object_node_ptr->material.diffuse.r, object_node_ptr->material.diffuse.g, object_node_ptr->material.diffuse.b, 1.0f};
                ImGui::ColorEdit3("Diffuse##diffuse material color", (float*)&diffuse);
                object_node_ptr->material.diffuse.r = diffuse.x;
                object_node_ptr->material.diffuse.g = diffuse.y;
                object_node_ptr->material.diffuse.b = diffuse.z;

                ImVec4 specular{object_node_ptr->material.specular.r, object_node_ptr->material.specular.g, object_node_ptr->material.specular.b, 1.0f};
                ImGui::ColorEdit3("Specular##specular material color", (float*)&specular);
                object_node_ptr->material.specular.r = specular.x;
                object_node_ptr->material.specular.g = specular.y;
                object_node_ptr->material.specular.b = specular.z;
              }
            }
            ImGui::EndChild();
          }

          if (item_prev_shaders != item_shaders && item_shaders >= 0)
          {
            current_node->setShader(std::static_pointer_cast<MX_SHADER>(MX_WORLD.m_Shaders[item_shaders]));
            item_prev_shaders = item_shaders;
          }

          if (dynamic_cast<GeometryNode*>(current_node.get()) && current_node != nullptr && current_node != current_root)
          {
            auto object_node_ptr = std::static_pointer_cast<GeometryNode>(current_node);

            if (item_prev_models != item_models && item_models >= 0)
            {
              object_node_ptr->setModel(MX_WORLD.m_Models[item_models]);
              item_prev_models = item_models;
            }

            if (item_prev_diffuse_map != item_diffuse_map && item_diffuse_map >= 0)
            {
              object_node_ptr->setDiffuseTexture(std::static_pointer_cast<MX_TEXTURE>(MX_WORLD.m_Textures[item_diffuse_map]));
              item_prev_diffuse_map = item_diffuse_map;
            }

            if (item_prev_normal_map != item_normal_map && item_normal_map >= 0)
            {
              object_node_ptr->setNormalTexture(std::static_pointer_cast<MX_TEXTURE>(MX_WORLD.m_Textures[item_normal_map]));
              item_prev_normal_map = item_normal_map;
            }

            if (item_prev_bump_map != item_bump_map && item_bump_map >= 0)
            {
              object_node_ptr->setBumpTexture(std::static_pointer_cast<MX_TEXTURE>(MX_WORLD.m_Textures[item_bump_map]));
              item_prev_bump_map = item_bump_map;
            }

            if (item_prev_height_map != item_height_map && item_height_map >= 0)
            {
              object_node_ptr->setHeightTexture(std::static_pointer_cast<MX_TEXTURE>(MX_WORLD.m_Textures[item_height_map]));
              item_prev_height_map = item_height_map;
            }
          }
        }
      }
    }
    ImGui::End();
  #endif
  }

  void rotate_node(std::shared_ptr<Node> node)
  {
    static float x_rotate_drag = 0;
    static float y_rotate_drag = 0;
    static float z_rotate_drag = 0;
        
    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("xr##x_rotate_slider", &x_rotate_drag, grab_speed))
    {
      node->setTransform(X, x_rotate_drag / transform_factor, 0);
    }

    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("yr##y_rotate_slider", &y_rotate_drag, grab_speed))
    {
      node->setTransform(Y, x_rotate_drag / transform_factor, 0);
    }

    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("zr##z_rotate_slider", &z_rotate_drag, grab_speed))
    {
      node->setTransform(Z, x_rotate_drag / transform_factor, 0);
    }
  }

  void translate_node(std::shared_ptr<Node> node)
  {
    static float x_translate_drag = 0;
    static float y_translate_drag = 0;
    static float z_translate_drag = 0;

    static float prev_x_translate_drag = 0;
    static float prev_y_translate_drag = 0;
    static float prev_z_translate_drag = 0;

    prev_x_translate_drag = x_translate_drag;
        
    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("x##x_slider", &x_translate_drag, grab_speed))
    {
      node->setTransform(
        (x_translate_drag > 0) ? (x_translate_drag > prev_x_translate_drag) ? RIGHT : LEFT : (x_translate_drag > prev_x_translate_drag) ? LEFT : RIGHT, 
        x_translate_drag / transform_factor, 
        0
      );
    }

    prev_y_translate_drag = y_translate_drag;

    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("y##y_slider", &y_translate_drag, grab_speed))
    {
      node->setTransform(
        (y_translate_drag > 0) ? (y_translate_drag > prev_y_translate_drag) ? UP : DOWN : (y_translate_drag > prev_y_translate_drag) ? DOWN : UP, 
        y_translate_drag / transform_factor,
        0
      );
    }

    prev_z_translate_drag = z_translate_drag;

    ImGui::SetNextItemWidth(-10);
    if (ImGui::DragFloat("z##z_slider", &z_translate_drag, grab_speed))
    {
      node->setTransform(
        (z_translate_drag > 0) ? (z_translate_drag > prev_z_translate_drag) ? FORWARDS : BACKWARDS : (z_translate_drag > prev_z_translate_drag) ? BACKWARDS : FORWARDS, 
        z_translate_drag / transform_factor, 
        0
      );
    }
  }

  void scale_node(std::shared_ptr<Node> node)
  {
    static float complete_scale_drag = 0;
    static float prev_complete_scale_drag = 0;
    
    ImGui::SetNextItemWidth(-10);
    ImGui::InputFloat("s##complete_scale_drag", &complete_scale_drag, 0.05f, 2.0f, "%.3f");

    if (complete_scale_drag != prev_complete_scale_drag && complete_scale_drag >= 0.01f)
      node->setTransform(SCALE, complete_scale_drag, 0);
  }

  void translate_vector(glm::vec3 &vec)
  {
    static float x_vec_translate = 0;
    static float prev_x_vec_translate = 0;
    static float y_vec_translate = 0;
    static float prev_y_vec_translate = 0;
    static float z_vec_translate = 0;
    static float prev_z_vec_translate = 0;

    ImGui::SetNextItemWidth(-10);
    ImGui::InputFloat("x##x_vec_translate", &x_vec_translate, 0.05f, 2.0f, "%.3f");

    if (x_vec_translate != prev_x_vec_translate && x_vec_translate >= 0.01f)
      vec.x += x_vec_translate;

    ImGui::SetNextItemWidth(-10);
    ImGui::InputFloat("y##y_vec_translate", &y_vec_translate, 0.05f, 2.0f, "%.3f");

    if (y_vec_translate != prev_y_vec_translate && y_vec_translate >= 0.01f)
      vec.y += y_vec_translate;

    ImGui::SetNextItemWidth(-10);
    ImGui::InputFloat("z##z_vec_translate", &z_vec_translate, 0.05f, 2.0f, "%.3f");

    if (z_vec_translate != prev_z_vec_translate && z_vec_translate >= 0.01f)
      vec.z += z_vec_translate;
  }

  void renderTransformMenu()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Transform", &p_open_transform, window_flags))
    {
      if (current_node != nullptr)
      {
        if (dynamic_cast<LightNode*>(current_node.get()))
        {
          if (dynamic_cast<DirectionalLightNode*>(current_node.get()))
          {
            translate_vector(std::static_pointer_cast<DirectionalLightNode>(current_node)->direction);
          }
          else if (dynamic_cast<PointLightNode*>(current_node.get()))
          {
            translate_vector(std::static_pointer_cast<PointLightNode>(current_node)->position);
          }
          else if (dynamic_cast<SpotLightNode*>(current_node.get()))
          {
            auto spot_light_ptr = std::static_pointer_cast<SpotLightNode>(current_node);
            spot_light_ptr->position = MX_CAMERA.m_Position;
            spot_light_ptr->direction = MX_CAMERA.m_Front;

            translate_vector(spot_light_ptr->direction);
            ImGui::Separator();
            translate_vector(spot_light_ptr->position);
          }
        }
        else if (dynamic_cast<ContainerNode*>(current_node.get()))
        {
          translate_node(current_node);
        }
        else if (dynamic_cast<GeometryNode*>(current_node.get()))
        {
          translate_node(current_node);
          ImGui::Separator();
          scale_node(current_node);
          ImGui::Separator();
          rotate_node(current_node);
        }
      }
    }
    ImGui::End();
  #endif
  }

  void renderScenesMenu()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (popup_no_titlebar)        popup_flags |= ImGuiWindowFlags_NoTitleBar;
    if (popup_no_scrollbar)       popup_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!popup_no_menu)           popup_flags |= ImGuiWindowFlags_MenuBar;
    if (popup_no_move)            popup_flags |= ImGuiWindowFlags_NoMove;
    if (popup_no_resize)          popup_flags |= ImGuiWindowFlags_NoResize;
    if (popup_no_collapse)        popup_flags |= ImGuiWindowFlags_NoCollapse;
    if (popup_no_nav)             popup_flags |= ImGuiWindowFlags_NoNav;
    if (popup_no_background)      popup_flags |= ImGuiWindowFlags_NoBackground;
    if (popup_no_bring_to_front)  popup_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (!popup_no_autoresize)      popup_flags |= ImGuiWindowFlags_AlwaysAutoResize;

    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Scenes##Scenes Window", &p_open_transform, window_flags))
    {
      float window_width = (ImGui::GetWindowWidth() / 3.0f) - 10.0f;

      if (ImGui::Button("new##create new scene", ImVec2(window_width, 20.0f)))
        ImGui::OpenPopup("Scene##create");

      ImGui::SameLine();

      if (ImGui::Button("load##load existing scene", ImVec2(window_width, 20.0f)))
        ImGui::OpenPopup("Scene##load");

      ImGui::SameLine();
      
      if (ImGui::Button("delete##delete existing scene", ImVec2(window_width, 20.0f)))
        ImGui::OpenPopup("Scene##delete");

      for (auto it : *all_scenes)
      {
        if (ImGui::CollapsingHeader(it->m_Name.c_str()))
        {
          // scene properties
          if (ImGui::BeginChild("scene properties child", ImVec2(-1, 113.0f), true, false))
          {
            ImGui::BulletText("Total:        %lu", it->m_ExistingObjects.size());
            ImGui::Separator();
            ImGui::BulletText("Lighting:");
            ImGui::Indent();
            ImGui::BulletText("Directional:  %lu", current_scenegraph->m_directional_light_nodes.size());
            ImGui::BulletText("Point:        %lu", current_scenegraph->m_point_light_nodes.size());
            ImGui::BulletText("Spot:         %lu", current_scenegraph->m_spot_light_nodes.size());
            ImGui::Unindent();
          }
          ImGui::EndChild();
        }
      }
      render_new_scene_popup();
      render_load_scene_popup();
      render_delete_scene_popup();
    }
    ImGui::End();
  #endif
  }

  static void render_new_scene_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("Scene##create", NULL, popup_flags))
    {
      static bool input_accepted = 1;
      if (input_accepted)
        ImGui::Text("Type in an unique name:");
      else
        ImGui::Text("Name already in use");

      static char input[128];
      ImGui::InputText("##type in name for object to spawn", input, IM_ARRAYSIZE(input));

      for (auto it : *all_scenes)
      {
        if (it->m_Name == input)
        {
          input_accepted = 0;
          break;
        }
        else
          input_accepted = 1;
      }

      ImGui::SameLine();
      if (ImGui::Button("Confirm##confirm create scene"))
      {
        if (!strlen(input) == 0 && input_accepted)
        {
          MX_WORLD.push(std::shared_ptr<Scene>(new Scene(input)));
          memset(&input[0], 0, sizeof(input));

          ImGui::CloseCurrentPopup();
        }
      }

      ImGui::SameLine();
      if (ImGui::Button("Cancel##cancel create scene"))
      {
        input_accepted = 1;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  #endif
  }

  static void render_delete_scene_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("Scene##delete", NULL, popup_flags))
    {
      // display all scenes
      all_current_scenes.resize(MX_WORLD.m_ExistingScenes.size());

      for (unsigned int i = 0; i < MX_WORLD.m_ExistingScenes.size(); ++i)
        all_current_scenes[i] = MX_WORLD.m_ExistingScenes[i]->m_Name.c_str();

      static int item_current_scenes = 0;
      static bool input_accepted = 1;

      if (input_accepted)
        ImGui::Text("Select a scene to delete:");
      else
        ImGui::Text("This scene can not be deleted");

      ImGui::Combo("##scenes to delete", &item_current_scenes, all_current_scenes.data(), all_current_scenes.size());

      ImGui::SameLine();
      if (ImGui::Button("Confirm##cancel deleting scene"))
      {
        if (MX_WORLD.m_ActiveScene != MX_WORLD.m_ExistingScenes[item_current_scenes] && MX_WORLD.m_ExistingScenes.size() > 0)
        {
          MX_INFO_LOG("MX: World: Pop: " + MX_WORLD.m_ExistingScenes[item_current_scenes]->m_Name);
          MX_WORLD.m_ExistingScenes.erase(MX_WORLD.m_ExistingScenes.begin() + item_current_scenes);
          MX_SUCCESS_LOG("MX: World: Pop: " + MX_WORLD.m_ExistingScenes[item_current_scenes]->m_Name);
          ImGui::CloseCurrentPopup();
        }
        else
          input_accepted = 0;
      }

      ImGui::SameLine();
      if (ImGui::Button("Cancel##cancel deleting scene"))
      {
        input_accepted = 1;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  #endif
  }

  static void render_load_scene_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("Scene##load", NULL, popup_flags))
    {
      // display all scenes
      all_current_scenes.resize(MX_WORLD.m_ExistingScenes.size());

      for (unsigned int i = 0; i < MX_WORLD.m_ExistingScenes.size(); ++i)
        all_current_scenes[i] = MX_WORLD.m_ExistingScenes[i]->m_Name.c_str();

      static int item_current_scenes = 0;
      ImGui::Text("Select a scene to load:");
      ImGui::Combo("##all_scenes_to_select", &item_current_scenes, all_current_scenes.data(), all_current_scenes.size());

      ImGui::SameLine();

      if (ImGui::Button("Confirm##confirm load scene from combo", ImVec2(60.0f, 20.0f)))
      {
        MX_WORLD.m_ActiveScene = MX_WORLD.m_ExistingScenes[item_current_scenes];
        item_current_scenes = -1;
        ImGui::CloseCurrentPopup();
      }

      //all_current_scenes.clear();

      ImGui::SameLine();

      if (ImGui::Button("Cancel##cancel load scene from combo"))
        ImGui::CloseCurrentPopup();

      ImGui::EndPopup();
    }
  #endif
  }
}