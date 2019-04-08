#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/platform/window/Window_SDL2.h"
#include "matrix/src/platform/window/Window_GLFW.h"

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

namespace MX {

    void GUI_ImGui::initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        MX_IMGUI_INIT;
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void GUI_ImGui::update() {
        ImGui_ImplOpenGL3_NewFrame();
        MX_IMGUI_NEW_FRAME;
        ImGui::NewFrame();
    }

    void GUI_ImGui::render() {
        ImGui::Begin("ImGui Window");
        ImGui::Text("Hello there");
        ImGui::End();
        
        ImGui::Render();
        MX_IMGUI_API_RENDER;
    }

    void GUI_ImGui::clean() {
        MX_IMGUI_API_CLOSE;
        MX_IMGUI_CLEAN;
        ImGui::DestroyContext();
    }
}