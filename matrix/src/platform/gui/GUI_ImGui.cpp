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
    #define MX_IMGUI_API_RENDER
    #define MX_IMGUI_API_CLOSE
  #endif

  #include <imgui_impl_opengl3.h>
#endif

namespace MX
{
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
    colors[ImGuiCol_ChildBg]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.41f, 0.41f, 0.41f, 0.31f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.80f, 0.35f, 0.02f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    all_scenes = &MX_WORLD.m_ExistingScenes;
    current_root = MX_WORLD.m_ActiveScene->m_Sg.m_Root;
    current_scenegraph = &MX_WORLD.m_ActiveScene->m_Sg;
    current_scene = MX_WORLD.m_ActiveScene;
    current_node = current_root;

    MX_IMGUI_INIT
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // reserve memory for incoming mx-logger messages
    logger_messages_for_gui.reserve(5000);
  #endif
  }

  void GUI_ImGui::update()
  {
  #ifdef MX_IMGUI_ACTIVE
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

    if (demo_window_enabled)            ImGui::ShowDemoWindow();

    if (menubar_enabled)                renderMenuBar();
    if (spawn_window_enabled)           renderSpawnMenu();
    if (scenegraph_enabled)             renderSceneGraph();
    if (outline_enabled)                renderOutline();
    if (scenes_window_enabled)          renderScenesMenu();
    if (assets_window_enabled)          renderAssestsMenu();
    if (logger_window_enabled)          renderLoggerWindow();
    if (transform_window_enabled)       renderTransformMenu();
    if (performance_monitor_enabled)    renderPerformanceMonitor();
    if (file_inspector_enabled)         renderFileInspectorWindow();

    ImGui::Render();
    MX_IMGUI_API_RENDER

    cool_down = 0;
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
}