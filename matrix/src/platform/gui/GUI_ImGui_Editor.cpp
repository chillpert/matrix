#include "matrix/src/Utils.h"
#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX
{
  static const float grab_speed = 0.001f;
  static const float transform_factor = 100.0f;

  static float x_drag = 0;
  static float y_drag = 0;
  static float z_drag = 0;

  static float prev_x_drag = 0;
  static float prev_y_drag = 0;
  static float prev_z_drag = 0;

 

  static void render_scenes_menu();
  static void render_assets_menu();
  static void render_transform_menu();

  void GUI_ImGui::renderEditorWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 0;
    static bool no_move = 1;
    static bool no_resize = 1;
    static bool no_collapse = 1;
    static bool no_close = 0;
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

    std::string editor_window_title = "World Editor - " + World::get().m_ActiveScene->m_Name;
    ImGui::Begin(editor_window_title.c_str(), &p_open_editor, window_flags);

    if (!p_open_editor)
      editor_window_enabled = 0;

    if (hierarchy_window_enabled)
    {
      ImGui::SetWindowPos(ImVec2(0.0f, 20.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f));
    }
    else
    {
      ImGui::SetWindowPos(ImVec2(0.0f, 20.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));
    }
    
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

    // display all active objects
    World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);
    all_active_objects.resize(active_objects_s.size());

    for (unsigned int i = 0; i < active_objects_s.size(); ++i)
      all_active_objects[i] = active_objects_s[i].c_str();
    
    if (show_assets_menu && !show_scenes_menu && !show_transform_menu)
      render_assets_menu();
    else if (!show_assets_menu && show_scenes_menu && !show_transform_menu)
      render_scenes_menu();
    else if (!show_assets_menu && !show_scenes_menu && show_transform_menu)
      render_transform_menu();

    active_objects_s.clear();

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
    {
      event_window_title = "Info";
      event_window_message = "Please enter a new name";
      input_window_enabled = 1;
      currentSelectionType = mx_object;
      currentInputType = mx_name;
    }

    ImGui::Separator();

    ImGui::Text("objects:");
    ImGui::Combo("##all_objects_to_delete", &item_objects_to_select, all_active_objects.data(), all_active_objects.size());

    ImGui::SameLine();

    // delete
    if (ImGui::Button("delete", ImVec2(60.0f, 20.0f)) && item_objects_to_select != 0)
    {
      World::get().m_ActiveScene->pop(active_objects_s.at(item_objects_to_select));
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
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);
      
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
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

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
    prev_x_drag = x_drag;
    
    if (ImGui::DragFloat("x##x_slider", &x_drag, grab_speed))
    {
      try
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

        search_holder->setTransform(
          (x_drag > 0) ? (x_drag > prev_x_drag) ? RIGHT : LEFT : (x_drag > prev_x_drag) ? LEFT : RIGHT, 
          x_drag / transform_factor, 
          0
        );
      }
      catch (const std::exception &e) { } 
      
      search_holder = nullptr;
    }

    prev_y_drag = y_drag;
    
    if (ImGui::DragFloat("y##y_slider", &y_drag, grab_speed))
    {
      try
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

        search_holder->setTransform(
          (y_drag > 0) ? (y_drag > prev_y_drag) ? UP : DOWN : (y_drag > prev_y_drag) ? DOWN : UP, 
          y_drag / transform_factor, 
          0
        );
      }
      catch(const std::exception& e) { }

      search_holder = nullptr;
    }
    
    prev_z_drag = z_drag;
    
    if (ImGui::DragFloat("z##z_slider", &z_drag, grab_speed))
    {
      try
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);

        search_holder->setTransform(
          (z_drag > 0) ? (z_drag > prev_z_drag) ? FORWARDS : BACKWARDS : (z_drag > prev_z_drag) ? BACKWARDS : FORWARDS, 
          z_drag / transform_factor, 
          0
        );
      }
      catch (const std::exception &e) { }
      
      search_holder = nullptr;
    }
  }

  static void render_scenes_menu()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::Button("new##create new scene", ImVec2(106.0f, 20.0f)))
    {
      event_window_title = "Info";
      event_window_message = "Give the scene a new name";
      input_window_enabled = 1;
      currentSelectionType = mx_scene;
      currentInputType = mx_name;
    }

    ImGui::SameLine();

    if (ImGui::Button("load##load existing scene", ImVec2(106.0f, 20.0f)))
    {
      event_window_title = "Info";
      event_window_message = "Select a scene to load";
      event_window_button = "Load";
      selection_window_enabled = 1;
    }

    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 1;
    static bool no_resize = 1;
    static bool no_collapse = 1;
    static bool no_close = 0;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;
    static bool p_open = 1;

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

    for (auto *it : World::get().m_ExistingScenes)
    {
      if (ImGui::TreeNode((it->m_Name + "##scenes tree").c_str()))
      {
        if (ImGui::Button("load##load scene"))
        {
          World::get().m_ActiveScene = it;
        }

        ImGui::SameLine();

        if (ImGui::Button("delete##delete scene"))
          ImGui::OpenPopup("Delete?");

        std::string number_objects = "Objects: " + std::to_string(all_active_objects.size());
        ImGui::Text(number_objects.c_str());
/*
        auto cam = it->m_Cam.getPosition();
        std::string camera_position = "Camera: " + f_str(cam.x, 2) + ", " + f_str(cam.y, 2) + ", " + f_str(cam.z, 2);
        ImGui::Text(camera_position.c_str());
*/
        if (ImGui::BeginPopupModal("Delete?", &p_open, window_flags))
        {
          ImGui::Text("Do you really want to delete the scene?");
          if (ImGui::Button("Confirm##confirm delete scene"))
          {
            ImGui::CloseCurrentPopup();
          }

          ImGui::SameLine();
          if (ImGui::Button("Cancel##cancel delete scene"))
          {
            ImGui::CloseCurrentPopup();
          }

          ImGui::EndPopup();
        }

        ImGui::TreePop();
      }
    }
  }
  #endif
}