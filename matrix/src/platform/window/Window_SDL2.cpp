#include "Window_SDL2.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "Controller.h"
#include "World.h"
#include "Application.h"

#ifdef MX_IMGUI_ACTIVE
  #include <imgui.h>
  #include <imgui_impl_sdl.h>
#endif

namespace MX
{
  static std::string SDL_ErrorMessage;

  bool Window_SDL2::initialize()
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      SDL_ErrorMessage = SDL_GetError();
      MX_FATAL("MX: Window: SDL2: context: " + SDL_ErrorMessage);
      return 0;
    }
    else
    {
      MX_SUCCESS("MX: Window: SDL2: context");

      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

      m_Window = SDL_CreateWindow(m_Props.m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                  m_Props.m_Width, m_Props.m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

      if (m_Window == NULL)
      {
        SDL_ErrorMessage = SDL_GetError();
        MX_FATAL("MX: Window: SDL2: " + SDL_ErrorMessage);

        return 0;
      }
      else
      {
        MX_SUCCESS("MX: Window: SDL2");

        m_Context = SDL_GL_CreateContext(m_Window);

        if (m_Context == NULL)
        {
          SDL_ErrorMessage = SDL_GetError();
          MX_FATAL("MX: Window: SDL2: GL context: " + SDL_ErrorMessage);
        }
        else
        {
          MX_SUCCESS("MX: Window: SDL2: GL context");
          return 1;
        }
      }
    }
    return 0;
  }

  void Window_SDL2::update() 
  {
    m_Props.m_Time = (float) (SDL_GetTicks()) / 1000.0f;
    m_Props.update_time();

    // update mouse visibility
    if (Controller::get().m_MouseHidden)
      SDL_SetRelativeMouseMode(SDL_TRUE);
    else
      SDL_SetRelativeMouseMode(SDL_FALSE);

    controllerCallback();
  }

  void Window_SDL2::render()
  {
    SDL_SetWindowTitle(m_Window, m_Props.m_Title.c_str());
    SDL_GL_SwapWindow(m_Window);
  }

  void Window_SDL2::close()
  {
    SDL_GL_DeleteContext(m_Context);

    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_Quit();
  }

  void Window_SDL2::controllerCallback() const
  {
    SDL_Event SDLevent;
    while (SDL_PollEvent(&SDLevent) != 0)
    {
    #ifdef MX_IMGUI_ACTIVE
      ImGui_ImplSDL2_ProcessEvent(&SDLevent);
    #endif
      if (SDLevent.type == SDL_KEYDOWN)
      {
        KeyboardButtonPressed event(SDLevent.key.keysym.sym);
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_KEYUP)
      {
        KeyboardButtonReleased event(SDLevent.key.keysym.sym);
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_MOUSEMOTION)
      {
        int x, y;
        SDL_GetMouseState(&x, &y);
        MouseMoved event(static_cast<float>(x), static_cast<float>(y));
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_MOUSEBUTTONDOWN)
      { 
        MouseButtonPressed event(SDLevent.button.button);
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_MOUSEBUTTONUP)
      {
        MouseButtonReleased event(SDLevent.button.button);
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_MOUSEWHEEL)
      {
        MouseScrolled event(static_cast<float>(SDLevent.wheel.x), static_cast<float>(SDLevent.wheel.y));
        event.handle();
        MX_LOG_EVENT(event)
      }
      if (SDLevent.type == SDL_WINDOWEVENT)
      {
        switch (SDLevent.window.event)
        {
          case SDL_WINDOWEVENT_CLOSE:
          {
            WindowClosed event;
            event.handle();
            MX_LOG_EVENT(event)
            break;
          }
          case SDL_WINDOWEVENT_RESIZED:
          {
            WindowResized event(SDLevent.window.data1, SDLevent.window.data2);
            event.handle();
            MX_LOG_EVENT(event)
            break;
          }
        }
      }
    }
  }

  void Window_SDL2::resize(int width, int height)
  {
    if (MX_SCENE != nullptr)
      MX_CAMERA.setScreenDimensions(width, height);
    SDL_SetWindowSize(m_Window, width, height);

    m_Props.m_Width = width;
    m_Props.m_Height = height;
  }

  void Window_SDL2::setTitle(const std::string &title)
  {
    SDL_SetWindowTitle(m_Window, title.c_str());

    m_Props.m_Title = title;
  }
}