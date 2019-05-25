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

  static bool no_titlebar = false;
  static bool no_scrollbar = false;
  static bool no_menu = false;
  static bool no_move = true;
  static bool no_resize = false;
  static bool no_collapse = false;
  static bool no_close = false;
  static bool no_nav = false;
  static bool no_background = false;
  static bool no_bring_to_front = false;
  static bool p_open = true;
  static bool enter_name = false;

  void enterNameWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGui::Begin("new Window");
    
    ImGui::Text("hello there");

    static char input[128];
    static int i0 = 123;
    ImGui::InputText("input text", input, IM_ARRAYSIZE(input));

    if (ImGui::Button("confirm")) // && name not already used)
    {
      enter_name = 0;
    }

    ImGui::End();
  #endif
  }

  void renderEditor()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    ImGui::Begin("World Editor", &p_open, window_flags);

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("projects"))
      {
        if (ImGui::MenuItem("new")) {}
        if (ImGui::MenuItem("open")) {}
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("settings"))
      {
        if (ImGui::MenuItem("save")) {}
        if (ImGui::MenuItem("save as")) {}
        if (ImGui::MenuItem("import config")) {}
        if (ImGui::MenuItem("export config")) {}
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("help"))
      {
        if (ImGui::MenuItem("about")) {}
        if (ImGui::MenuItem("search")) {}
        if (ImGui::MenuItem("credits")) {}
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("screen"))
      {
        if (ImGui::MenuItem("toggle max size"))
        {
          if (Application::get().m_Window->m_Props.m_FullScreen == 0)
          {
            WindowResized event(1920, 1080);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 1;
          }
          else
          {
            WindowResized event(initial_window_width, initial_window_height);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 0;
          }
        }
        if (ImGui::MenuItem("set resolution"))
        {

        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    // display all scenes
    std::vector<const char*> all_current_scenes;
    all_current_scenes.resize(World::get().m_ExistingScenes.size() + 1);
    all_current_scenes[0] = World::get().m_ActiveScene->m_Name.c_str();

    for (unsigned int i = 0; i < World::get().m_ExistingScenes.size(); ++i)
      all_current_scenes[i+1] = World::get().m_ExistingScenes[i]->m_Name.c_str();

    static int item_current_scenes = 0;
    ImGui::Text("select scene:");
    ImGui::Combo("##all_scenes_to_select", &item_current_scenes, all_current_scenes.data(), all_current_scenes.size());

    ImGui::SameLine();

    if (ImGui::Button("load"))
    {
      if (item_current_scenes == 1)
      {
        World::get().m_ActiveScene = World::get().m_ExistingScenes[0];
        item_current_scenes = 0;
      }

      if (item_current_scenes == 2)
      {
        World::get().m_ActiveScene = World::get().m_ExistingScenes[1];
        item_current_scenes = 0;
      }
    }

    const char* items[] = {"", "monkey", "cube", "rock", "sphere"};
    
    static int item_objects_to_spawn = 0;
    ImGui::Text("select object:");
    ImGui::Combo("##all_objects_to_spawn", &item_objects_to_spawn, items, IM_ARRAYSIZE(items));

    if (enter_name)
      enterNameWindow();

    ImGui::SameLine();

    // spawn selected object
    if (ImGui::Button("spawn"))
    {
      if (item_objects_to_spawn == 1)
      {
        item_objects_to_spawn = 0;
        World::get().m_ActiveScene->push("monkey1", "monkey.obj");
      }

      if (item_objects_to_spawn == 2)
      {
        item_objects_to_spawn = 0;
        World::get().m_ActiveScene->push("cube1", "cube.obj");
      }

      if (item_objects_to_spawn == 3)
      {
        item_objects_to_spawn = 0;
        World::get().m_ActiveScene->push("rock1", "rock.obj");
      }

      if (item_objects_to_spawn == 4)
      {
        item_objects_to_spawn = 0;
        World::get().m_ActiveScene->push("sphere1", "sphere.obj");
      }
    }

    // display all active objects
    std::vector<std::string> active_objects_s;
    World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);

    std::vector<const char*> all_active_objects;
    all_active_objects.resize(active_objects_s.size());

    for (unsigned int i = 0; i < active_objects_s.size(); ++i)
      all_active_objects[i] = active_objects_s[i].c_str();

    ImGui::Text("select object:");
    static int item_objects_to_delete = 0;
    ImGui::Combo("##all_objects_to_delete", &item_objects_to_delete, all_active_objects.data(), all_active_objects.size());

    ImGui::SameLine();

    // delete
    if (ImGui::Button("delete"))
    {
      if (item_objects_to_delete == 1)
      {
        item_objects_to_delete = 0;
        World::get().m_ActiveScene->pop(active_objects_s.at(1));
      }

      if (item_objects_to_delete == 2)
      {
        item_objects_to_delete = 0;
        World::get().m_ActiveScene->pop(active_objects_s.at(2));  
      }

      if (item_objects_to_delete == 3)
      {
        item_objects_to_delete = 0;
        World::get().m_ActiveScene->pop(active_objects_s.at(3));
      }

      if (item_objects_to_delete == 4)
      {
        item_objects_to_delete = 0;
        World::get().m_ActiveScene->pop(active_objects_s.at(4));
      }
    }
    
    //ImGui::Checkbox("Rotate", &rotateFlag);
    //ImGui::SliderFloat("Speed:", &)

    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Scale"))
    {
      ImGui::SliderFloat("x", &xSlider, 0.0f, 100.0f);
      ImGui::SliderFloat("y", &ySlider, 0.0f, 100.0f);
      ImGui::SliderFloat("z", &zSlider, 0.0f, 100.0f);
    }
    if (ImGui::CollapsingHeader("Rotate"))
    {
      ImGui::Text("add rotation implementation");
    }
    if (ImGui::CollapsingHeader("Translate"))
    {
      ImGui::Text("nothing to be seen here");
    }

    ImGui::End();

  #endif
  }  
}