#include "matrix/src/platform/window/WindowGLFW.h"
#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/event/MouseEvent.h"

#ifdef MX_DEBUG
    #define LOGEVENT event.printEventType();
#else
    #define LOGEVENT
#endif

namespace Matrix {
    bool WindowGLFW::createContext() {
        if (!glfwInit()) {
            MX_FATAL("GLFW initialization");
            return false;
        } else {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
            m_Window = glfwCreateWindow(m_Props.m_Width, m_Props.m_Height, m_Props.m_Title.c_str(), NULL, NULL);
            if (!m_Window) {
                MX_FATAL("GLFW window initialization");
                return false;
            } else {
                glfwMakeContextCurrent(m_Window);
                glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
                glfwSetCursorPosCallback(m_Window, mouse_callback);
                glfwSetScrollCallback(m_Window, scroll_callback);
                glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetKeyCallback(m_Window, key_callback);
            
                MX_SUCCESS("GLFW context");
                return true;
            }
        }
        MX_FATAL("GLFW context");
        return false;
    }

    void WindowGLFW::update() const {
        
    }

    void WindowGLFW::render() const {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void WindowGLFW::resize() const {
        
    }

    void WindowGLFW::close() const {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        
    }

    void error_callback(int error, const char* description) {
        MX_FATAL(description);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (action) {
            case GLFW_PRESS: {
                KeyboardButtonPressed event(key);
                event.handle();
                LOGEVENT;
                break;
            }
            case GLFW_RELEASE: {
                KeyboardButtonReleased event(key);
                event.handle();
                LOGEVENT;
                break;
            }
            case GLFW_REPEAT: {
                
                break;
            }    
        }
    }        
}