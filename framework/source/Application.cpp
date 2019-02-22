#include "Application.h"
#include "Logger.h"

namespace Matrix {
    
    Application::Application() {
        INFO("Application created");
        m_Title = "Matrix Framework";
        m_Width = 1200;
        m_Height = 600;
        m_Running = true;
    }

    Application::~Application() {

    }

    Application &Application::get() {
        static Application instance;
        return instance;
    }

    void Application::initialize(void (*initialize_func)()) {
        if (!glfwInit()) {
            //FATAL("GLFW initialisation failed");
            m_Running = false;
        } else {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // glfwGetPrimaryMonitor() for full screen
            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
            if (!m_Window) {
                //FATAL("GLFW window initialisation failed");
                m_Running = false;
            } else {
                glfwMakeContextCurrent(m_Window);

                glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
                glfwSetCursorPosCallback(m_Window, mouse_callback);
                glfwSetScrollCallback(m_Window, scroll_callback);
                glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                glewExperimental = GL_TRUE; 
                GLenum glewError = glewInit();
    	        if (glewError != GLEW_OK) {
                    //FATAL("GLEW initialisation failed");
                    m_Running = false;
    	        } else {
                    INFO("Application successfully initialized");

                    glEnable(GL_DEPTH_TEST);
                    initialize_func();
                }
            }
        }
    }

    void Application::start(void (*initialize_func)(), void (*update_func)(), void (*render_func)()) {
        this->initialize(initialize_func);
        // rendering loop
        while(m_Running) {
            this->update(update_func);
            this->render(render_func);
        }
        this->clean();
    }

    void Application::update(void (*update_func)()) {
        processInput(m_Window);
        update_func();
    }

    void Application::render(void (*render_func)()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        render_func();  

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void Application::clean() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Application::setWidth(int width) {
        m_Width = width;
    }

    void Application::setHeight(int height) {
        m_Height = height;
    }

    void Application::setTitle(std::string title) {
        m_Title = title;
    }

    void Application::stop() {
        m_Running = false;
    }

    void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            Application::get().stop();
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

    }

}
