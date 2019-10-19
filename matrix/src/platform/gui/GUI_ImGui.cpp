#include "GUI_ImGui.h"
#include "Window.h"
#include "Window_SDL2.h"
#include "Application.h"

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
  void GUI_ImGui::initialize()
  {
#ifdef MX_IMGUI_ACTIVE
    MX_IMGUI_INIT
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
#endif
  }

  void GUI_ImGui::update()
  {
    ImGui_ImplOpenGL3_NewFrame();
    MX_IMGUI_NEW_FRAME
    ImGui::NewFrame();
  }

  void GUI_ImGui::render()
  {
#ifdef MX_IMGUI_ACTIVE
    ImGui::Render();
    MX_IMGUI_API_RENDER
#endif
  }

  void GUI_ImGui::clear()
  {
#ifdef MX_IMGUI_ACTIVE
  
#endif
  }

  void GUI_ImGui::clean()
  {
#ifdef MX_IMGUI_ACTIVE
    MX_IMGUI_API_CLOSE
    MX_IMGUI_CLEAN
    ImGui::DestroyContext();
#endif
  }
}