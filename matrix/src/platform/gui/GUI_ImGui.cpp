#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/platform/window/Window_SDL2.h"
#include "matrix/src/platform/window/Window_GLFW.h"

#ifdef MX_IMGUI_ACTIVE

#include <IMGUI/imgui.h>
#ifdef MX_GLFW_ACTIVE
  #include <IMGUI/imgui_impl_glfw.h>
  #define MX_IMGUI_INIT       ImGui_ImplGlfw_InitForOpenGL(Window_GLFW::get().getWindow(), true);
  #define MX_IMGUI_NEW_FRAME  ImGui_ImplGlfw_NewFrame();
  #define MX_IMGUI_CLEAN      ImGui_ImplGlfw_Shutdown();
#elif MX_SDL2_ACTIVE
  #include <IMGUI/imgui_impl_sdl.h>
  #define MX_IMGUI_INIT       ImGui_ImplSDL2_InitForOpenGL(Window_SDL2::get().getWindow(), Window_SDL2::get().getContext());
  #define MX_IMGUI_NEW_FRAME  ImGui_ImplSDL2_NewFrame(Window_SDL2::get().getWindow());
  #define MX_IMGUI_CLEAN      ImGui_ImplSDL2_Shutdown();
#endif
#ifdef MX_OPENGL_ACTIVE
  #define MX_IMGUI_API_RENDER ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  #define MX_IMGUI_API_CLOSE  ImGui_ImplOpenGL3_Shutdown();
#elif MX_DIRECTX_ACTIVE
  #define MX_IMGUI_API
#endif
#include <IMGUI/imgui_impl_opengl3.h>

#endif

#include "matrix/src/layers/World.h"
#include "matrix/src/layers/Scene.h"
#include "matrix/src/platform/api/Model.h"
#ifdef MX_OPENGL_ACTIVE 
  #include "matrix/src/platform/api/Model_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
#endif

namespace MX
{
  void GUI_ImGui::initialize()
  {
    #ifdef MX_IMGUI_ACTIVE
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::StyleColorsDark();
      MX_IMGUI_INIT;
      ImGui_ImplOpenGL3_Init("#version 330");
    #endif
  }

  void GUI_ImGui::update()
  {
    #ifdef MX_IMGUI_ACTIVE
      ImGui_ImplOpenGL3_NewFrame();
      MX_IMGUI_NEW_FRAME;
      ImGui::NewFrame();
    #endif
  }

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
  }

  void GUI_ImGui::render()
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

      static int item_current_Scenes = 0;
      const char* items_Scenes[] = {"main menu", "tutorial", "jungle"};
      ImGui::Combo("select Scene", &item_current_Scenes, items_Scenes, IM_ARRAYSIZE(items_Scenes));

      if (ImGui::Button("add"))
      {
        MX_WARN("button add pressed");
      }

      ImGui::SameLine();

      if (ImGui::Button("delete"))
      { 
        MX_WARN("button delete pressed");
      }

      ImGui::NewLine();

      const char* items[] = {"...", "monkey", "cube", "rock", "sphere"};
      
      static int item_objects_to_spawn = 0;
      ImGui::Text("select object:");
      ImGui::Combo("##objects_list", &item_objects_to_spawn, items, IM_ARRAYSIZE(items));

      if (enter_name)
        enterNameWindow();

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

      if (ImGui::Button("delete monkey"))
      {
        MX_WARN("active scene: " + World::get().m_ActiveScene->m_Name);
        for (const auto &it : World::get().m_ActiveScene->m_Sg.m_Root->getChildren())
        {
          std::cout << it->m_Name << ", ";
        }

        std::cout << std::endl;
        
        MX_SUCCESS(World::get().m_ActiveScene->m_Sg.recursive_search("monkey1", World::get().m_ActiveScene->m_Sg.m_Root)->m_Name + " found!");
      }
      
/*
      // delete selected object
      if (ImGui::Button("delete"))
      {
        if (item_current_objects == 1)
        {
          item_current_objects = 0;

          // World::get().m_ActiveScene->pop("monkey.obj");
          MX_WARN("monkey deleted");
        }
      }
*/
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

      ImGui::Render();
      MX_IMGUI_API_RENDER;
    #endif
  }

  void GUI_ImGui::clean()
  {
    #ifdef MX_IMGUI_ACTIVE
      MX_IMGUI_API_CLOSE;
      MX_IMGUI_CLEAN;
      ImGui::DestroyContext();
    #endif
  }
}