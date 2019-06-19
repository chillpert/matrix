#include <GUI_ImGui.h>
#include <Window.h>
#include <Window_SDL2.h>
#include <Application.h>

#ifdef MX_IMGUI_ACTIVE
  #include <imgui_impl_sdl.h>
  #define MX_IMGUI_INIT       ImGui_ImplSDL2_InitForOpenGL(\
                                static_cast<Window_SDL2*>(Application::get().m_Window->getWindow())->m_Window,\
                                static_cast<Window_SDL2*>(Application::get().m_Window->getWindow())->m_Context\
                              );
  #define MX_IMGUI_NEW_FRAME  ImGui_ImplSDL2_NewFrame(static_cast<Window_SDL2*>(Application::get().m_Window->getWindow())->m_Window);
  #define MX_IMGUI_CLEAN      ImGui_ImplSDL2_Shutdown();

#ifdef MX_OPENGL_ACTIVE
  #define MX_IMGUI_API_RENDER ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  #define MX_IMGUI_API_CLOSE  ImGui_ImplOpenGL3_Shutdown();
#elif MX_DIRECTX_ACTIVE
  #define MX_IMGUI_API
#endif
#include <imgui_impl_opengl3.h>

#endif

namespace MX
{
  static bool first_run = 1;
  static bool dockspace_p_open = 1;
  MX_TEXTURE play_button("elon.jpg");

  ImFont* font_global;

  void GUI_ImGui::initialize()
  {
  #ifdef MX_IMGUI_ACTIVE
  
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    std::string font_file = MX_FONTS_PATH + std::string("DroidSans.ttf");
    font_global = io.Fonts->AddFontFromFileTTF(font_file.c_str(), 15.0f);
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 0.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.11f, 0.11f, 0.11f, 0.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.20f, 0.20f, 0.20f, 0.33f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.68f, 0.68f, 0.68f, 0.31f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.34f, 0.51f, 0.38f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.16f, 0.31f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.16f, 0.31f, 0.20f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    current_root = MX_WORLD.m_ActiveScene->m_Sg.m_Root;
    current_node = current_root;

    play_button.initialize();

    MX_IMGUI_INIT
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // reserve memory for incoming mx-logger messages
    logger_messages_for_gui.reserve(5000);
  #endif
  }

  void GUI_ImGui::update()
  {
  #ifdef MX_IMGUI_ACTIVE
    current_scene = MX_WORLD.m_ActiveScene;
    current_scenegraph = &MX_WORLD.m_ActiveScene->m_Sg;
    current_root = MX_WORLD.m_ActiveScene->m_Sg.m_Root;
    all_scenes = &MX_WORLD.m_ExistingScenes;

    all_objects.clear();
    current_scene->m_Sg.getAllObjects(all_objects, current_scene->m_Sg.m_Root);

    ImGui_ImplOpenGL3_NewFrame();
    MX_IMGUI_NEW_FRAME
    ImGui::NewFrame();
  #endif
  }

  void GUI_ImGui::render()
  {
  #ifdef MX_IMGUI_ACTIVE
    // set font
    ImGui::PushFont(font_global);
    ImGui::PopFont();

    renderDockSpace();
    renderViewport();

    if (demo_window_enabled)
      ImGui::ShowDemoWindow();
    if (menubar_enabled)
      renderMenuBar();
    if (editor_window_enabled)
      renderEditorWindow();
    if (hierarchy_window_enabled)
      renderHierarchyWindow();
    if (logger_window_enabled)
      renderLoggerWindow();
    if (file_inspector_enabled)
      renderFileInspectorWindow();

    ImGui::Render();
    MX_IMGUI_API_RENDER
  #endif
  }

  void GUI_ImGui::clean()
  {
  #ifdef MX_IMGUI_ACTIVE
    MX_IMGUI_API_CLOSE
    MX_IMGUI_CLEAN
    ImGui::DestroyContext();

    // delete allocated chars
    for (std::vector<const char*>::iterator iter = all_models.begin() + 1; iter != all_models.end(); ++iter)
      delete *iter;

  #endif
  }

  void renderDockSpace()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspace_p_open, window_flags);
    ImGui::PopStyleVar();

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (opt_fullscreen)
      ImGui::PopStyleVar(2);

    ImGui::End();

  #endif
  }

  void renderViewport()
  {
  #ifdef MX_IMGUI_ACTIVE
    static ImGuiWindowFlags window_flags = 0;
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 0;
    static bool no_nav = 0;
    static bool no_background = 1;
    static bool no_bring_to_front = 0;
    static bool no_autoresize = 0;
    static bool p_open = 1;
    static bool p_open_performance_monitor = 1;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; 
    if (no_autoresize)      window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

    static int current_frame = 0;
    static int first_iteration = 1;
    static ImTextureID my_tex_id;
    static float my_tex_w;
    static float my_tex_h;

    current_frame = Application::get().m_Window->m_Props.m_Frames;
    
    if (ImGui::Begin("View Port", &p_open, window_flags))
    {
      Window::WindowProps::ViewPort *app_viewport = &Application::get().m_Window->m_Props.m_Viewport;
      
      std::string fps_message = std::to_string(current_frame) + " FPS";
      ImGui::Text(fps_message.c_str());

      if (first_iteration)
      {
        my_tex_id = (void*)play_button.getID();
        my_tex_w = play_button.m_Stb.width;
        my_tex_h = play_button.m_Stb.height;
        first_iteration = 0;
      }

      ImGui::SameLine();
      if (ImGui::ImageButton(my_tex_id, ImVec2(16.0f, 16.0f), ImVec2(-1, -1), ImVec2(16.0f / my_tex_w, 16.0f / my_tex_h), 3, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
        current_scenegraph->is_paused = !current_scenegraph->is_paused;


      static int menubar_offset = 19;

      if (!first_run)
      {
        ImGui::SetWindowPos(ImVec2(0, menubar_offset));
        ImGui::SetWindowSize(ImVec2(
          app_viewport->m_Viewport_max_x,
          app_viewport->m_Viewport_max_y - menubar_offset
        ));
        first_run = 0;
      }

      // comments are values at start up with window resolution of 1200, 600
      auto window_size = ImGui::GetWindowSize(); // 853, 581
      auto window_pos = ImGui::GetWindowPos(); // 0, 19

      app_viewport->m_Viewport_min_x = window_pos.x; // 0
      app_viewport->m_Viewport_min_y = window_size.y + window_pos.y; // 19

      app_viewport->m_Viewport_max_x = window_size.x; // 853
      app_viewport->m_Viewport_max_y = window_size.y; // 581
    }
    ImGui::End();

    if (ImGui::Begin("Performance Monitor", &p_open_performance_monitor))
    {
      static float fps_avg;
      static int max_fps = 0;
      static std::vector<float> frames;

      frames.push_back(static_cast<float>(current_frame));

      if (current_frame > max_fps)
        max_fps = current_frame;

      for (float it : frames)
        fps_avg += it;

      fps_avg /= frames.size();

      std::string fps_avg_message = "avg " + std::to_string(fps_avg);

      ImGui::PlotLines("Frame Time", frames.data(), frames.size(), 0, fps_avg_message.c_str(), 0.0f, static_cast<int>(max_fps) * 1.5f, ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 37.0f)); // 37.0f so that no scroll bar will appear

      if (frames.size() > 20000)
        frames.clear();
    }
    ImGui::End();
    
  #endif
  }
}