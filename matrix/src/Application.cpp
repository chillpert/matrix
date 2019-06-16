#include "matrix/src/Application.h"
#include <string>

namespace MX
{
  Application::Application()
  {
    MX_INFO_LOG("MX: Application: Constructor");

    m_Window =  std::make_unique<MX_WINDOW_TYPE>();
    m_LayerStack = std::make_unique<LayerStack>();

    #ifdef MX_PLATFORM_UNIX_X64
      #pragma GCC diagnostic ignored "-Wformat-security"
    #endif
  }

  Application::~Application()
  {
    delete m_API;
    m_API = nullptr;
    delete m_GUI;
    m_GUI = nullptr;

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
    m_Running = m_Window->initialize();
    MX_SUCCESS("MX: Application: Initialization: Window");
    
    // set up API
    m_Running = m_API->initialize();
    MX_SUCCESS("MX: Application: Initialization: API");
    
    initialize_func();
    MX_SUCCESS_LOG("MX: Application: Initialization: Func");

    // set up GUI
    m_GUI->initialize();
    MX_SUCCESS("MX: Application: Initialization: GUI");

    if (m_Running)
      MX_SUCCESS("MX: Application: Initialization");
    else
      MX_FATAL("MX: Application: Initialization");
  }

  void Application::update(void (*update_func)())
  {
    m_Window->update();

    m_Window->controllerCallback();

    m_GUI->update();

    m_API->update();
    
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
}
