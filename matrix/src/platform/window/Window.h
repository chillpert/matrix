#ifndef WINDOW_H
#define WINDOW_H

#ifdef MX_GLFW_ACTIVE
    #define WINDOW_TYPE new Matrix::WindowGLFW();
#else
    #error "Matrix Framework only supports GLFW for now"
#endif

#include "matrix/src/pch/stdafx.h"

namespace Matrix {

    class MATRIX_API Window {
    public:
        Window() {}
        ~Window() {}
        
        void setWidth(int width);
        void setHeight(int height);
        void setTitle(std::string title);
        
        virtual void update() const {};
        virtual void render() const {};

        virtual bool createContext() { return false; }
        virtual void resize() const {}
        virtual void close() const {}
    
        int m_Width = 1200;
        int m_Height = 600;
        std::string m_Title = "Matrix Framework";
    };
}

#endif // WINDOW_H