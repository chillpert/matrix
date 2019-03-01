#include "matrix/src/Application.h"

namespace MX {
    
    Application::Application() {
        MX_INFO("Creating Application");
    }

    Application::~Application() {

    }

    Application &Application::get() {
        static Application instance;
        return instance;
    }

    void Application::initialize(void (*initialize_func)()) {
        // setting window 
        m_Running = m_Window->createContext();
        
        // setting API
        m_Running = m_API->createContext();

        m_Running ? MX_SUCCESS("Application initialization") : MX_FATAL("Application initialization");
    }

    void Application::update(void (*update_func)()) {
        m_Window->update();
        m_Window->controllerCallback();
        update_func();
    }

    void Application::render(void (*render_func)()) {
        m_API->render();
        
        render_func();  

        m_Window->render();
    }

    void Application::clean() {
        m_Window->close();
    }

    void Application::stop() {
        m_Running = false;
    }
}
