#ifndef Window_GLFW_H
#define Window_GLFW_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_GLFW_ACTIVE

namespace MX {

    class Window_GLFW : public Window {
    public:
        MX_API static Window_GLFW& get() {
            static Window_GLFW instance;
            return instance;
        }

        MX_API ~Window_GLFW() {}

        MX_API void update() const override; 
        MX_API void render() const override; 
        MX_API bool createContext() override;
        
        MX_API void close() const override; 
        MX_API void controllerCallback() override {}

        MX_API void setTitle() override;
        MX_API void resize() override;        

        MX_API inline auto getWindow() { return m_Window; }
    private:
        MX_API Window_GLFW() {}

        GLFWwindow* m_Window;
    };
}

#endif 

#endif // Window_GLFW_H
