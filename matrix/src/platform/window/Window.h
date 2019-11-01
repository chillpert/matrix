#ifndef WINDOW_H
#define WINDOW_H

#ifdef MX_DEBUG
  #define LOGEVENT event.printEventType()
#else
  #define LOGEVENT
#endif

#include "stdafx.h"

namespace MX
{
  class Window
  {
  public:
    MX_API Window() = default;
    MX_API virtual ~Window() {};

    MX_API Window(const Window&) = default;
    MX_API Window &operator=(const Window&) = default;

    MX_API virtual void update() = 0;
    MX_API virtual void render() = 0;
    MX_API virtual bool initialize() = 0;

    MX_API virtual void close() = 0;
    MX_API virtual void controllerCallback() const = 0;

    // this function is needed to get to derived class members
    MX_API virtual Window *getWindow() = 0;

    MX_API virtual void setTitle(const std::string &title) = 0;
    MX_API virtual void resize(int width, int height) = 0;

    struct WindowProps
    {
      void update_time();

      int m_Width = initial_window_width;
      int m_Height = initial_window_height;

      bool m_FullScreen = 0;

      // timing
      float m_DeltaTime = 0.0f;
      float m_PreviousTime = 0.0f;
      float m_Time = 0.0;
      int m_Frames = 0;
      
      std::string m_Title = "Matrix-Framework";

      struct ViewPort
      {
        int m_Viewport_min_x = 0;
        int m_Viewport_min_y = 0;

        int m_Viewport_max_x = initial_window_width;
        int m_Viewport_max_y = initial_window_height;
      };

      ViewPort m_Viewport;
    };
 
    WindowProps m_Props;
  };
}

#endif // WINDOW_H