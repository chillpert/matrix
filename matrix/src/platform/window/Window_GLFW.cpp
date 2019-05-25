#include "matrix/src/platform/window/Window_GLFW.h"
#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/event/MouseEvent.h"
#include "matrix/src/event/WindowEvent.h"
#include "matrix/src/controller/Controller.h"

#ifdef MX_GLFW_ACTIVE

namespace MX
{
  bool Window_GLFW::initialize()
  {
    if (!glfwInit())
    {
      MX_FATAL("GLFW initialization");
      return false;
    }
    else
    {
      const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      glfwWindowHint(GLFW_RED_BITS, mode->redBits);
      glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
      glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
      glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      
      m_Window = glfwCreateWindow(m_Props.m_Width, m_Props.m_Height, m_Props.m_Title.c_str(), NULL, NULL);

      if (!m_Window)
      {
        MX_FATAL("GLFW window initialization");
        return false;
      }
      else
      {
        glfwMakeContextCurrent(m_Window);

        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
        
        });
        
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        { 
          xoffset = xoffset + 0.5 - (xoffset < 0);
          yoffset = yoffset + 0.5 - (yoffset < 0);
          int x = int(xoffset);
          int y = int(yoffset);
          MouseScrolled event(x, y);
          event.handle();
          LOGEVENT;
        });
      
        glfwSetErrorCallback([](int, const char* description)
        {
          std::string message = description;
          MX_FATAL(message);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
          switch (action)
          {
            case GLFW_PRESS:
            {
              KeyboardButtonPressed event(key);
              event.handle();
              LOGEVENT;
              break;
            }
            case GLFW_RELEASE:
            {
              KeyboardButtonReleased event(key);
              event.handle();
              LOGEVENT;
              break;
            }
            case GLFW_REPEAT:
            {
              KeyboardButtonPressed event(key);
              event.handle();
              LOGEVENT;
              break;
            }    
          }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
          xpos = xpos + 0.5 - (xpos < 0);
          ypos = ypos + 0.5 - (ypos < 0);
          int x = int(xpos);
          int y = int(ypos);
          MouseMoved event(x, y);
          event.handle();
          LOGEVENT;
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
          switch(action)
          {
            case GLFW_PRESS:
            {
              MouseButtonPressed event(button);
              event.handle();
              LOGEVENT;
              break;
            }
            case GLFW_RELEASE:
            {
              MouseButtonReleased event(button);
              event.handle();
              LOGEVENT;
              break;
            }
          }
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
          WindowClosed event;
          event.handle();
          LOGEVENT;
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
          WindowResized event(width, height);
          event.handle();
          LOGEVENT;
        });

        glfwSwapInterval(1);
        MX_SUCCESS("MX: Window: GLFW: Context");
        return true;
      }
    }

    MX_FATAL("MX: Window: GLFW: Context");
    return false;
  }

  void Window_GLFW::update()
  { 
    m_Props.m_Time = (float) glfwGetTime();
    updateTime();

    // update mouse visibility
    if (Controller::get().m_MouseHidden)
      glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
      glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  void Window_GLFW::render() const
  {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }

  void Window_GLFW::close() const
  {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }

  void Window_GLFW::resizeWindow(int width, int height)
  {
    glfwSetWindowSize(m_Window, width, height);
  }

  void Window_GLFW::setTitle()
  {
    glfwSetWindowTitle(m_Window, m_Props.m_Title.c_str());
  }
}

#endif