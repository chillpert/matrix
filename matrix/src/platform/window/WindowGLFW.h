#ifndef WINDOWGLFW_H
#define WINDOWGLFW_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_GLFW_ACTIVE

namespace MX {

    class WindowGLFW : public Window {
    public:
        MX_API WindowGLFW() {}
        MX_API ~WindowGLFW() {}

        MX_API void update() const override; 
        MX_API void render() const override; 
        MX_API bool createContext() override;
        
        MX_API void close() const override; 
        MX_API void controllerCallback() override {}

        MX_API void setTitle() override;
        MX_API void resize() override;        

        MX_API inline auto getWindow() { return m_Window; }
    private:
        GLFWwindow* m_Window;
    };
}

#endif 

#endif // WINDOWGLFW_H
