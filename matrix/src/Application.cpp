#include <Application.h>

namespace MX
{
  Application::Application()
  {
    MX_INFO_LOG("MX: Application: Constructor");

    m_API = std::make_unique<MX_API_TYPE>();
    m_GUI = std::make_unique<MX_GUI_TYPE>();

    m_Window =  std::make_unique<Window_SDL2>();

    m_World = World::get_default_world();

    #ifdef MX_PLATFORM_UNIX_X64
      #pragma GCC diagnostic ignored "-Wformat-security"
    #endif
  }

  Application::~Application()
  {
    MX_INFO_LOG("MX: Application: Destroyed");
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
    MX_SUCCESS_LOG("MX: Application: Initialization: Window");
    
    // set up API
    m_Running = m_API->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: API");
    
    initialize_func();
    MX_SUCCESS_LOG("MX: Application: Initialization: Func");
  
    // set up GUI
    m_GUI->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: GUI");

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

    MX_SUCCESS_LOG("MX: Application: Closed");
  }
}
