#ifndef WINDOW_H
#define WINDOW_H

#ifdef MX_GLFW_ACTIVE
    #define WINDOW_TYPE new Matrix::WindowGLFW();
#elif MX_SDL2_ACTIVE
    #define WINDOW_TYPE new Matrix::WindowSDL2();
#else 
    #error "Matrix Framework only supports GLFW and SDL2"
#endif

#ifdef MX_DEBUG
    #define LOGEVENT event.printEventType();
#else
    #define LOGEVENT
#endif

#include "matrix/src/pch/stdafx.h"

namespace Matrix {

    class Window {
    public:
        MATRIX_API Window() {}
        MATRIX_API virtual ~Window() {}
        
        MATRIX_API virtual void update() const {};
        MATRIX_API virtual void render() const {};

        MATRIX_API virtual bool createContext() { return false; }
        MATRIX_API virtual void resize() const {}
        MATRIX_API virtual void close() const {}

        MATRIX_API virtual void controllerCallback() {}
        
        struct WindowProps {
            WindowProps() 
                : m_Width(1200), m_Height(600), m_Title("Matrix Framework") {}
            ~WindowProps() {}

            int m_Width;
            int m_Height;
            std::string m_Title;
        };

        WindowProps m_Props; 
    };
}

#endif // WINDOW_H