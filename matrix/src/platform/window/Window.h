#ifndef WINDOW_H
#define WINDOW_H

#ifdef MX_GLFW_ACTIVE
  #define MX_WINDOW_TYPE &MX::Window_GLFW::get();
#elif MX_SDL2_ACTIVE
  #define MX_WINDOW_TYPE &MX::Window_SDL2::get();
#else 
  #error "Matrix Framework only supports GLFW and SDL2"
#endif

#ifdef MX_DEBUG
  #define LOGEVENT event.printEventType();
#else
  #define LOGEVENT
#endif

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  class Window
  {
  public:
    MX_API Window() {}
    MX_API virtual ~Window() {}
    
    MX_API virtual void update() {}
    MX_API virtual void render() const {}
    MX_API virtual bool initialize() { return false; }

    MX_API virtual void close() const {}
    MX_API virtual void controllerCallback() {}

    MX_API void setTitle(std::string title);
    MX_API void resize(int width, int height);

    struct WindowProps
    {
      WindowProps() 
        : m_Width(1200), m_Height(600), m_Time(0.0), m_Title("Matrix Framework") {}
      ~WindowProps() {}

      int m_Width;
      int m_Height;
      double m_Time;
      std::string m_Title;
    };
 
    WindowProps m_Props; 
  protected:
    MX_API virtual void setTitle() {}
    MX_API virtual void resize() {}
  };
}

#endif // WINDOW_H