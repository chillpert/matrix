#ifndef APPLICATION_H
#define APPLICATION_H

#define MX_WORLD Application::get().m_World
#define MX_SCENEGRAPH Application::get().m_World.m_ActiveScene->m_Sg
#define MX_CAMERA Application::get().m_World.m_ActiveScene->m_Cam
#define MX_SCENE Application::get().m_World.m_ActiveScene
#define MX_ROOT Application::get().m_World.m_ActiveScene->m_Sg.m_Root

#include <stdafx.h>
#include <Window.h>
#include <Window_SDL2.h>
#include <API.h>
#include <API_OpenGL.h>
#include <GUI.h>
#include <GUI_ImGui.h>
#include <LayerStack.h>
#include <World.h>

namespace MX
{
  class Application
  {     
  public:
    MX_API static Application &get();
  
    MX_API void initialize(void (*initialize_func)());
    MX_API void render(void (*render_func)());
    MX_API void update(void (*update_func)());
    MX_API void clean();

    std::unique_ptr<API> m_API;
    std::unique_ptr<GUI> m_GUI;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<LayerStack> m_LayerStack;

    World m_World;

    bool m_Running;
  
  private:
    MX_API Application();
    MX_API ~Application();

    MX_API Application(const Application&) = delete;
    MX_API Application &operator=(const Application&) = delete;
  };  
}

#endif // APPLICATION_H