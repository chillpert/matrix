#include "matrix/src/Application.h"
#include <string>

namespace MX
{
  Application::Application()
  {
    MX_INFO("MX: Application: Created");
  }

  Application::~Application()
  {
    MX_INFO("MX: Application: Destroyed");
  }

  Application &Application::get()
  {
    static Application instance;
    return instance;
  }

  void Application::initialize(void (*initialize_func)())
  {
    // set up window 
    m_Running = m_Window->createContext();
    
    // set up API
    m_Running = m_API->createContext();
    
    // set up GUI
    m_GUI->initialize();

    initialize_func();

    if (m_Running)
    {
        MX_SUCCESS("MX: Application: Initialization");
    }
    else
    {
        MX_FATAL("MX: Application: Initialization");
    }
  }

  void Application::update(void (*update_func)())
  {
    m_Window->update();

    m_Window->controllerCallback();

    m_GUI->update();
     
    update_func();
  }

  void Application::render(void (*render_func)())
  {
    m_API->clear();

    m_API->render();

    render_func();

    m_GUI->render();   

    m_Window->render();
  }

  void Application::clean()
  {
    m_GUI->clean();

    m_Window->close();

    MX_SUCCESS("MX: Application: Closed");
  }

  void Application::stop()
  {
    m_Running = false;
  }
}
