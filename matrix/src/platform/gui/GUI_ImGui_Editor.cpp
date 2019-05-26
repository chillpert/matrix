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

  static int item_objects_to_spawn = 0;
  const char* items[] = {"", "monkey", "cube", "rock", "sphere"};

  static bool show_event_window = 0;
  static std::string event_window_title = "undefined window title";
  static std::string event_window_message = "undefined window message";
  static std::string event_window_button = "undefined window button label";

  static bool show_input_window = 0;
  static std::string input_window_title = "undefined window title";
  static std::string input_window_message = "undefined window message";

  enum InputTypes
  {
    mx_name,      // string input
    mx_resolution // two integer input
  };

  InputTypes currentInputType = mx_name;

  /*
    #####################################################################
    Opens an input window for different input types defined by InputTypes
    #####################################################################
  */
  void openInputWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGui::Begin(input_window_title.c_str());
    ImGui::Text(input_window_message.c_str());

    switch (currentInputType)
    {
      // string
      case mx_name:
      {
        static char input[128];
        try 
        {
          ImGui::InputText("##type in name for object to spawn", input, IM_ARRAYSIZE(input));
        }
        catch (std::exception e)
        {
          MX_FATAL("MX: GUI: Input Window: " + std::string(e.what()));
        }

        if (ImGui::Button("confirm##confirm naming"))
        {
          std::vector<std::string> active_objects_s;
          World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);
          for (const std::string &it : active_objects_s)
          {
            if (it == input)
            {
              event_window_title = "Warning";
              event_window_message = "This name is already being used";
              event_window_button = "Confirm";
              show_event_window = 1;
              break;
            }
          }
          if (!strlen(input) == 0 && !show_event_window)
          {
            World::get().m_ActiveScene->push(input, items[item_objects_to_spawn] + std::string(".obj"));
            item_objects_to_spawn = 0;
            show_input_window = 0;
            memset(&input[0], 0, sizeof(input));
          }
        }
        break;
      }
      // two integer
      case mx_resolution:
      {
        static int input[2];
        try
        {
          ImGui::InputInt2("##resolution input int2", input, IM_ARRAYSIZE(input));
        }
        catch(const std::exception& e)
        {
          MX_FATAL("MX: GUI: Resolution Input Window: " + std::string(e.what()));
        }
    
        if (ImGui::Button("confirm##confirm resolution input"))
        {
          if (input[0] > 1920 || input[1] > 1080 || input[0] < 200 || input[1] < 200)
          {
            event_window_title = "Warning";
            event_window_message = "Invalid resolution";
            show_event_window = 1;
          }
          else
          {
            WindowResized event(input[0], input[1]);
            event.handle();
            LOGEVENT(event);
    
            if (input[0] == 1920 && input[1] == 1080)
              Application::get().m_Window->m_Props.m_FullScreen = 1;
    
            show_input_window = 0;
          }      
        }

        ImGui::SameLine();

        if (ImGui::Button("cancel"))
          show_input_window = 0;

        break;
      }
      default:
        break;
    }

    ImGui::End();
  #endif
  }

  void openEventWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGui::Begin(event_window_title.c_str());
    ImGui::Text(event_window_message.c_str());
    std::string buttonLabel = event_window_button + "##button labeling for event window";
    if (ImGui::Button(buttonLabel.c_str()))
      show_event_window = 0;
    ImGui::End();
  #endif
  }

  /*
    #####################################################################
                              main GUI function
    #####################################################################
  */
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

    if (show_event_window)
      openEventWindow();
    else if (show_input_window)
      openInputWindow();
    else
    {
    ImGui::Begin("World Editor", &p_open, window_flags);

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("scenes##manage scenes"))
      {
        if (ImGui::MenuItem("new##create new scene"))
        {

        }
        if (ImGui::MenuItem("load##load existing scene"))
        {

        }
        if (ImGui::MenuItem("open##opens scene from file"))
        {

        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("settings"))
      {
        if (ImGui::MenuItem("save"))
        {
          
        }
        if (ImGui::MenuItem("save as"))
        {

        }
        if (ImGui::MenuItem("import config"))
        {

        }
        if (ImGui::MenuItem("export config"))
        {

        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("help"))
      {
        if (ImGui::MenuItem("about"))
        {
          event_window_title = "About";
          event_window_message = "Waehlt die Partei,\ndenn sie ist sehr gut!";
          event_window_button = "Yes";
          show_event_window = 1;
        }
        if (ImGui::MenuItem("search"))
        {

        }
        if (ImGui::MenuItem("credits"))
        {

        }
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
          input_window_title = "Info";
          input_window_message = "Please enter a resolution";
          show_input_window = 1;
          currentInputType = mx_resolution;
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
      World::get().m_ActiveScene = World::get().m_ExistingScenes[item_current_scenes - 1];
      item_current_scenes = 0;
    }

    // display all active objects
    std::vector<std::string> active_objects_s;
    World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);
    
    ImGui::Text("select object:");
    ImGui::Combo("##all_objects_to_spawn", &item_objects_to_spawn, items, IM_ARRAYSIZE(items));

    ImGui::SameLine();

    // spawn selected object
    if (ImGui::Button("spawn") && item_objects_to_spawn != 0)
    {
      input_window_title = "Info";
      input_window_message = "Please enter a new name";
      show_input_window = 1;
      currentInputType = mx_name;
    }

    std::vector<const char*> all_active_objects;
    all_active_objects.resize(active_objects_s.size());

    for (unsigned int i = 0; i < active_objects_s.size(); ++i)
      all_active_objects[i] = active_objects_s[i].c_str();

    ImGui::Text("select model:");
    static int item_objects_to_select = 0;
    ImGui::Combo("##all_objects_to_delete", &item_objects_to_select, all_active_objects.data(), all_active_objects.size());

    ImGui::SameLine();

    // delete
    if (ImGui::Button("delete") && item_objects_to_select != 0)
    {
      World::get().m_ActiveScene->pop(active_objects_s.at(item_objects_to_select));
      item_objects_to_select = 0;
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

    ImGui::End();

  #endif
  }  
  }
}