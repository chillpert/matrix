#ifndef WINDOWSDL2_H
#define WINDOWSDL2_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_SDL2_ACTIVE

namespace MX {

    class WindowSDL2 : public Window {
    public:
    	MX_API static WindowSDL2& get() {
            static WindowSDL2 instance;
            return instance;
        }

        MX_API ~WindowSDL2() {}

        MX_API void update() const override; 
        MX_API void render() const override; 
        MX_API bool createContext() override;

        MX_API void close() const override;
        MX_API void controllerCallback() override;

        MX_API void setTitle() override;
        MX_API void resize() override;
        
        MX_API inline SDL_Window* getWindow() { return m_Window; } 
        MX_API inline SDL_GLContext& getContext() { return m_Context; }
    private:
        MX_API WindowSDL2() {}

        SDL_Window* m_Window = NULL;
        SDL_GLContext m_Context;
    };
}

#endif

#endif // WINDOWSDL2_H