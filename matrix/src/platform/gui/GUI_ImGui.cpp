#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/platform/window/Window_SDL2.h"
#include "matrix/src/platform/window/Window_GLFW.h"

#ifdef MX_IMGUI_ACTIVE

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

namespace MX
{
  void GUI_ImGui::initialize()
  {
  #ifdef MX_IMGUI_ACTIVE
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
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
    colors[ImGuiCol_WindowBg]               = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.33f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.17f, 0.17f, 0.17f, 0.45f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.18f, 0.18f, 0.18f, 0.33f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.68f, 0.68f, 0.68f, 0.31f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.11f, 0.37f, 0.00f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.15f, 0.51f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.15f, 0.52f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.01f, 0.83f, 0.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.04f, 0.52f, 0.00f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.13f, 0.72f, 0.01f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.01f, 0.67f, 0.07f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.49f, 0.06f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.05f, 0.61f, 0.00f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.00f, 0.77f, 0.07f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.00f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.01f, 0.49f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.51f, 0.03f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.12f, 0.69f, 0.00f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.00f, 0.75f, 0.12f, 0.95f);
    
    MX_IMGUI_INIT

    ImGui_ImplOpenGL3_Init("#version 330");

    check_folder_for_objects();
  #endif
  }

  void GUI_ImGui::update()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGui_ImplOpenGL3_NewFrame();
    MX_IMGUI_NEW_FRAME
    ImGui::NewFrame();
  #endif
  }

  void GUI_ImGui::render()
  {
  #ifdef MX_IMGUI_ACTIVE

    if (event_window_enabled)
      renderEventWindow();
    else if (input_window_enabled)
      renderInputWindow();
    else if (selection_window_enabled)
      renderSelectionWindow();
    else
    {
      if (menubar_enabled)
        renderMenuBar();
      if (editor_window_enabled)
        renderEditorWindow();
      if (hierarchy_window_enabled)
        renderHierarchyWindow();
    }

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
    for (std::vector<char*>::iterator iter = all_available_models.begin() + 1; iter != all_available_models.end(); ++iter)
      delete *iter;

  #endif
  }
}