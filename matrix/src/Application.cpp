#include "matrix/src/Application.h"
#include "matrix/src/Logger.h"

namespace Matrix {
    
    Application::Application() {
        INFO("Creating Application");
    }

    Application::~Application() {

    }

    Application &Application::get() {
        static Application instance;
        return instance;
    }

    void Application::initialize(void (*initialize_func)()) {
        // setting window attributes
        m_Window->setTitle("Matrix Framework");
        m_Window->setWidth(1200);
        m_Window->setHeight(600);
        m_Running = m_Window->createContext();
        
        // setting API
        m_Running = m_API->createContext();

        m_Running = true;
        SUCCESS("Application initialized");
    }

    void Application::update(void (*update_func)()) {
        m_Window->update();

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
