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

  void GUI_ImGui::render()
  {
    #ifdef MX_IMGUI_ACTIVE
      ImGui::Begin("ImGui Window");
      ImGui::Text("Hello there");
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