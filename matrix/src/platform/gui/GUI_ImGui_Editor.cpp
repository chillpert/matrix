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
  static void render_assets_menu();
  static void render_transform_menu();

  static void render_new_scene_popup();
  static void render_load_scene_combo_popup();
  static void render_spawn_object_popup();
  static void render_delete_scene_popup(Scene *scene);
  static void render_load_scene_popup(Scene *scene);

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

    // update container of existing objects in active scene
    World::get().m_ActiveScene->m_Sg.getAllObjects(&all_current_objects, World::get().m_ActiveScene->m_Sg.m_Root);

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
      render_assets_menu();
    else if (!show_assets_menu && show_scenes_menu && !show_transform_menu)
      render_scenes_menu();
    else if (!show_assets_menu && !show_scenes_menu && show_transform_menu)
      render_transform_menu();

    ImGui::End();
  #endif
  }

  static void render_assets_menu()
  {
  #ifdef MX_IMGUI_ACTIVE    
    ImGui::Text("models:");
    ImGui::Combo("##all_objects_to_spawn", &item_objects_to_spawn, all_available_models.data(), IM_ARRAYSIZE(all_available_models.data()) * all_available_models.size());
    
    ImGui::SameLine();

    // spawn selected object
    if (ImGui::Button("spawn", ImVec2(60.0f, 20.0f)) && item_objects_to_spawn != 0)
      ImGui::OpenPopup("Object##spawn object");

    render_spawn_object_popup();

    ImGui::Separator();

    ImGui::Text("objects:");
    ImGui::Combo("##all_objects_to_delete", &item_objects_to_select, all_current_objects.data(), all_current_objects.size());

    ImGui::SameLine();

    // delete
    if (ImGui::Button("delete", ImVec2(60.0f, 20.0f)) && item_objects_to_select != 0)
    {
      World::get().m_ActiveScene->pop(all_current_objects.at(item_objects_to_select));
      item_objects_to_select = 0;
    }

    ImGui::Text("shaders:");
    ImGui::Combo("##all_shaders_to_select", &item_shaders_to_select, all_available_shaders.data(), IM_ARRAYSIZE(all_available_shaders.data()) * all_available_shaders.size());
    ImGui::SameLine();

    // select shader
    if (ImGui::Button("load##select shader", ImVec2(60.0f, 20.0f)) && item_shaders_to_select != 0)
    {
      try
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(all_current_objects.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);
      
        for (auto *it : World::get().m_Shaders)
        {
          if (it->getName() == all_available_shaders.at(item_shaders_to_select))
          {
            search_holder->m_Shader = it;
            MX_INFO("MX: Node: " + search_holder->m_Name + ": Set Shader: " + it->getName());
            search_holder = nullptr;
          }
        }
      }
      catch (const std::exception &e) { }

      item_shaders_to_select = 0;
    }

    ImGui::Text("textures:");
    ImGui::Combo("##all_textures_to_select", &item_texture_to_select, all_available_textures.data(), IM_ARRAYSIZE(all_available_textures.data()) * all_available_textures.size());
    ImGui::SameLine();

    // select texture
    if (ImGui::Button("load##select texture", ImVec2(60.0f, 20.0f)) && item_texture_to_select != 0)
    {
      try
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(all_current_objects.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

        for (auto *it : World::get().m_Textures)
        {
          // remove file format ending
          std::string temp = it->getName();
          temp = temp.substr(0, temp.find_last_of("."));

          if (temp == all_available_textures.at(item_texture_to_select))
          {
          #ifdef MX_INSTANT_SHADER_INIT
            it->initialize();
          #endif
            search_holder->m_Texture = it;
            MX_INFO("MX: Node: " + search_holder->m_Name + ": Set texture: " + it->getName());
            search_holder = nullptr;
          }
        }
      }
      catch (const std::exception &e) { }
  
      item_texture_to_select = 0;
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
        Node *temp = app_sg->search(all_current_objects.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

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
        Node *temp = app_sg->search(all_current_objects.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

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
        Node *temp = app_sg->search(all_current_objects.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

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

    for (auto *it : World::get().m_ExistingScenes)
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
        std::string number_objects = "Objects: " + std::to_string(all_current_objects.size()); // needs to be fixed

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

      for (Scene *it : World::get().m_ExistingScenes)
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
          Scene *temp = new Scene(input);
          World::get().push(temp);
          MX_INFO("MX: Scene: Switching from " + World::get().m_ActiveScene->m_Name + " to " + temp->m_Name);
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

  static void render_delete_scene_popup(Scene *scene)
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
          for (std::vector<Scene*>::iterator iter = World::get().m_ExistingScenes.begin(); iter != World::get().m_ExistingScenes.end(); ++iter)
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

  static void render_load_scene_popup(Scene *scene)
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

      for (const std::string &it : all_current_objects)
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
        World::get().m_ActiveScene->push(input, all_available_models[item_objects_to_spawn] + std::string(".obj"), all_current_objects.at(item_objects_to_select));
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