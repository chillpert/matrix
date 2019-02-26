#ifndef APPLICATION_H
#define APPLICATION_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/window/Window.h"
#include "matrix/src/platform/window/WindowGLFW.h"
#include "matrix/src/platform/api/API.h"
#include "matrix/src/platform/api/API_OpenGL.h"

namespace Matrix {

    class MATRIX_API Application {
    public:
        ~Application();
        static Application &get();
        
        void initialize(void (*initialize_func)());
        void render(void (*render_func)());
        void update(void (*update_func)());
        void stop();
        void clean();

        inline bool isRunning() { return m_Running; }
        inline auto getWindow() { return m_Window; }
        
    private: 
        Application();
        
        API* m_API = API_TYPE;
        Window* m_Window = WINDOW_TYPE;
        bool m_Running;
    };  
}

#endif // APPLICATION_H