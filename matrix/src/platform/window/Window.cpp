#include "matrix/src/platform/window/Window.h"

namespace Matrix {

    void Window::setWidth(int width) {
        m_Width = width;
    }
    
    void Window::setHeight(int height) {
        m_Height = height;
    }
    
    void Window::setTitle(std::string title) {
        m_Title = title;
    }
    
}