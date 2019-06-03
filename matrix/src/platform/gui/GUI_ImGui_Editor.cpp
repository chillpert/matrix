#include "matrix/src/Utils.h"
#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX
{
  static float xSlider = 0.0f;
  static float ySlider = 0.0f;
  static float zSlider = 0.0f;

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

  void GUI_ImGui::renderEditorWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
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
      if (ImGui::BeginMenu("scenes##manage scenes"))
      {
        if (ImGui::MenuItem("new##create new scene"))
        {
          event_window_title = "Info";
          event_window_message = "Give the scene a new name";
          input_window_enabled = 1;
          currentSelectionType = mx_scene;
          currentInputType = mx_name;
        }
        if (ImGui::MenuItem("load##load existing scene"))
        {
          event_window_title = "Info";
          event_window_message = "Select a scene to load";
          event_window_button = "Load";
          selection_window_enabled = 1;
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("add##spawn object"))
      {
        if (ImGui::MenuItem("object#spawn object from editor window"))
        {
          // todo
        }
      }
      ImGui::EndMenuBar();
    }

    // display all active objects
    World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);
    
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

    std::vector<const char*> all_active_objects;
    all_active_objects.resize(active_objects_s.size());

    for (unsigned int i = 0; i < active_objects_s.size(); ++i)
      all_active_objects[i] = active_objects_s[i].c_str();

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
      World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);
      search_holder->m_ShaderName = all_available_shaders.at(item_shaders_to_select);
      item_shaders_to_select = 0;
    }

    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Translate"))
    {
      static bool movedSlider = 0;

      ImGui::Text("X - Axis");
      if (ImGui::Button("+ ##x+"))
      {
        xSlider += 0.2f;
        movedSlider = 1;
      }
      ImGui::SameLine();
      if (ImGui::Button("- ##x-"))
      {
        xSlider -= 0.2f;
        movedSlider = 1;
      }
      
      ImGui::Text("Y - Axis");
      if (ImGui::Button("+ ##y+"))
      {
        ySlider += 0.2f;
        movedSlider = 1;
      }
      ImGui::SameLine();
      if (ImGui::Button("- ##y-"))
      {
        ySlider -= 0.2f;
        movedSlider = 1;
      }
      
      ImGui::Text("Z - Axis");
      if (ImGui::Button("+ ##z+"))
      {
        zSlider += 0.2f;
        movedSlider = 1;
      }
      ImGui::SameLine();
      if (ImGui::Button("- ##z-"))
      {
        zSlider -= 0.2f;
        movedSlider = 1;
      }

      if (movedSlider)
      {
        World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(item_objects_to_select), World::get().m_ActiveScene->m_Sg.m_Root);
        glm::fmat4 model_matrix = glm::fmat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(xSlider, ySlider, zSlider));
        search_holder->setLocalTransform(model_matrix);
        movedSlider = 0;
      }
    }

    active_objects_s.clear();

    ImGui::End();
  #endif
  }
}