#ifndef APPLICATION_H
#define APPLICATION_H

#include "stdafx.h"
#include "WindowEvent.h"
#include "Window.h"
#include "Window_SDL2.h"
#include "API.h"
#include "API_OpenGL.h"
#include "GUI.h"
#include "GUI_ImGui.h"
#include "GUI_Editor.h"
#include "LayerStack.h"
#include "World.h"

#define MX_APP           Application::get()
#define MX_IS_RUNNING(x) MX_APP.setRunning(x)

#define MX_WINDOW        MX_APP.m_Window
#define MX_GAPI          MX_APP.m_API
#define MX_GUI           MX_APP.m_active_gui

#define MX_WORLD         MX_APP.getWorld()
#define MX_SCENE         MX_WORLD.m_ActiveScene
#define MX_SCENES        MX_WORLD.m_ExistingScenes
#define MX_SCENEGRAPH    MX_SCENE->m_Sg
#define MX_CAMERA        MX_SCENE->m_Cam
#define MX_ROOT          MX_SCENE->m_Sg.m_Root

namespace MX
{
  class Application
  {
  public:
    MX_API static Application &get();

    MX_API void run();

    MX_API void OnEvent(Event& event);
    MX_API void PushLayer(Layer* layer);
    MX_API void PushOverlay(Layer* overlay);

    MX_API World& getWorld() { return m_World; }
    MX_API void setRunning(bool flag);

  private:
    MX_API Application();
    MX_API ~Application();

    MX_API void initialize();
    MX_API void render();
    MX_API void update();
    MX_API void clean();

    MX_API Application(const Application&) = delete;
    MX_API Application &operator=(const Application&) = delete;

    MX_API bool OnWindowClose(WindowClosed& event);

  private:
    World m_World;
    LayerStack m_LayerStack;
    bool m_Running = true;
    
  public:
    std::unique_ptr<API> m_API;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<GUI> m_active_gui;

  };
}

#endif // APPLICATION_H