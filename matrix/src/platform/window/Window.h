#ifndef WINDOW_H
#define WINDOW_H

#ifdef MX_GLFW_ACTIVE
    #define WINDOW_TYPE new Matrix::WindowGLFW();
#else
    #error "Matrix Framework only supports GLFW for now"
#endif

#include "matrix/src/pch/stdafx.h"

namespace Matrix {

    

    class Window {
    public:
        MATRIX_API Window() {}
        MATRIX_API ~Window() {}
        
        MATRIX_API void setWidth(int width);
        MATRIX_API void setHeight(int height);
        MATRIX_API void setTitle(std::string title);
        
        MATRIX_API virtual void update() const {};
        MATRIX_API virtual void render() const {};

        MATRIX_API virtual bool createContext() { return false; }
        MATRIX_API virtual void resize() const {}
        MATRIX_API virtual void close() const {}
    
        int m_Width = 1200;
        int m_Height = 600;
        std::string m_Title = "Matrix Framework";
    };
}

#endif // WINDOW_H