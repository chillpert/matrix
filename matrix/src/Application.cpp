#include "Application.h"
#include "WindowEvent.h"

#include "Window_Layer.h"
#include "API_Layer.h"
#include "Editor_Layer.h"
#include "World_Layer.h"

namespace MX
{
  Application::Application()
  {
    MX_INFO_LOG("MX: Application: Constructor");
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

  void Application::run()
  {
    //PushLayer(new MX::Window_Layer("Window"));
    m_API = std::make_unique<MX_API_TYPE>();
    m_active_gui = std::make_unique<GUI_Editor>();
    m_Window = std::make_unique<Window_SDL2>();

    m_Running = m_Window->initialize();
    m_Running = m_API->initialize();
    m_active_gui->initialize();

    PushLayer(new World_Layer("World"));

    while (m_Running)
    {
      for (Layer* layer : m_LayerStack)
        layer->onUpdate();

      update();

      for (Layer* layer : m_LayerStack)
        layer->onRender();
      
      render();
    }

    for (Layer* layer : m_LayerStack)
      layer->onDetach();

    clean();
  }

  void Application::initialize()
  {
    m_API = std::make_unique<MX_API_TYPE>();
    m_active_gui = std::make_unique<GUI_Editor>();
    m_Window =  std::make_unique<Window_SDL2>(); 

    // set up window
    m_Running = m_Window->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: Window");

    // set up API
    m_Running = m_API->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: API");

    m_World.initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: World");

    // set up GUI
    m_active_gui->initialize();
    MX_SUCCESS_LOG("MX: Application: Initialization: GUI");

    if (m_Running)
      MX_SUCCESS("MX: Application: Initialization");
    else
      MX_FATAL("MX: Application: Initialization");
  }

  void Application::update()
  {
    m_Window->update();

    m_API->update();

    m_active_gui->update();

    //m_World.update();
  }

  void Application::render()
  {
    //m_World.render();

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

  void Application::setRunning(bool flag)
  {
    m_Running = flag;
  }

  void Application::OnEvent(Event& event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowClosed>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
      (*--it)->onEvent(event);
      if (event.isHandled())
        break;
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.pushLayer(layer);
		layer->onAttach();
  }

  void Application::PushOverlay(Layer* overlay)
  {
    m_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
  }

  bool Application::OnWindowClose(WindowClosed& event)
  {
    m_Running = false;
    return true;
  }
}
