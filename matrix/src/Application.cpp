#include "Application.h"

namespace MX
{
  Application::Application()
  {
    MX_INFO_LOG("MX: Application: Constructor");

    m_API = std::make_unique<MX_API_TYPE>();
    m_active_gui = std::make_unique<GUI_Editor>();

    m_Window =  std::make_unique<Window_SDL2>();
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
    m_active_gui->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: GUI");

    if (m_Running)
      MX_SUCCESS("MX: Application: Initialization");
    else
      MX_FATAL("MX: Application: Initialization");
  }

  void Application::update(void (*update_func)())
  {
    m_Window->update();

    m_API->update();

    m_active_gui->update();

    update_func();
  }

  void Application::render(void (*render_func)())
  {
    render_func();

    m_API->render();

    m_active_gui->render();
    
    m_Window->render();
  }

  void Application::clean()
  {
    m_active_gui->clean();

    m_Window->close();

    MX_SUCCESS_LOG("MX: Application: Closed");
  }
}
