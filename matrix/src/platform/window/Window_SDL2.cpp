#include "matrix/src/platform/window/Window_SDL2.h"
#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/event/MouseEvent.h"
#include "matrix/src/event/WindowEvent.h"

#ifdef MX_SDL2_ACTIVE

namespace MX
{
  static std::string SDL_ErrorMessage;

  bool Window_SDL2::initialize()
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      SDL_ErrorMessage = SDL_GetError();
      MX_FATAL("SDL2 context: " + SDL_ErrorMessage);
      return 0;
    }
    else
    {
      MX_SUCCESS("SDL2 context");
      
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

      m_Window = SDL_CreateWindow(m_Props.m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                  m_Props.m_Width, m_Props.m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
      if (m_Window == NULL)
      {
        SDL_ErrorMessage = SDL_GetError();
        MX_FATAL("SDL2 window: " + SDL_ErrorMessage);

        return 0;
      }
      else
      {
        MX_SUCCESS("SDL2 window");

        m_Context = SDL_GL_CreateContext(m_Window);
        if (m_Context == NULL)
        {
          SDL_ErrorMessage = SDL_GetError();
          MX_FATAL("SDL2 GL context: " + SDL_ErrorMessage);
        }
        else
        {
          MX_SUCCESS("SDL2 GL context");
          return 1;
        }
      }
    }
    return 0;
  }

  void Window_SDL2::update() 
  {
    m_Props.m_Time = SDL_GetTicks() / 1000.0f;
  }

  void Window_SDL2::render() const
  {
    SDL_SetWindowTitle(m_Window, m_Props.m_Title.c_str());
    SDL_GL_SwapWindow(m_Window);
  }

  void Window_SDL2::close() const
  {
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
  }

  void Window_SDL2::controllerCallback()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_KEYDOWN)
      {
        KeyboardButtonPressed event(event.key.keysym.sym);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_KEYUP)
      {
        KeyboardButtonReleased event(event.key.keysym.sym);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_MOUSEMOTION)
      {
        int x, y;
        SDL_GetMouseState(&x, &y);
        MouseMoved event(x, y);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN)
      { 
        MouseButtonPressed event(event.button.button);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_MOUSEBUTTONUP)
      {
        MouseButtonReleased event(event.button.button);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_MOUSEWHEEL)
      {
        MouseScrolled event(event.wheel.x, event.wheel.y);
        event.handle();
        LOGEVENT;
      }
      if (event.type == SDL_WINDOWEVENT)
      {
        switch (event.window.event)
        {
          case SDL_WINDOWEVENT_CLOSE:
          {
            WindowClosed event;
            event.handle();
            LOGEVENT;
            break;
          }
          case SDL_WINDOWEVENT_RESIZED:
          {
            WindowResized event(int(event.window.data1), int(event.window.data1));
            event.handle();
            LOGEVENT;
            break;
          }
        }
      }
    }   
  }

  void Window_SDL2::setTitle()
  {
    SDL_SetWindowTitle(m_Window, m_Props.m_Title.c_str());
  }

  void Window_SDL2::resize()
  {
    SDL_SetWindowSize(m_Window, m_Props.m_Width, m_Props.m_Height);
  }
}

#endif