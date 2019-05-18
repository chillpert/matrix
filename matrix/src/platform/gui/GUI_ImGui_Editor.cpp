#include "matrix/src/platform/gui/GUI_ImGui.h"

namespace MX
{
  static float xSlider = 0.0f;
  static float ySlider = 0.0f;
  static float zSlider = 0.0f;

  static bool no_titlebar = false;
  static bool no_scrollbar = false;
  static bool no_menu = false;
  static bool no_move = false;
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
        ImGui::MenuItem("new");
        ImGui::MenuItem("open");
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("settings"))
      {
        ImGui::MenuItem("save");
        ImGui::MenuItem("save as");
        ImGui::MenuItem("import config");
        ImGui::MenuItem("export config");
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("help"))
      {
        ImGui::MenuItem("about");
        ImGui::MenuItem("search");
        ImGui::MenuItem("credits");
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    // display all scenes
    const char* available_scenes[World::get().m_ExistingScenes.size() + 1];
    available_scenes[0] = World::get().m_ActiveScene->m_Name.c_str();

    for (unsigned int i = 0; i < World::get().m_ExistingScenes.size(); ++i)
      available_scenes[i+1] = World::get().m_ExistingScenes[i]->m_Name.c_str();

    static int item_current_scenes = 0;
    ImGui::Text("select scene:");
    ImGui::Combo("##all_scenes_to_select", &item_current_scenes, available_scenes, IM_ARRAYSIZE(available_scenes));

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
        //enter_name = 1;
        //if (!enter_name)
        //{
          World::get().m_ActiveScene->push("monkey1", "monkey.obj");
          item_objects_to_spawn = 0;
          MX_WARN("monkey spawned");
        //}
      }

      if (item_objects_to_spawn == 2)
      {
        item_objects_to_spawn = 0;
        
        World::get().m_ActiveScene->push("cube1", "cube.obj");
        MX_WARN("cube spawned");
      }

      if (item_objects_to_spawn == 3)
      {
        item_objects_to_spawn = 0;
        
        World::get().m_ActiveScene->push("rock1", "rock.obj");
        MX_WARN("rock spawned");
      }

      if (item_objects_to_spawn == 4)
      {
        item_objects_to_spawn = 0;
        
        World::get().m_ActiveScene->push("sphere1", "sphere.obj");
        MX_WARN("sphere spawned");
      }
    }

    // display all active objects
    std::vector<std::string> active_objects_s;
    std::vector<char*> active_objects_c;

    World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);

    std::transform(active_objects_s.begin(), active_objects_s.end(), std::back_inserter(active_objects_c), [](const std::string &s){
      char *pc = new char[s.size()+1];
      std::strcpy(pc, s.c_str());
      return pc;
    });

    const char* active_objects[active_objects_s.size()];
    for (unsigned int i = 0; i < active_objects_s.size(); ++i)
    {
      active_objects[i] = active_objects_c[i];
    }

    ImGui::Text("select object:");
    static int item_objects_to_delete = 0;
    ImGui::Combo("##all_objects_to_delete", &item_objects_to_delete, active_objects, IM_ARRAYSIZE(active_objects));

    ImGui::SameLine();

    // delete
    if (ImGui::Button("delete"))
    {
/*
      MX_WARN("before scene: " + World::get().m_ActiveScene->m_Name);
      for (const auto &it : World::get().m_ActiveScene->m_Sg.m_Root->getChildren())
      {
        std::cout << it->m_Name << ": " << it << std::endl;
      }

      Node *t = &World::get().m_ActiveScene->m_Sg.recursive_search("monkey1", World::get().m_ActiveScene->m_Sg.m_Root); 
      std::cout << "pls: " << t << std::endl;
*/
      //World::get().m_ActiveScene->m_Sg.recursive_delete(&World::get().m_ActiveScene->m_Sg.recursive_search("monkey1", World::get().m_ActiveScene->m_Sg.m_Root));
/*
      MX_WARN("after delete: " + World::get().m_ActiveScene->m_Name);
      for (const auto &it : World::get().m_ActiveScene->m_Sg.m_Root->getChildren())
      {
        std::cout << it->m_Name << ": " << it << std::endl;
      }
*/
      if (item_objects_to_delete == 1)
      {
        MX_FATAL("deleting " + active_objects_s.at(1));
        World::get().m_ActiveScene->m_Sg.recursive_delete(&World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(1), World::get().m_ActiveScene->m_Sg.m_Root));
        item_objects_to_delete = 0;
      }

      if (item_objects_to_delete == 2)
      {
        MX_FATAL("deleting " + active_objects_s.at(2));
        World::get().m_ActiveScene->m_Sg.recursive_delete(&World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(2), World::get().m_ActiveScene->m_Sg.m_Root));
        item_objects_to_delete = 0;
      }

      if (item_objects_to_delete == 3)
      {
        MX_FATAL("deleting cube" + active_objects_s.at(3));
        World::get().m_ActiveScene->m_Sg.recursive_delete(&World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(3), World::get().m_ActiveScene->m_Sg.m_Root));
        item_objects_to_delete = 0;
      }

      if (item_objects_to_delete == 4)
      {
        MX_FATAL("deleting cube" + active_objects_s.at(4));
        World::get().m_ActiveScene->m_Sg.recursive_delete(&World::get().m_ActiveScene->m_Sg.recursive_search(active_objects_s.at(4), World::get().m_ActiveScene->m_Sg.m_Root));
        item_objects_to_delete = 0;
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