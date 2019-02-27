#ifndef WINDOWGLFW_H
#define WINDOWGLFW_H

#include "matrix/src/platform/window/Window.h"

namespace Matrix {

    class MATRIX_API WindowGLFW : public Window {
    public:
        WindowGLFW() {}
        ~WindowGLFW() {}

        void update() const override; 
        void render() const override; 

        bool createContext() override;
        void resize() const override;
        void close() const override; 

        inline auto getWindow() { return m_Window; }
    private:
        GLFWwindow* m_Window;
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void error_callback(int error, const char* description);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif // WINDOWGLFW_H
