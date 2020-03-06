#ifndef APPLICATION_H
#define APPLICATION_H

#define MX_APP          Application::get()

#define MX_WINDOW       MX_APP.m_Window
#define MX_GAPI         MX_APP.m_API
#define MX_GUI          MX_APP.m_active_gui

#define MX_WORLD        MX_APP.m_World
#define MX_SCENEGRAPH   MX_APP.m_World.m_ActiveScene->m_Sg
#define MX_CAMERA       MX_APP.m_World.m_ActiveScene->m_Cam
#define MX_SCENE        MX_APP.m_World.m_ActiveScene
#define MX_SCENES       MX_APP.m_World.m_ExistingScenes
#define MX_ROOT         MX_APP.m_World.m_ActiveScene->m_Sg.m_Root

#ifdef MX_DEBUG
  #define MX_ASSERT(x,y)  MX::Debug::assert_condition(x, y)
  #define ASSERT(x,y)     Debug::assert_condition(x,y)
#elif
  #define MX_ASSERT(x,y)
  #define ASSERT(x,y)
#endif

// always assert no matter release or debug
#define MX_AASSERT(x,y)  MX::Debug::assert_condition(x, y)
#define AASERT(x,y)      Debug::assert_condition(x,y)

#include "stdafx.h"
#include "Window.h"
#include "Window_SDL2.h"
#include "API.h"
#include "API_OpenGL.h"
#include "GUI.h"
#include "GUI_ImGui.h"
#include "GUI_Editor.h"
#include "LayerStack.h"
#include "World.h"

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
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<GUI> m_active_gui;

    LayerStack m_LayerStack;
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