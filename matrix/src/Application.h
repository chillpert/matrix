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
  class MX_API Application
  {     
  public:
    virtual ~Application();

    static Application &get();
  
    void initialize(void (*initialize_func)());
    void render(void (*render_func)());
    void update(void (*update_func)());
    void stop();
    void clean();

    inline bool isRunning() { return m_Running; }
    inline Window* getWindow() { return m_Window; }
    inline LayerStack* getLayerStack() { return m_LayerStack; }
  private:
    Application();
  protected:   
    API* m_API = MX_API_TYPE;
    GUI* m_GUI = MX_GUI_TYPE;
    Window* m_Window = MX_WINDOW_TYPE;
    LayerStack* m_LayerStack = new LayerStack;
    bool m_Running;
  };  
}

#endif // APPLICATION_H