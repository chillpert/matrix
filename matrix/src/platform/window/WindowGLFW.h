#ifndef WINDOWGLFW_H
#define WINDOWGLFW_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_GLFW_ACTIVE

namespace Matrix {

    class WindowGLFW : public Window {
    public:
        MATRIX_API WindowGLFW() {}
        MATRIX_API ~WindowGLFW() {}

        MATRIX_API void update() const override; 
        MATRIX_API void render() const override; 

        MATRIX_API bool createContext() override;
        MATRIX_API void resize() const override;
        MATRIX_API void close() const override; 

        MATRIX_API void controllerCallback() override {}

        MATRIX_API inline auto getWindow() { return m_Window; }
    private:
        GLFWwindow* m_Window;
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void error_callback(int error, const char* description);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif 

#endif // WINDOWGLFW_H
