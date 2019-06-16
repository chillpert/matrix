#ifndef APPLICATION_H
#define APPLICATION_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/window/Window.h"
#include "matrix/src/platform/window/Window_GLFW.h"
#include "matrix/src/platform/window/Window_SDL2.h"
#include "matrix/src/platform/api/API.h"
#include "matrix/src/platform/api/API_OpenGL.h"
#include "matrix/src/platform/gui/GUI.h"
#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/layers/LayerStack.h"

namespace MX
{
  class Application
  {     
  public:
    MX_API static Application &get();
  
    MX_API void initialize(void (*initialize_func)());
    MX_API void render(void (*render_func)());
    MX_API void update(void (*update_func)());
    MX_API void stop();
    MX_API void clean();

    std::unique_ptr<API> m_API;
    std::unique_ptr<GUI> m_GUI;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<LayerStack> m_LayerStack;

    bool m_Running;
  
  private:
    MX_API Application();
    MX_API ~Application();

    MX_API Application(const Application&) = delete;
    MX_API Application &operator=(const Application&) = delete;
  };  
}

#endif // APPLICATION_H