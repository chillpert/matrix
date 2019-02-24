#include "matrix/src/platform/window/WindowGLFW.h"
#include "Matrix/src/Logger.h"

#ifdef GLFW_ACTIVE

    namespace Matrix {
        
        bool WindowGLFW::createContext() {
            if (!glfwInit()) {
                FATAL("GLFW initialisation");
                return false;
            } else {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                // glfwGetPrimaryMonitor() for full screen
                m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
                if (!m_Window) {
                    FATAL("GLFW window initialisation");
                    return false;
                } else {
                    glfwMakeContextCurrent(m_Window);
                    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
                    glfwSetCursorPosCallback(m_Window, mouse_callback);
                    glfwSetScrollCallback(m_Window, scroll_callback);
                    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                
                    SUCCESS("GLFW context");
                    return true;
                }
            }
            FATAL("GLFW context");
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
    
        void processInput(GLFWwindow *window) {
            //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {}
               // Application::get().stop();
        }
    
        void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            //glViewport(0, 0, width, height);
        }
    
        void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        
        }
    
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        
        }
    }

#endif