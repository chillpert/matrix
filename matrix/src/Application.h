#ifndef APPLICATION_H
#define APPLICATION_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/window/Window.h"
#include "matrix/src/platform/window/WindowGLFW.h"
#include "matrix/src/platform/window/WindowSDL2.h"
#include "matrix/src/platform/api/API.h"
#include "matrix/src/platform/api/API_OpenGL.h"
#include "matrix/src/layers/LayerStack.h"

namespace MX {

    class MX_API Application {     
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

    protected:   
        API* m_API = MX_API_TYPE;
        Window* m_Window = MX_WINDOW_TYPE;
        LayerStack* m_LayerStack = new LayerStack;
        bool m_Running;
    };  
}

#endif // APPLICATION_H