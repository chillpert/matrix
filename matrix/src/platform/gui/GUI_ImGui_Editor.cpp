#include "matrix/src/Utils.h"
#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX
{
  static const float grab_speed = 0.001f;
  static const float transform_factor = 100.0f;

  static bool scene_name_accepted = 1;
  static bool scene_delete_accepted = 0;
  static bool object_name_accepted = 1;
  // static bool object_delete_accepted = 0;

  static bool show_transform_menu = 0;
  static bool show_scenes_menu = 1;
  static bool show_assets_menu = 0;

  static float x_drag = 0;
  static float y_drag = 0;
  static float z_drag = 0;

  static float prev_x_drag = 0;
  static float prev_y_drag = 0;
  static float prev_z_drag = 0;

  static int item_models = 0;
  static int item_objects = 0;
  static int item_shaders = 0;
  static int item_diffuse_map = 0;
  static int item_normal_map = 0;
  static int item_bump_map = 0;

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

  static void render_scenes_menu();
  static void render_node_menu();
  static void render_transform_menu();

  static void render_new_scene_popup();
  static void render_load_scene_combo_popup();
  static void render_spawn_object_popup();
  static void render_delete_scene_popup(std::shared_ptr<Scene> scene);
  static void render_load_scene_popup(std::shared_ptr<Scene> scene);

  void renderEditorWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 0;
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

    ImGui::Begin("World Editor", &p_open_editor, window_flags);

    if (!p_open_editor)
      editor_window_enabled = 0;

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::MenuItem("Scenes##manage scenes", "", true, !show_scenes_menu))
      {
        show_scenes_menu = 1;
        show_assets_menu = 0;
        show_transform_menu = 0;
      }

      if (ImGui::MenuItem("Assets##spawn object", "", true, !show_assets_menu))
      {
        show_scenes_menu = 0;
        show_assets_menu = 1;
        show_transform_menu = 0;
      }

      if (ImGui::MenuItem("Transform##apply transforms", "", true, !show_transform_menu))
      {
        show_scenes_menu = 0;
        show_assets_menu = 0;
        show_transform_menu = 1;
      }

      ImGui::EndMenuBar();
    }
    
    if (show_assets_menu && !show_scenes_menu && !show_transform_menu)
      render_node_menu();
    else if (!show_assets_menu && show_scenes_menu && !show_transform_menu)
      render_scenes_menu();
    else if (!show_assets_menu && !show_scenes_menu && show_transform_menu)
      render_transform_menu();

    ImGui::End();
  #endif
  }

  static void render_node_menu()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool needs_refresh = 1;

    static ImTextureID my_tex_id;
    static float my_tex_w;
    static float my_tex_h;

    static char object_name[128];
    ImGui::InputText("##give object an unique name", object_name, IM_ARRAYSIZE(object_name));
    ImGui::SameLine();

    if (ImGui::Button("spawn##object", ImVec2(60.0f, 20.0f)))
    {
      if (current_scene->push(object_name))
        current_node = current_scenegraph->search(object_name, current_root);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Combo("##objects to select", &item_objects, all_objects.data(), all_objects.size());
    ImGui::SameLine();

    if (ImGui::Button("load##object", ImVec2(60.0f, 20.0f)))
    {
      needs_refresh = 1;
      current_node = current_scenegraph->search(all_objects.at(item_objects), current_root);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (needs_refresh)
    {
      needs_refresh = 0;

      if (current_node != current_root)
      {
        for (u_int64_t i = 0; i < all_models.size(); ++i)
        {
          std::string rhs = all_models[i] + std::string(".obj");
          if (current_node->m_Model->m_Name == rhs)
            item_models = i;
        }

        for (u_int64_t i = 0; i < all_shaders.size(); ++i)
        {
          if (current_node->m_Shader->m_Name == all_shaders[i])
            item_shaders = i;
        }

        for (u_int64_t i = 0; i < all_diffuse_maps.size(); ++i)
        {
          std::string rhs = all_diffuse_maps[i] + std::string(".jpg");
          if (current_node->m_Texture->m_Name == rhs)
            item_diffuse_map = i;
        }

        for (u_int64_t i = 0; i < all_normal_maps.size(); ++i)
        {
          std::string rhs = all_normal_maps[i] + std::string(".jpg");
          if (current_node->m_Texture->m_Name == rhs)
            item_diffuse_map = i;
        }

        for (u_int64_t i = 0; i < all_bump_maps.size(); ++i)
        {
          std::string rhs = all_bump_maps[i] + std::string(".jpg");
          if (current_node->m_Texture->m_Name == rhs)
            item_diffuse_map = i;
        }

        if (current_node->m_Texture != nullptr)
        {
          my_tex_id = (void*)current_node->m_Texture->getID();
          my_tex_w = static_cast<float>(current_node->m_Texture->m_Stb.width);
          my_tex_h = static_cast<float>(current_node->m_Texture->m_Stb.height);
        }
      }
      else
      {
        item_models = 0;
        item_shaders = 0;
        item_diffuse_map = 0;
        item_normal_map = 0;
        item_bump_map = 0;
      }
    }

    if (current_node != current_root)
    {
      static bool render_file_inspector = 0;

      static int item_prev_models = item_models;
      static int item_prev_shaders = item_shaders;
      static int item_prev_diffuse_map = item_diffuse_map;
      static int item_prev_normal_map = item_normal_map;
      static int item_prev_bump_map = item_bump_map;

      ImGui::BeginChild("Model and Shader Group", ImVec2(0, 130), true);
      ImGui::BulletText("Model");
      ImGui::Combo("##model", &item_models, all_models.data(), IM_ARRAYSIZE(all_models.data()) * all_models.size());
      
      ImGui::NewLine();

      ImGui::BulletText("Shader");
      ImGui::Combo("##shader", &item_shaders, all_shaders.data(), IM_ARRAYSIZE(all_shaders.data()) * all_shaders.size());

      ImGui::EndChild();

      ImGui::NewLine();

      ImGui::BeginChild("Map Group", ImVec2(0, 160), true);

      ImGui::BulletText("Diffuse Map");
      ImGui::Combo("##diffuse map", &item_diffuse_map, all_diffuse_maps.data(), IM_ARRAYSIZE(all_diffuse_maps.data()) * all_diffuse_maps.size());
      ImGui::SameLine();

      if (ImGui::ImageButton(my_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / my_tex_w, 16.0f / my_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
        render_file_inspector = 1;

      ImGui::Spacing();
      ImGui::BulletText("Normal Map");
      ImGui::Combo("##normal map", &item_normal_map, all_normal_maps.data(), IM_ARRAYSIZE(all_normal_maps.data()) * all_normal_maps.size());

      ImGui::Spacing();
      ImGui::BulletText("Bump Map");
      ImGui::Combo("##bump map", &item_bump_map, all_bump_maps.data(), IM_ARRAYSIZE(all_bump_maps.data()) * all_bump_maps.size());

      ImGui::EndChild();
  
      if (item_prev_models != item_models)
      {
        current_node->setModel(std::static_pointer_cast<MX_MODEL>(World::get().m_Models[item_models]));
        item_prev_models = item_models;
      }

      if (item_prev_shaders != item_shaders)
      {
        current_node->setShader(std::static_pointer_cast<MX_SHADER>(World::get().m_Shaders[item_shaders]));
        item_prev_shaders = item_shaders;
      }

      if (item_prev_diffuse_map != item_diffuse_map)
      {
        current_node->setTexture(std::static_pointer_cast<MX_TEXTURE>(World::get().m_Textures[item_diffuse_map]));
        item_prev_diffuse_map = item_diffuse_map;
      }

      if (item_prev_normal_map != item_normal_map)
      {
        current_node->setTexture(std::static_pointer_cast<MX_TEXTURE>(World::get().m_Textures[item_normal_map]));
        item_prev_normal_map = item_normal_map;
      }

      if (item_prev_bump_map != item_bump_map)
      {
        current_node->setTexture(std::static_pointer_cast<MX_TEXTURE>(World::get().m_Textures[item_bump_map]));
        item_prev_bump_map = item_bump_map;
      }

      if (render_file_inspector)
      {
        ImGui::Begin("File Inspector", &render_file_inspector);
        ImGui::Text(current_node->m_Texture->m_Name.c_str());
        ImGui::Image((void*)current_node->m_Texture->getID(), ImVec2(my_tex_w / (my_tex_w / ImGui::GetWindowWidth()), my_tex_h / (my_tex_h / ImGui::GetWindowHeight())));
        ImGui::End();
      }
    }
  #endif
  }

  static void render_transform_menu()
  {
  #ifdef MX_IMGUI_ACTIVE
    SceneGraph *app_sg = &World::get().m_ActiveScene->m_Sg;

    prev_x_drag = x_drag;
    
    if (ImGui::DragFloat("x##x_slider", &x_drag, grab_speed))
    {
      try
      {
        std::shared_ptr<Node> temp = app_sg->search(all_objects.at(item_objects), std::shared_ptr<Node>(World::get().m_ActiveScene->m_Sg.m_Root));

        temp->setTransform(
          (x_drag > 0) ? (x_drag > prev_x_drag) ? RIGHT : LEFT : (x_drag > prev_x_drag) ? LEFT : RIGHT, 
          x_drag / transform_factor, 
          0
        );
      }
      catch (const std::exception &e) { } 
    }

    prev_y_drag = y_drag;
    
    if (ImGui::DragFloat("y##y_slider", &y_drag, grab_speed))
    {
      try
      {
        std::shared_ptr<Node> temp = app_sg->search(all_objects.at(item_objects), std::shared_ptr<Node>(World::get().m_ActiveScene->m_Sg.m_Root));

        temp->setTransform(
          (y_drag > 0) ? (y_drag > prev_y_drag) ? UP : DOWN : (y_drag > prev_y_drag) ? DOWN : UP, 
          y_drag / transform_factor,
          0
        );
      }
      catch(const std::exception& e) { }
    }
    
    prev_z_drag = z_drag;
    
    if (ImGui::DragFloat("z##z_slider", &z_drag, grab_speed))
    {
      try
      {
        std::shared_ptr<Node> temp = app_sg->search(all_objects.at(item_objects), std::shared_ptr<Node>(World::get().m_ActiveScene->m_Sg.m_Root));

        temp->setTransform(
          (z_drag > 0) ? (z_drag > prev_z_drag) ? FORWARDS : BACKWARDS : (z_drag > prev_z_drag) ? BACKWARDS : FORWARDS, 
          z_drag / transform_factor, 
          0
        );
      }
      catch (const std::exception &e) { }
    }
  #endif
  }

  static void render_scenes_menu()
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

    if (ImGui::Button("new##create new scene", ImVec2(106.0f, 20.0f)))
      ImGui::OpenPopup("Scene##create");

    render_new_scene_popup();

    ImGui::SameLine();

    if (ImGui::Button("load##load existing scene", ImVec2(106.0f, 20.0f)))
      ImGui::OpenPopup("Scene##load scene from combo");

    render_load_scene_combo_popup();

    for (auto it : *all_scenes)
    {
      if (ImGui::TreeNode((it->m_Name + "##scenes tree").c_str()))
      {
        if (it->m_Name != World::get().m_ActiveScene->m_Name)
        {
          if (ImGui::Button("load##load scene"))
            ImGui::OpenPopup("Scene##load");

          ImGui::SameLine();
        }
        
        if (World::get().m_ExistingScenes.size() > 1)
        {
          if (ImGui::Button("delete##delete scene"))
            ImGui::OpenPopup("Scene##delete");
        }

        render_load_scene_popup(it);
        render_delete_scene_popup(it);

        // scene properties
        std::string number_objects = "Objects: " + std::to_string(all_objects.size()); // needs to be fixed

        ImGui::Text(number_objects.c_str());
        ImGui::TreePop();
      }
    }
  #endif
  }

  static void render_new_scene_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("Scene##create", NULL, popup_flags))
    {      
      if (scene_name_accepted)
        ImGui::Text("Type in an unique name:");
      else
        ImGui::Text("Name already in use");

      static char input[128];
      ImGui::InputText("##type in name for object to spawn", input, IM_ARRAYSIZE(input));

      for (auto it : *all_scenes)
      {
        if (it->m_Name == input)
        {
          scene_name_accepted = 0;
          break;
        }
        else
          scene_name_accepted = 1;
      }
      
      if (ImGui::Button("Confirm##confirm create scene"))
      {
        if (!strlen(input) == 0 && scene_name_accepted)
        {
          World::get().push(std::shared_ptr<Scene>(new Scene(input)));
          memset(&input[0], 0, sizeof(input));
          
          ImGui::CloseCurrentPopup();
        }
      }

      ImGui::SameLine();
      if (ImGui::Button("Cancel##cancel create scene"))
      {
        scene_name_accepted = 1;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  #endif
  }

  static void render_delete_scene_popup(std::shared_ptr<Scene> scene)
  {
    if (ImGui::BeginPopupModal("Scene##delete", NULL, popup_flags))
    {
      if (World::get().m_ExistingScenes.size() > 1)
        scene_delete_accepted = 1;

      if (scene_delete_accepted)
        ImGui::Text("Do you really want to delete the scene?");
      else
        ImGui::Text("You can not delete this scene\nCreate a new one first!");

      if (ImGui::Button("Confirm##confirm delete scene"))
      {
        if (scene_delete_accepted)
        {
          for (std::vector<std::shared_ptr<Scene>>::iterator iter = (*all_scenes).begin(); iter != (*all_scenes).end(); ++iter)
          {
            if  ((*iter)->m_Name == scene->m_Name && iter != World::get().m_ExistingScenes.begin())
            {
              MX_INFO("MX: World: Deleting scene: " + (*iter)->m_Name);
              World::get().m_ExistingScenes.erase(iter);
              World::get().m_ActiveScene = World::get().m_ExistingScenes.at(0);
              break;
            }
          }
          ImGui::CloseCurrentPopup();
        }
        else
          ImGui::CloseCurrentPopup();
      }

      ImGui::SameLine();

      if (scene_delete_accepted)
      {
        if (ImGui::Button("Cancel##cancel delete scene"))
          ImGui::CloseCurrentPopup();
      }
      
      ImGui::EndPopup();
    }
  }

  static void render_load_scene_popup(std::shared_ptr<Scene> scene)
  {
    if (ImGui::BeginPopupModal("Scene##load", NULL, popup_flags))
    {
      // pseudo loading (just for prototyping)
      static float progress = 0.0f;
      static float progress_dir = 1.0f;
      progress += progress_dir * ImGui::GetIO().DeltaTime;

      ImGui::ProgressBar(progress, ImVec2(100.0f,0.0f));

      if (progress >= 1.0f /* changes are being discarded when swapping scenes */)
      {
        progress = 0.0f;
        World::get().m_ActiveScene = scene;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  }

  static void render_load_scene_combo_popup()
  {
    if (ImGui::BeginPopupModal("Scene##load scene from combo", NULL, popup_flags))
    {
      // display all scenes
      all_current_scenes.resize(World::get().m_ExistingScenes.size());

      for (unsigned int i = 0; i < World::get().m_ExistingScenes.size(); ++i)
        all_current_scenes[i] = World::get().m_ExistingScenes[i]->m_Name.c_str();

      static int item_current_scenes = 0;
      ImGui::Text("Select a scene to load:");
      ImGui::Combo("##all_scenes_to_select", &item_current_scenes, all_current_scenes.data(), all_current_scenes.size());

      ImGui::SameLine();

      if (ImGui::Button("Confirm##confirm load scene from combo", ImVec2(60.0f, 20.0f)))
      {
        World::get().m_ActiveScene = World::get().m_ExistingScenes[item_current_scenes];
        item_current_scenes = 0;
        ImGui::CloseCurrentPopup();
      }

      all_current_scenes.clear();

      ImGui::SameLine();

      if (ImGui::Button("Cancel##cancel load scene from combo"))
        ImGui::CloseCurrentPopup();

      ImGui::EndPopup();
    }
  }

  static void render_spawn_object_popup()
  {
    if (ImGui::BeginPopupModal("Object##spawn object", NULL, popup_flags))
    {
      if (object_name_accepted)
        ImGui::Text("Give the object an unique name:");
      else
        ImGui::Text("Name is already being used");
      
      static char input[128];
      ImGui::InputText("##type in name for object to spawn", input, IM_ARRAYSIZE(input));

      for (const std::string &it : all_objects)
      {
        if (it == input)
        {
          object_name_accepted = 0;
          break;
        }
        else
          object_name_accepted = 1;
      }
      if (ImGui::Button("Confirm##confirm spawn object") && !strlen(input) == 0 && object_name_accepted)
      {
        World::get().m_ActiveScene->push(input);
        memset(&input[0], 0, sizeof(input));
        ImGui::CloseCurrentPopup();
      }

      ImGui::SameLine();

      if (ImGui::Button("Cancel##cancle spawn object"))
      {
        object_name_accepted = 1;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  }
}